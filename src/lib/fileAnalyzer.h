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

#ifndef _FILEANALYZER_H_
#define _FILEANALYZER_H_

#include <QList>
#include <QMutex>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "globals.h"

#include "logLine.h"

#include "logFile.h"
#include "logViewColumn.h"
#include "logViewColumns.h"

#include "analyzer.h"

class LogViewModel;
class LogFileReader;
class LogMode;

class FileAnalyzer : public Analyzer
{
    Q_OBJECT

public:
    explicit FileAnalyzer(LogMode *logMode);

    virtual ~FileAnalyzer();

    void watchLogFiles(bool enabled) Q_DECL_OVERRIDE;

    void setLogFiles(const QList<LogFile> &logFiles) Q_DECL_OVERRIDE;
    
    static LogLine logLinePrevious;
    
    QString tmp_filename;
    QRegularExpressionMatch hostname_match;
    
        QMap<QString, int> mapMonths;

protected:
    virtual LogFileReader *createLogFileReader(const LogFile &logFile) = 0;
    virtual Analyzer::LogFileSortMode logFileSortMode() = 0;

    virtual LogLine *parseMessage(const QString &logLine, const LogFile &originalFile) = 0;
    // virtual LogLine *adv_parseMessage(const QString &logLine, const LogFile &originalFile) = 0;

private:
    void deleteLogFiles();

    /**
     * Parse and insert the buffered lines in the model
     * Returns the count of inserted lines
     */
    int insertLines(const QStringList &bufferedLines, const LogFile &logFile, ReadingMode readingMode);
    

    /**
     * Parse and insert a line in the model
     * Returns false if it was not inserted, true if it was
     */
    bool insertLine(const QString &buffer, const LogFile &originalFile, ReadingMode readingMode);
    
    inline QString undefinedHostName();
    inline QString undefinedProcess();
    inline LogLine *undefinedLogLine(const QString &message, const LogFile &originalFile);

private slots:
    void logFileChanged(LogFileReader *logFileReader, Analyzer::ReadingMode readingMode,
                        const QStringList &content);

protected:
    QList<LogFileReader *> logFileReaders;
};


#endif // _FILEANALYZER_H_
