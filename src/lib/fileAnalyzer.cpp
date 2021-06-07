/***************************************************************************
 *   KSystemLog, a system log viewer tool                                  *
 *   Copyright (C) 2007 by Nicolas Ternisien                               *
 *   nicolas.ternisien@gmail.com                                           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 ***************************************************************************/

#include "fileAnalyzer.h"

#include <KLocalizedString>
#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
#include <QFileInfo>

#include "logging.h"
#include "ksystemlogConfig.h"

#include "logViewModel.h"


#include "logMode.h"
#include "logFileReader.h"

#include "logFile.h"



using namespace std;

FileAnalyzer::FileAnalyzer(LogMode *logMode)
    : Analyzer(logMode)
{
        // Initialize Existing months
    mapMonths[QLatin1String("Jan")] = 1;
    mapMonths[QLatin1String("Feb")] = 2;
    mapMonths[QLatin1String("Mar")] = 3;
    mapMonths[QLatin1String("Apr")] = 4;
    mapMonths[QLatin1String("May")] = 5;
    mapMonths[QLatin1String("Jun")] = 6;
    mapMonths[QLatin1String("Jul")] = 7;
    mapMonths[QLatin1String("Aug")] = 8;
    mapMonths[QLatin1String("Sep")] = 9;
    mapMonths[QLatin1String("Oct")] = 10;
    mapMonths[QLatin1String("Nov")] = 11;
    mapMonths[QLatin1String("Dec")] = 12;
    
}

FileAnalyzer::~FileAnalyzer()
{
    deleteLogFiles();

    // logMode is managed by Globals
    // logViewModel is managed by LogViewWidget
}

void FileAnalyzer::watchLogFiles(bool enabled)
{
    // Enable the log file watching, by revert order to read the most top file at last, and be sure its line
    // will be kept

    QListIterator<LogFileReader *> it(logFileReaders);
    it.toBack();
    while (it.hasPrevious()) {
        LogFileReader *logFileReader = it.previous();
        logFileReader->watchFile(enabled);
    }
}

void FileAnalyzer::deleteLogFiles()
{
    watchLogFiles(false);

    // Remove the watching on the monitored files
    foreach (LogFileReader *logFileReader, logFileReaders) {
        logDebug() << "Remove file : " << logFileReader->logFile().url().path();
        delete logFileReader;
    }

    logFileReaders.clear();
}

void FileAnalyzer::setLogFiles(const QList<LogFile> &logFiles)
{
    // Remove previous files
    deleteLogFiles();

    foreach (const LogFile &logFile, logFiles) {
        LogFileReader *logFileReader = createLogFileReader(logFile);
        logFileReaders.append(logFileReader);

        connect(logFileReader, &LogFileReader::contentChanged, this, &FileAnalyzer::logFileChanged);
        connect(logFileReader, &LogFileReader::statusBarChanged, this, &Analyzer::statusBarChanged);
        connect(logFileReader, &LogFileReader::errorOccured, this, &Analyzer::errorOccured);
    }
}

void FileAnalyzer::logFileChanged(LogFileReader *logFileReader, ReadingMode readingMode,
                                  const QStringList &content)
{
    QString filePath = logFileReader->logFile().url().path();
    if (readingMode == Analyzer::FullRead)
        logDebug() << "File " << filePath << " has been modified on full read.";
    else
        logDebug() << "File " << filePath << " has been modified on partial read";

    if (parsingPaused == true) {
        logDebug() << "Pause enabled. Nothing read.";
        return;
    }

    logDebug() << "Locking file modifications of " << filePath;
    insertionLocking.lock();
    logDebug() << "Unlocking file modifications of " << filePath;

    QTime benchmark;
    benchmark.start();

    int insertedLogLineCount;

    logViewModel->startingMultipleInsertions();

    if (readingMode == Analyzer::UpdatingRead) {
        insertedLogLineCount = insertLines(content, logFileReader->logFile(), Analyzer::UpdatingRead);
    } else {
        logDebug() << "Reading file " << filePath;

        emit statusBarChanged(i18n("Opening '%1'...", filePath));

        // Inform that we are now reading the "index" file
        emit readFileStarted(*logMode, logFileReader->logFile(),
                             logFileReaders.count() - logFileReaders.indexOf(logFileReader),
                             logFileReaders.count());

        insertedLogLineCount = insertLines(content, logFileReader->logFile(), Analyzer::FullRead);

        emit statusBarChanged(i18n("Log file '%1' loaded successfully.", filePath));
    }

    logViewModel->endingMultipleInsertions(readingMode, insertedLogLineCount);

    // Inform connected LoadingBar that the reading is now finished
    emit readEnded();

    // Inform LogManager that new lines have been added
    emit logUpdated(insertedLogLineCount);

    // Inform MainWindow status bar
    emit statusBarChanged(i18n("Log file '%1' has changed.", filePath));

    logDebug() << "Updating log files in " << benchmark.elapsed() << " ms";

    insertionLocking.unlock();
}


// The return value is apparently the number of inserted log lines
int FileAnalyzer::insertLines(const QStringList &bufferedLines, const LogFile &logFile,
                              ReadingMode readingMode)
{
    logDebug() << "Inserting lines...";

    // If there is no line
    if (bufferedLines.size() == 0) {
        logWarning() << "File is empty : " << logFile.url().path();
        return 0;  // Returns the number of inserted log lines
    }

    // HACK: For some log files, you need to set the hostname by scanning the file.
    //      Since this would take too long if you did it for every line, you should do it here.
    QString tmp_filename = logFile.url().fileName();
    QRegularExpression pattern_pm_suspend(R"Q(.*Linux (\w*).*)Q", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpression pattern_rkhunter(R"Q(.*Running Rootkit Hunter.*on (\w*)$)Q");    
    QRegularExpression pattern3234823(R"Q(^.*(\w{3,3}) (\d{1,2}) (\w{3,3}) (\d{4,4}) (\d{2,2}):(\d{2,2}):(\d{2,2}) (\w{2,2}) (\w{3,3}).*)Q");
    QRegularExpression pattern332834(R"Q(^.*(\w{3,3}) (\w{3,3})\s{1,2}(\d{1,2}) (\d{2,2}):(\d{2,2}):(\d{2,2}) (\w{3,3}) (\d{4,4}).*)Q",QRegularExpression::DotMatchesEverythingOption); // hibernate & suspend
    QRegularExpressionMatch hostname_match;
    // the pm-suspend file doesn't have regular timestamps
    // Look for "Initial commandline parameters", then time is around line 2, hostname is around line 10 
    if (tmp_filename.indexOf(QString("pm-suspend")) == 0 ) {

            // Assuming that a new FileAnalyzer is created for each separate file, the previousHostName shoudl be cleared every time.
            // If it isn't set, this should be the first batch of lines that has the ability to see things. So set it here.
            // Trying to be a little resilient to people changing the log format.
            QString opening_lines = bufferedLines[0]+bufferedLines[1]+bufferedLines[2]+bufferedLines[3]+bufferedLines[4]+bufferedLines[5]+bufferedLines[6]+bufferedLines[7]+bufferedLines[8]+bufferedLines[9]+bufferedLines[10]+bufferedLines[11]+bufferedLines[12];
            if (pattern_pm_suspend.match(opening_lines).hasMatch() ) {
                hostname_match = pattern_pm_suspend.match(opening_lines);
                previousHostName = hostname_match.captured(1);
            };
            // Now getting time. Reusing the match variable
            if (pattern332834.match(opening_lines).hasMatch() ) {
                hostname_match = pattern332834.match(opening_lines);
previousDate = QDateTime(QDate(hostname_match.captured(8).toInt(),mapMonths[hostname_match.captured(2)],hostname_match.captured(3).toInt()),
                    QTime(hostname_match.captured(4).toInt(),hostname_match.captured(5).toInt(),hostname_match.captured(6).toInt()));
                    //qDebug() << "pm-suspend previousDate time is " << previousDate << previousDate.isValid();
            };
        if (tmp_filename.indexOf(QString("rkhunter")) == 0) {
            //qDebug() << "Entered FileAnalyzer::insertLines for rkhunter";
            if (pattern_rkhunter.match(bufferedLines[0]).hasMatch() ) {
                //qDebug() << "FileAnalyzer::insertLines, pattern_rkhunter matches file " << bufferedLines[0];
                hostname_match = pattern_rkhunter.match(bufferedLines[0]);
                previousHostName = hostname_match.captured(1);
                //qDebug() << " hostname_match = " << hostname_match;
                if (pattern3234823.match(bufferedLines[2]).hasMatch() ){
                    hostname_match = pattern3234823.match(bufferedLines[2]);
                    previousDate = QDateTime( QDate(hostname_match.captured(4).toInt(),mapMonths[hostname_match.captured(3)],hostname_match.captured(2).toInt()),
                    QTime(hostname_match.captured(5).toInt(),hostname_match.captured(6).toInt(),hostname_match.captured(7).toInt()));
                    //qDebug() << "previousDate time is " << previousDate <<  previousDate.isValid();
                } else {
                    //qDebug() << "FileAnalyzer::insertLines, pattern3234823 no match on time " << bufferedLines[2];
                };
            } else {
                    //qDebug() << "FileAnalyzer::insertLines, pattern_rkhunter no match on host " << bufferedLines[0];
                };
        } else if (tmp_filename.indexOf(QString("Xorg.")) == 0) {
            if (pattern_pm_suspend.match(bufferedLines.join("")).hasMatch() ) {
                hostname_match = pattern_pm_suspend.match(bufferedLines.join(""));
                previousHostName = hostname_match.captured(1);
            }   
        } 
//         else if (tmp_filename.indexOf(QString("syslog")) == 0) {
//             Need to pull out the year for syslog in merge
//             QFile currentfile(logFile.url().path());
//             QFileInfo fileInfo; fileInfo.setFile(currentfile);
//             QDateTime fileCreated = fileInfo.lastModified();  // I need this for log files that don't include a year
//             previousDate = fileCreated;
//             qDebug() << "FileAnalyzer picking up previousDate for syslog " << currentfile << fileInfo << fileCreated << previousDate.isValid();
        };
 

    
    int stop = 0;
    int currentPosition = 0;

    QListIterator<QString> it(bufferedLines);
    /**
     * If the log file is sorted, then we can ignore the first lines
     * if there are more lines in the log file than the max lines
     *
     * TODO Read revertly the file and ignore last lines if we are in Descending mode
     */
    logDebug() << "Log file Sort mode is " << logFileSortMode();
    
    // it is a buffer iterator, currentPosition looks like the number of lines inserted.
    if (logFileSortMode() == Analyzer::AscendingSortedLogFile) {
        // Calculate how many lines we will ignore
        if (bufferedLines.size() > KSystemLogConfig::maxLines()) {
            stop = bufferedLines.size() - KSystemLogConfig::maxLines();
        }

        // Ignore those lines
        while (currentPosition < stop) {
            it.next();
            ++currentPosition;
        }
    }

    int insertedLogLineCount = 0;
    QString buffer; 
    while (currentPosition < bufferedLines.size()) {
        buffer = it.next();

 
        // I've modified this to include the previous line, just in case we have an advanced parser
        bool inserted = insertLine(buffer, logFile, readingMode);
      
        if (inserted) {
            insertedLogLineCount++;
        }

        // It's updating the progress bar
        if (readingMode == Analyzer::FullRead) {
            informOpeningProgress(currentPosition, (bufferedLines.size() - 1) - stop);
        }

        ++currentPosition;

    }

    qDebug() << "Total read lines :" << (bufferedLines.size() - stop) << "(" << logFile.url().path() << ")";

    return insertedLogLineCount;
}

bool FileAnalyzer::insertLine(const QString &buffer, const LogFile &originalFile, ReadingMode readingMode)
{
    // This is where the action is. It's being called by the function above, insertLines (catchy naming)
    // HACK: I'm passing the previous line as a class static var. This is necessary to make some of these parsers work, rather than rewriting everything.

     LogLine* line;
    if (buffer.length() > 14)  { line = parseMessage(buffer, originalFile); } else {return false; };

    
    // Invalid log line or empty one
    if (line == NULL ||  line == undefinedLogLine("", originalFile) || line->logItems().isEmpty()) {
//qDebug() << "*******************************************";
//qDebug() << "*******************************************";
//qDebug() << "*******************************************";
//qDebug() << "Returning false on FileAnalyzer::insertLine " << line << originalFile;
//qDebug() << "*******************************************";
//qDebug() << "*******************************************";
//qDebug() << "*******************************************";
        return false;
    }

    previousDate = line->time(); // saving the actual line data so I can see the previous line to steal date, global var
    
    // On full reading, it is not needed to display the recent status
    if (readingMode == Analyzer::FullRead) {
        line->setRecent(false);
    }

    // I'm assuming this is some sort of ridiculous function overloading to get logViewModel to represent every logView
    // 
    return logViewModel->insertNewLogLine(line);
}

inline LogLine *FileAnalyzer::undefinedLogLine(const QString &message, const LogFile &originalFile)
{
    QStringList items;
    items << undefinedHostName() << undefinedProcess() << message;
    return new LogLine(logLineInternalIdGenerator++, QDateTime::currentDateTime(), items,
                       originalFile.url().path(), originalFile.defaultLogLevel(), logMode);
}


inline QString FileAnalyzer::undefinedHostName()
{
    // i18nc("Undefined host name", "undefined");
    return QLatin1String("");
}

inline QString FileAnalyzer::undefinedProcess()
{
    // i18nc("Undefined process", "undefined");
    return QLatin1String("");
}
