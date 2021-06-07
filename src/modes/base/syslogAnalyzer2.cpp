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

#include "syslogAnalyzer2.h"

#include <QStringList>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QDebug>
#include <QMap>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QHostInfo>
#include <QFileInfo>

#include <KLocalizedString>

#include "globals.h"
#include "logging.h"

#include "localLogFileReader.h"
#include "logLine.h"
#include "logMode.h"
#include "logLevel.h"
#include "logViewWidget.h"

#include "logViewModel.h"

#include "parsingHelper.h"

#include "ksystemlogConfig.h"


extern QDateTime previousDate;




 
    inline LogLevel* SyslogAnalyzer2::level_from_message(const QString &level_message) {
        
            if (level_message == "" || level_message.length() < 3) {Globals::instance().informationLogLevel(); };

    const QRegularExpression* pattern_emergency = new QRegularExpression(R"Q([-\ ]*EMERGENCY|EMERG|EMRG|Emergency[:\ ]|emergency:|\ emerg\ |\.emerg[:\.\ ])Q");
    const QRegularExpression* pattern_alert =  new QRegularExpression(R"Q([-\ ]*ALERT|ALERT|ALRT|Alert[:\ ]|\.alert[:\.\ ])Q");
    const QRegularExpression* pattern_critical =  new QRegularExpression(R"Q([-\ ]*CRITICAL|CRIT|Critical[:\ ]|\ critical\ |\.crit[\.\ ]|\.critical[:\.\ ]| PANIC[:\ ]| panic[:\ ])Q");
    const QRegularExpression* pattern_error = new  QRegularExpression(R"Q([-\ ]*ERROR|ERR|\ Error[:\ ]|\ error\ |\ err\ |\.err[\.\ ]|\.error[:\.\ ]|'.*'\s+[fF]ailed)Q");
    const QRegularExpression* pattern_warning = new  QRegularExpression(R"Q([-\ ]*WARNING|WARN|WRN|\ Warning[:\ ]|\ warn\ |\ warning\ |\ warning:|\.warn[\.\ ]|\.warning[:\.\ ])Q");
    const QRegularExpression* pattern_notice = new  QRegularExpression(R"Q([-\ ]*NOTICE|NOTICE|\ Notice[:\ ]|\ notice\ |\.notice[:\.\ ])Q");
    const QRegularExpression* pattern_debug = new  QRegularExpression(R"Q(DBG|[-\ ]*DEBUG|\ Debug[:\ ]|\.debug[:\.\ ])Q");
    
    // Massive screwup in Qt
    if (level_message == "") { return(Globals::instance().informationLogLevel()); };
        
        if ((pattern_emergency->match(level_message).hasMatch())) {
            return Globals::instance().emergencyLogLevel();
        } else if ((pattern_critical->match(level_message).hasMatch())) {
            return Globals::instance().criticalLogLevel();
        } else if ((pattern_alert->match(level_message).hasMatch())) {
            return Globals::instance().alertLogLevel();
        } else if ((pattern_error->match(level_message).hasMatch())) {
            return Globals::instance().errorLogLevel();
        } else if ((pattern_warning->match(level_message).hasMatch())) {
            return Globals::instance().warningLogLevel();
        } else if ((pattern_notice->match(level_message).hasMatch())) {
            return Globals::instance().noticeLogLevel();
        } else if ((pattern_debug->match(level_message).hasMatch())) {
            return Globals::instance().debugLogLevel();
        }

        return Globals::instance().informationLogLevel();
    }    
       
        inline QString SyslogAnalyzer2::get_standard_level(const QString &level_message) {
            
            

    // const QRegularExpression* pattern_emergency = new QRegularExpression(R"Q(EMERG|EMRG|Emergency|\ emerg\ |\.emerg[\.\ ])Q");
    const QRegularExpression* pattern_emergency = new QRegularExpression(R"Q([-\ ]*EMERGENCY|EMERG|EMRG|Emergency[:\ ]|emergency:|\ emerg\ |\.emerg[:\.\ ])Q");
    const QRegularExpression* pattern_alert =  new QRegularExpression(R"Q([-\ ]*ALERT|ALERT|ALRT|Alert[:\ ]|\.alert[:\.\ ])Q");
    const QRegularExpression* pattern_critical =  new QRegularExpression(R"Q([-\ ]*CRITICAL|CRIT|Critical[:\ ]|\ critical\ |\.crit[\.\ ]|\.critical[:\.\ ]| PANIC[:\ ]| panic[:\ ])Q");
    const QRegularExpression* pattern_error = new  QRegularExpression(R"Q([-\ ]*ERROR|ERR|\ Error[:\ ]|\ error\ |\ err\ |\.err[\.\ ]|\.error[:\.\ ]|'.*'\s+[fF]ailed)Q");
    const QRegularExpression* pattern_warning = new  QRegularExpression(R"Q([-\ ]*WARNING|WARN|WRN|\ Warning[:\ ]|\ warn\ |\ warning\ |\ warning:|\.warn[\.\ ]|\.warning[:\.\ ])Q");
    const QRegularExpression* pattern_notice = new  QRegularExpression(R"Q([-\ ]*NOTICE|NOTICE|\ Notice[:\ ]|\ notice\ |\.notice[:\.\ ])Q");
    const QRegularExpression* pattern_debug = new  QRegularExpression(R"Q(DBG|[-\ ]*DEBUG|\ Debug[:\ ]|\.debug[:\.\ ])Q");
    
        // Massive screwup in Qt
        if (level_message == "") { return(QString("INFO")); };


            if ((pattern_emergency->match(level_message).hasMatch())) {
                return QString("EMERG");
            } else if ((pattern_critical->match(level_message).hasMatch())) {
                return QString("CRIT");
            } else if ((pattern_alert->match(level_message).hasMatch())) {
                return QString("ALERT");
            } else if ((pattern_error->match(level_message).hasMatch())) {
                return QString("ERR");
            } else if ((pattern_warning->match(level_message).hasMatch())) {
                return QString("WARN");
            } else if ((pattern_notice->match(level_message).hasMatch())) {
                 return QString("NOTICE");
            } else if ((pattern_debug->match(level_message).hasMatch())) {
                return QString("DBG");
            }

        return QString("");  // You are expected to fill this in below.
        // return QString("INFO");
        }    

SyslogAnalyzer2::SyslogAnalyzer2(LogMode *logMode)
    : FileAnalyzer(logMode)
{
}

SyslogAnalyzer2::~SyslogAnalyzer2()
{
}

LogViewColumns SyslogAnalyzer2::initColumns()
{
    LogViewColumns columns;
    columns.addColumn(LogViewColumn(i18n("Date"), true, false));
    columns.addColumn(LogViewColumn(i18n("Host"), true, true));
    columns.addColumn(LogViewColumn(i18n("Process"), true, true));
    columns.addColumn(LogViewColumn(i18n("Level"), true, true));
    columns.addColumn(LogViewColumn(i18n("Message"), true, false));
        //qDebug() << "Added columns";
    return columns;
}

LogFileReader *SyslogAnalyzer2::createLogFileReader(const LogFile &logFile)
{
    return new LocalLogFileReader(logFile);
}

Analyzer::LogFileSortMode SyslogAnalyzer2::logFileSortMode()
{
    return Analyzer::AscendingSortedLogFile;
}

// Bogus parser to keep C++ happy

// LogLine *SyslogAnalyzer2::parseMessage(const QString &logLine, const LogFile &originalFile) {
// 
//     QString incrediblelevelsofbullshit = logLine; 
//     QString superbullshit = QString("I'm using the wrong parser. Try using adv_parser. Original:") + incrediblelevelsofbullshit;
//     QStringList bullshit = {QString("DOESNOTEXIST"), QString("bogus"), superbullshit};
//     return new LogLine(
//         logLineInternalIdGenerator++, 
//         QDateTime::currentDateTime(), 
//         bullshit, 
//         originalFile.url().path(),
//         originalFile.defaultLogLevel(), 
//         logMode);
//     }





// We're getting passed a string logLine & a file originalFile.
// We're returning a pointer to structure LogLine, defined in logLine.h
//  logLine.d is the logLinePrivate
//    Members include 
//          long internalId; 
//          QDateTime time; 
//          QStringList logItems; 
//          QString originalFile; 
//          LogLevel *logLevel; 
//          LogMode *logMode; 
//          bool recent;
//          LogViewWidgetItem *item;
LogLine *SyslogAnalyzer2::parseMessage(const QString &logLine, const LogFile &originalFile  )
{
    // qDebug() << QTime::currentTime() << " : Reading line : " << logLine << " from " << originalFile.url.path();
    // 5 is an arbitrary number. I hate having line fragments contaminate things.
    
    if (logLine.length() < 15 ) {
    //qDebug() << "Too short line" << logLine;
        return SyslogAnalyzer2::undefinedLogLine(logLine, originalFile);
    }
  
    QMap<QString, QString> mapMonths;
        // Initialize Existing months
    mapMonths[QString("Jan")] = QLatin1String("01");
    mapMonths[QString("Feb")] = QLatin1String("02");
    mapMonths[QString("Mar")] = QLatin1String("03");
    mapMonths[QString("Apr")] = QLatin1String("04");
    mapMonths[QString("May")] = QLatin1String("05");
    mapMonths[QString("Jun")] = QLatin1String("06");
    mapMonths[QString("Jul")] = QLatin1String("07");
    mapMonths[QString("Aug")] = QLatin1String("08");
    mapMonths[QString("Sep")] = QLatin1String("09");
    mapMonths[QString("Oct")] = QLatin1String("10");
    mapMonths[QString("Nov")] = QLatin1String("11");
    mapMonths[QString("Dec")] = QLatin1String("12");

    
  //qDebug() << "Previous host name is " << previousHostName;
  //qDebug() << "Previous date/time is " << previousDate;
    
    // Some scratch vars to hold the info
    QString date, day, month, year, time8, time83, tz, am_pm, level, utc_adjust, message;
    bool got_match = false;
    
    // Pointer to convience logLevels to indicate message priority (EMERGENCY, CRITICAL, etc....)
    LogLevel* alevel = Globals::instance().informationLogLevel();
      
    QDateTime dateTime;       

    QFile currentfile(originalFile.url().path());
    QFileInfo fileInfo; fileInfo.setFile(currentfile);
    QDateTime fileCreated = fileInfo.lastModified();  // I need this for log files that don't include a year
    QString currentfilename = fileInfo.fileName();
    QString currentfilepath = fileInfo.path();
  //qDebug() << "currentfilepath = " << currentfilepath;
    QString localhostname = "";
  
    // These regular expression patterns are based on the current crop of log file formats
    // The naming convention is based on the number of characters in the opening items such as Date, Day, Month, Year
    // The R"Q(....)"Q is a raw string. No way to do it otherwise, unless you want to be escaping your escape chars & making everything unreadable.
    // [\^$.|?*+()
    QRegularExpression pattern3234823(R"Q(^.*(\w{3,3})[-\s]{1,2}(\d{1,2})[-\s](\w{3,3}) (\d{4,4}) (\d{2,2}):(\d{2,2}):(\d{2,2}) (\w{2,2}) (\w{3,3}).*)Q");  // sleep & others
          //qDebug() << "pattern3234823 is valid? " << pattern3234823.isValid(); 
    QRegularExpression pattern332834(R"Q(^.*(\w{3,3}) (\w{3,3})\s{1,2}(\d{1,2}) (\d{2,2}):(\d{2,2}):(\d{2,2}) (\w{3,3}) (\d{4,4}).*)Q"); // hibernate & suspend
          //qDebug() << "pattern332834 is valid? " << pattern332834.isValid(); 
    QRegularExpression pattern323a(R"Q(^.*(\w{3,3}),*[-\s]{1,2}(\d{1,2})[-\s](\w{3,3}) (\d{4,4}) ([:\d]{8,8}) ([-+\d]{4,5})(.*))Q");
          //qDebug() << "pattern323a is valid? " << pattern323a.isValid();
    QRegularExpression pattern323b(R"Q(^.*(\w{3,3})[-\ ]{1,2}(\d{1,2})[-\ ]{1,1}(\w{3,3}) (\d{4,4}) ([:\d]{8,8})c (\S{2,}) (.*))Q");
          //qDebug() << "pattern323b is valid? " << pattern323b.isValid();
    QRegularExpression pattern328host(R"Q(^.*(\w{3,3})[-\ ]{1,2}(\d{1,2})[-\ ]{1,1}([:\d]{8,8}) ([-_\w]+) (\w+)(.*))Q");
          //qDebug() << "pattern328host is valid? " << pattern328host.isValid();
    QRegularExpression pattern328hostprocess(R"Q(^.*(\w{3,3})[-\ ]{1,2}(\d{1,2})[-\ ]{1,1}([:\d]{8,8}) ([-_\w]+) ([-_\w\d\[\]]+): (.*))Q");
          //qDebug() << "pattern328host is valid? " << pattern328host.isValid(); // syslog in merge
    QRegularExpression pattern332a(R"Q(^.*(\w{3,3})[-\ ]{1,1}(\w{3,3})[-\ ]{1,2}(\d{1,2}) ([:\d]{8,12}) (\w{3,}) (\d{4,4}) (.*))Q");
          //qDebug() << "pattern332a is valid? " << pattern332a.isValid();
    QRegularExpression pattern332b(R"Q(^.*(\w{3,3})[-\ ]{1,1}(\w{3,3})[-\ ]{1,1}(\d{2,2}) ([:\d]{8,12}) (\w{3,}) (\d{4,4}))Q");
          //qDebug() << "pattern332b is valid? " << pattern332a.isValid();
    QRegularExpression pattern422a(R"Q(^(\d{4,4})[-\ ]{1,1}(\d{1,2})[-\ ]{1,1}(\d{2,2}) ([:\.\d]{12,12}) (\w{3,})(.*))Q");     
          //qDebug() << "pattern422a is valid? " << pattern422a.isValid();
    QRegularExpression pattern422b(R"Q(^(\d{4,4})[-\ ]{1,1}(\d{1,2})[-\ ]{1,1}(\d{2,2}) ([:\.\d]{8,8})[\s:]{1,}(.*))Q"); 
          //qDebug() << "pattern422b is valid? " << pattern422b.isValid();
    QRegularExpression pattern422c(R"Q(^.*(\d{4,4})[-/](\d{2,2})[-/](\d{2,2}) ([:\.\d]{8,12})[:\s]\(UTC[-+]{1,1}([:\d]{4,4})\)(.*))Q"); 
          //qDebug() << "pattern422c is valid? " << pattern422c.isValid();
    QRegularExpression pattern422d(R"Q(^.*(\d{4,4})[-/](\d{2,2})[-/](\d{2,2}) ([:\.\d]{8,8})[:\s](.*))Q"); // alternatives
          //qDebug() << "pattern422d is valid? " << pattern422d.isValid();
    QRegularExpression pattern_team(R"Q(^(\d{4,4})/(\d{2,2})/(\d{2,2}) ([:\.\d]{8,12}) (.*))Q"); 
          //qDebug() << "pattern_team is valid? " << pattern_team.isValid();
    // Rootkit Hunter is a bit odd, just grab time & message, get level out of message
    QRegularExpression pattern8rkhunter(R"Q(^\[([:\.\d]{8,8})\] (.*))Q"); 
          //qDebug() << "pattern8rkhunter is valid? " << pattern422c.isValid();    
    
      //qDebug() << "Our logLine is " << logLine ;
    // Who let these people out of the asylum?!?!
    QRegularExpressionMatch match;
    QString hostname = "";
    QString process;
    
    // Resetting everything
    day = "";
    date = "";
    month = "";
    year = "";
    time8 = "";
    time83 = "";
    am_pm = "";
    tz = "";
    utc_adjust = "";
    message = "";
    level = "";
    hostname = "";

    
    if (currentfilename.startsWith("pm-powersave") || currentfilename.startsWith("security.report.")) {
      //qDebug() << "I'm not going to bother matching because the filename is " << currentfilename;
        // dont' bother matching
        message = logLine;
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine);
        got_match = true;
    } else if (!logLine.startsWith("   ") && currentfilename.startsWith("TeamViewer")  ) {  // Anything starting w/ spaces isn't a real line. It's a header line. It should pick up the date/time from the previous line. It will be wrong, but the header has the date/time
        // use pattern_team and fail anything that doesn't match
        match = pattern_team.match(logLine);
        year = match.captured(1);
        month = match.captured(2);
        date = match.captured(3);
        time83 = match.captured(4);
        message = match.captured(5);
        // Anything that doesn't match the pattern is a header. Useful, yes, but really 
        got_match = true;
    } else if ((pattern323a.match(logLine).hasMatch())) {
        match = pattern323a.match(logLine);
        day = match.captured(1);
        date = match.captured(2);
        month = mapMonths[match.captured(3)];
        year = match.captured(4);
        time8 = match.captured(5);
        utc_adjust = match.captured(6);
        message = match.captured(7);
        // This is how you try to get a level extracted from the message text, assuming there is no explicit specification.
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern323a";
    } else if ((pattern323b.match(logLine).hasMatch())) {
        match = pattern323b.match(logLine);
        day = match.captured(1);
        date = match.captured(2);
        month = mapMonths[match.captured(3)];
        time83 = match.captured(4);
        tz = match.captured(5);
        year = match.captured(6);
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern323b";       
    } else if ((pattern332a.match(logLine).hasMatch())) {
         match = pattern332a.match(logLine);
         day = match.captured(1);
        month = mapMonths[match.captured(2)];
        date = match.captured(3);
        year = match.captured(4);
        time8 = match.captured(5);
        message = match.captured(6);
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern332a";       
    } else if ((pattern332b.match(logLine).hasMatch())) {
        match = pattern332b.match(logLine);
        day = match.captured(1);
        month = mapMonths[match.captured(2)];
        date = match.captured(3);
        time83 = match.captured(4);       
        tz = match.captured(5);
        year = match.captured(6);
        message = logLine; // Just a time message
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern332b";     
      //qDebug() << match;
    } else if (currentfilename.indexOf("syslog") == 0 || currentfilename.indexOf("ufw.log") == 0 || currentfilename.indexOf("daemon.log") == 0) {
        match = pattern328hostprocess.match(logLine);
        month = mapMonths[match.captured(1)];
        date = match.captured(2);
        time8 = match.captured(3);
        hostname = match.captured(4);
        process = match.captured(5);
        if (currentfilename.indexOf("ufw.log") == 0) process = "firewall";
        message = match.captured(6);
        year = QString::number(fileCreated.date().year()); 
//         if ( previousDate.isValid() && month.toInt() <= previousDate.date().month() ) {
//             year = QString::number(previousDate.date().year());  // You have to get the year from the file in fileAnalyzer.cpp
//         } else {
//           //qDebug() << "syslog is not getting the previousDate in fileAnalyzer.cpp";
//         }
//         if (month.toInt() > previousDate.date().month() ) {
//           //qDebug() << " syslog date appending: year & the rollover conversion" << year ;
//             year = QString::number(year.toInt() - 1);  // cover the case where the 
//           //qDebug() << " syslog date appending: year after conversion" << year ;
//                logfile wraps around the year, assuming you
//                rotate your logfiles more than once a year.
//         }
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern328hostprocess";   
      //qDebug() << match;
    } else if (!(currentfilepath.indexOf("exim") >= 0) && !currentfilename.startsWith("sleep") && !currentfilename.startsWith("pm-") && (pattern328host.match(logLine).hasMatch())  ) {
        match = pattern328host.match(logLine);
        month = mapMonths[match.captured(1)];
        date = match.captured(2);
        time83 = match.captured(3);
        hostname = match.captured(5);
        message = match.captured(6);
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern328host";     
      //qDebug() << match;
    } else if ((pattern422a.match(logLine).hasMatch())) {
        match = pattern422a.match(logLine);
        year = match.captured(1);
        month = match.captured(2);
        date = match.captured(3);
        time83 = match.captured(4);
        level = match.captured(5);
        alevel = level_from_message(level);
        level = get_standard_level(level); // Standardize the output
        message = match.captured(6);
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern422a";       
    } else if ((pattern422b.match(logLine).hasMatch())) {
        match = pattern422b.match(logLine);
        year = match.captured(1);
        month = match.captured(2);
        date = match.captured(3);
        time83 = match.captured(4);
        message = match.captured(5);
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern422b";  
    } else if ((pattern422c.match(logLine).hasMatch())) {
        match = pattern422c.match(logLine);
        year = match.captured(1);
        month = match.captured(2);
        date = match.captured(3);
        time83 = match.captured(4);
        utc_adjust = match.captured(5);
        message = match.captured(6);
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern422c";  
    }  else if ((pattern422d.match(logLine).hasMatch())) {
        match = pattern422d.match(logLine);
        year = match.captured(1);
        month = match.captured(2);
        date = match.captured(3);
        time8 = match.captured(4);
        message = match.captured(5);
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern422d";  
    }  else if (currentfilename.startsWith("rkhunter") && (pattern8rkhunter.match(logLine).hasMatch())  ) {
        match = pattern8rkhunter.match(logLine);
        time8 = match.captured(1);
        message = match.captured(2);
        dateTime = previousDate;
        hostname = previousHostName;
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern8rkhunter";  
      //qDebug() << match;
    }  else if ((pattern3234823.match(logLine).hasMatch())) {
        match = pattern3234823.match(logLine);
        day = match.captured(1);
        date = match.captured(2);
        month = mapMonths[match.captured(3)];
        year = match.captured(4);
        am_pm = match.captured(8);
        if (am_pm == "AM" || am_pm == "am") {
            time8 = match.captured(5)+":"+match.captured(6)+":"+match.captured(7);
        } else {
            time8 = QString::number(match.captured(5).toInt()+12)+":"+match.captured(6)+":"+match.captured(7);   
        };
        tz = match.captured(9);
        message = "";
        // This is how you try to get a level extracted from the message text, assuming there is no explicit specification.
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern3234823";
      //qDebug() << match;
    } else if ((pattern332834.match(logLine).hasMatch())) {
        match = pattern332834.match(logLine);
        day = match.captured(1);
        month = mapMonths[match.captured(2)];
        date = match.captured(3);
        time8 = match.captured(4)+":"+match.captured(5)+":"+match.captured(6);
        tz = match.captured(7);
        year = match.captured(8);
        message = "";
        // This is how you try to get a level extracted from the message text, assuming there is no explicit specification.
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = true;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "Match pattern332834";
      //qDebug() << match;
    } else {   // No match, so defaults;
        message = logLine;
        alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
        level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        got_match = false;  // I have to try multiple patterns. Best to keep track of success explicitly.
      //qDebug() << "No Match !!! on " << logLine << " level = " << level;         
    };
  //qDebug() << "Out of  syslogAnalyzer2::parseMessage matching field & time8, time83 = " << time8 << time83 << year;
    
    // Convert all time8 formats to time8.3
    if (time83.length() == 9) time83.chop(1); // guarding against mistakes, I allow a trailing :
    if (time8.length() == 9) time8.chop(1);  
    if (time83.length() == 0 && time8.length() != 0) time83 = time8.append(QString(".000"));
    if (time83.length() == 8) time83  = time83.append(QString(".000"));
  //qDebug() << "time8 " << time8 << " time83 " << time83;
 
    // Extract time & date info. Create the output dateTime
    QRegularExpression pattern_time(R"Q((\d{2,2}):(\d{2,2}):(\d{2,2}).(\d{3,3}))Q");
    QRegularExpressionMatch time_match = pattern_time.match(time83);
  //qDebug() << "Trying to match time83 " << time83 << time_match;
    if (time83.length() == 12 && year != "" && date != "" && month != "" && time_match.hasMatch()) {
        // This is the timestamp output from this routine.
        dateTime = QDateTime(QDate(year.toInt(), month.toInt(), date.toInt()),                                          
                    QTime(time_match.captured(1).toInt(),time_match.captured(2).toInt(),time_match.captured(3).toInt()).addMSecs(time_match.captured(3).right(3).toInt()));  
      //qDebug() << "In date setting1: year, month, date " << year << month << date;
      //qDebug() << "In date setting1: QDate = " << QDate(year.toInt(), month.toInt(), date.toInt());
      //qDebug() << "In date setting1: QTime = " << QTime(time_match.captured(1).toInt(),time_match.captured(2).toInt(),time_match.captured(3).toInt()).addMSecs(time_match.captured(3).right(3).toInt());
      //qDebug() << "dateTime just matched is " << dateTime << " and is " << dateTime.isValid();
    };
  //qDebug() << "dateTime is " << dateTime << " and is " << dateTime.isValid();


    if (hostname.length() <= 0) localhostname = QHostInfo::localHostName(); // 
    // A decision needs to be made on a case-by-case basis as to whether to include the hostname.
    // If it's possible to be mistaken, it should be omitted.
    
    // QtGlobals Doesn't work. Don't try again. QString tmp_result = QString::fromStdString(qgetenv("HOSTNAME").toStdString());
    // The file name being examined is originalFile.url.toString()
    // The previous line LogLine &previous_line needs to be added to everything, logLinePrevious
    
  
    // TOTAL HACK:
    // Some of the logging formats actually have the hostname and process name. This is going to be super-useful in a merge
    // Filenames: pm-*, mail* will have their process name injected & the hostname parsed

     
    // Filenames: ddm*, nvid*, format*, alternatives*, trim*, teamviewer*, mx-*, rkhunter*, ufw*, gufw*, tiger*, hibernate*, sleep*, openvpn*, cups/access*, 
    // will have their process name artificially inserted


    QRegularExpression pattern_tigerhostname(R"Q(security\.report\.(\w*)\.(\d{2,2})(\d{2,2})(\d{2,2})-(\d{2,2}):(\d{2,2}))Q");
    QRegularExpression pattern_teamviewer_id(R"Q(^ID:\s*(\d+))Q");
    QRegularExpressionMatch hostname_try;    
    QString tmp_filename = originalFile.url().fileName();
    QString tmp_filepath = originalFile.url().path();
  //qDebug() << " Our filename for today is " << originalFile.url().fileName();
    if (process.length() == 0) {
        if (tmp_filename.lastIndexOf(QString("formatusb")) >= 0) {
            process = "formatusb";
        } else if (tmp_filename.indexOf(QString("ddm.log")) >= 0 || tmp_filename.indexOf(QString("nvidia")) >= 0) {
            process = "nvidia";
            dateTime = fileCreated;
          //qDebug() << "Nvidia here. File creation date = " << fileCreated << " which is " << fileCreated.isValid();
        } else if (tmp_filename.indexOf(QString("alternatives")) >= 0) {
            process = "alternatives";
        } else if (tmp_filename.indexOf(QString("fontconfig")) >= 0) {
            process = "fontconfig";
        } else if (tmp_filename.indexOf(QString("trim.log")) >= 0) {
            process = "trim";
        } else if (tmp_filename.indexOf(QString("TeamViewer")) >= 0) {
            process = "teamviewer";
            // Teamviewer occasionally puts a block of startup info. This grabs the Teamviewer ID# out of that block.
            // There is also interesting information in terms of participant <hostname> that I'm not capturing.
            // It will take a bit more work to actually parse what these log files mean.
            if (pattern_teamviewer_id.match(logLine).hasMatch()) {
                hostname_try = pattern_teamviewer_id.match(logLine);
                hostname = hostname_try.captured(1);
                previousHostName = hostname;
            } else {
                hostname = previousHostName;
            };
        } else if (tmp_filename.indexOf(QString("mx-snapshot")) >= 0) {
            process = "mx-snapshot";
        } else if (tmp_filename.indexOf(QString("mx-boot-repair")) >= 0) {
            process = "mx-boot-repair";
        } else if (tmp_filename.indexOf(QString("mx-live-usb-maker")) >= 0) {
            process = "mx-live-usb-maker";
        } else if (tmp_filename.indexOf(QString("rkhunter")) >= 0) {
            process = "rkhunter";
        } else if (tmp_filename.indexOf(QString("ufw.log")) >= 0 || tmp_filename.indexOf(QString("gufw")) >= 0) {
            process = "ufw-firewall";
        } else if (tmp_filename.lastIndexOf(QString("security.report.")) == 0) {
            process = "tiger";
            if (previousDate.isValid()) {
                dateTime = previousDate;
                if (previousHostName != "") hostname = previousHostName;
            } else if (hostname == "" && pattern_tigerhostname.match(currentfilename).hasMatch()) {
                time_match = pattern_tigerhostname.match(currentfilename);
                hostname_try = pattern_tigerhostname.match(currentfilename);
                hostname = hostname_try.captured(1);
                previousHostName = hostname;
                //qDebug() << "Tiger: trying to set host & date: host " << hostname << " dateTime match " << hostname_try;
                dateTime = QDateTime(QDate(2000+time_match.captured(2).toInt(),time_match.captured(3).toInt(),time_match.captured(4).toInt()),QTime(time_match.captured(5).toInt(),time_match.captured(6).toInt(),QString("00").toInt()));
                previousDate = dateTime;
            };
        } else if (tmp_filename.indexOf(QString("hibernate.")) >= 0) {
            process = "hibernate";
        } else if (tmp_filename.indexOf(QString("sleep.")) >= 0) {
            process = "sleep";
        } else if (tmp_filename.indexOf(QString("pm-powersave")) >= 0) {
            process = "powersave";
        } else if (tmp_filename.indexOf(QString("pm-suspend")) >= 0) {
            process = "suspend";
        } else if (tmp_filename.indexOf(QString("acpid")) >= 0) {
            process = "acpid";
        } else if (tmp_filename.indexOf(QString("samba")) >= 0) {
            process = "samba";
        } else if (tmp_filename.indexOf(QString("lightdm")) >= 0) {
            process = "lightdm";
        } else if (tmp_filepath.indexOf(QString("cups")) >= 0) {
            process = "cups";
        } else if (tmp_filepath.indexOf(QString("apache")) >= 0 || tmp_filepath.indexOf(QString("httpd")) >= 0) {
            process = "apache";
        } else if (tmp_filepath.indexOf(QString("samba")) >= 0 || tmp_filename.indexOf(QString("smbd.log")) == 0) {
            process = "samba";
        } else if (tmp_filename.indexOf(QString("mail.")) >= 0 || tmp_filepath.indexOf(QString("exim")) >= 0 || tmp_filename.indexOf(QString("postfix.")) >= 0 || tmp_filename.indexOf(QString("sendmail.")) >= 0 || tmp_filename.indexOf(QString("mutt.")) >= 0 || tmp_filename.indexOf(QString("qmail.")) >= 0 ) {
            if (process == "") process = "mail";
            if (year == "") { // fixing up dateTime
                year = QString::number(fileCreated.date().year());
              //qDebug() << "Special mail year = " << year;
                  //qDebug() << "Special for mail to match time83 " << time83 << time_match;
                    if (time83.length() == 12 && year != "" && date != "" && month != "" && time_match.hasMatch()) {
                        // This is the timestamp output from this routine.
                        dateTime = QDateTime(QDate(year.toInt(), month.toInt(), date.toInt()),                                          
                                    QTime(time_match.captured(1).toInt(),time_match.captured(2).toInt(),time_match.captured(3).toInt()).addMSecs(time_match.captured(3).right(3).toInt()));  
                      //qDebug() << "In date setting2: year, month, date " << year << month << date;    
                      //qDebug() << "In date setting2: QDate = " << QDate(year.toInt(), month.toInt(), date.toInt());
                      //qDebug() << "In date setting2: QTime = " << QTime(time_match.captured(1).toInt(),time_match.captured(2).toInt(),time_match.captured(3).toInt()).addMSecs(time_match.captured(3).right(3).toInt());
                      //qDebug() << "dateTime just matched is " << dateTime << " and is " << dateTime.isValid();
                    };
                  //qDebug() << "dateTime is " << dateTime << " and is " << dateTime.isValid();
            };
        } ;
    };
    
    
    // If you didn't match a pattern, need to dummy up the info. 
    // Search for warning level in the message
    // If you can't find warning level, grab warning from previous message
    // If the previous line had a valid date, use it. Otherwise, you get back dated to 1970.
    if (!got_match) { // This match is from the previous patterns, not the time match

        // Can you find warning level in message?
        if (level == "") {
            alevel = level_from_message(logLine);  // This is returning a funky reference to a logLevel object
            level = get_standard_level(logLine); // This is returning text to a short all-caps standardized log level
        }
        
        
        
    // Here's the plan, if the date/time/host is given in the line, grab & use it.
    // If there is no date/time, but the previous logLine has one, use that one because it's probably some log file that is free format
    // If you have no idea what the date is, set it to be 1/1/1970, beginning of Unix epoch time.
    // Never return a malformed string line. You can only do stuff like that when the loggers have real standards, like the kernel logs.
    // Some files record date/time but no year (mail*). Grab the year from the file access time and hope it's right.
        // Probably have to fix it up for New Year's
    
    // Keep in mind that the year, month, and date just collected are strings, while those used to create the logLine are integer

 
        // HACK: For a line w/o adequate header. Need to fix up date/time based on previous good one
        // logLinePrevious is the previous line.
        // If it has a dateTime which is good, then use it. Otherwise, it's set to Unix epoch being Jan 1, 1970

        if (!dateTime.isValid()) {
                    
            // No year, but valid QTime & date/month
            if (year == "" && month != "" && date != "" ) {
              //qDebug() << "Faking up time for year " << year << " from " << QDateTime(QDate(fileCreated.date().year(), month.toInt(),date.toInt()), QTime(0,0,0));
                dateTime = QDateTime(QDate(fileCreated.date().year(), month.toInt(), date.toInt()), QTime(0,0,0)); // Scary things at midnight
            }
            // Just makign sure Nvidia works
            else if (process == "nvidia") {
                dateTime = fileCreated;
              //qDebug() << "Forcing Nvidia to have date " << dateTime << " which is " << dateTime.isValid();
            }
            // Have valid previousDate & working time, use it.
            else if ( QTime((time83.mid(1,2)).toInt(),time83.mid(4,2).toInt(),time83.mid(7,6).toInt()).isValid() ) { 
              //qDebug() << "Doing previousDate " << previousDate;
                dateTime = previousDate;
                dateTime.setTime(QTime((time83.mid(1,2)).toInt(),time83.mid(4,2).toInt(),time83.mid(7,6).toInt()));
            }  else {
              //qDebug() << "Going back in time" ;
                dateTime = QDateTime(QDate(1970, 1, 1), QTime(0, 0, 0));
            } ;
        };
  //     else if (!dateTime().isValid() && year != "") {
//         if (QTime(match.captured(1).toInt(),match.captured(2).toInt(),match.captured(3).toInt()).isValid()) {
//           //qDebug() << "Faking up time for year " << year << " from " << QDateTime(QDate(year.toInt(), month.toInt(),date.toInt()), QTime(0,0,0));
//             dateTime = QDateTime(QDate(year.toInt(), month.toInt(), date.toInt()), QTime(match.captured(1).toInt(),match.captured(2).toInt(),match.captured(3).toInt()));
//         } else {

//         };
//     }

    }    
    
    // We need to assemble this arbitrary list plus the dateTime
    // Really bad form to use positions to conveny info
    
    // This function is defined inline in the header. Just to make sure that all priority levels look alike
  //qDebug() << "Prior to converting level, it is " << level;
    level = get_standard_level(level);
  //qDebug() << "Post converting level, it is " << level;
    QStringList list;
    list.append(hostname);
    list.append(process);
    list.append(level);
    list.append(message);
  //qDebug() << "Output list = " << list;

    /* Error levels, Priorities, LogLevels are defined in GlobalsPrivate (of course)
        enum LogLevelIds {
        EMERGENCY_LOG_LEVEL_ID = 0,
        ALERT_LOG_LEVEL_ID,
        CRITICAL_LOG_LEVEL_ID,
        ERROR_LOG_LEVEL_ID,
        WARNING_LOG_LEVEL_ID,
        NOTICE_LOG_LEVEL_ID,
        INFORMATION_LOG_LEVEL_ID,
        DEBUG_LOG_LEVEL_ID,
        NONE_LOG_LEVEL_ID,

        LOG_LEVEL_NUM
    };
    Can probably return these from GlobalsPrivate::
        LogLevel *noLogLevel;
    LogLevel *debugLogLevel;
    LogLevel *informationLogLevel;
    LogLevel *noticeLogLevel;
    LogLevel *warningLogLevel;
    LogLevel *errorLogLevel;
    LogLevel *criticalLogLevel;
    LogLevel *alertLogLevel;
    LogLevel *emergencyLogLevel;
    */
    
    // Returning results of a logLine constructor, which no doubt generates the unique internalId (not very robust)
    // dateTime format is QDate(year, monthNum, dayNum), QTime(h, m, s)
    // list is a QStringList containing hostname, process, message , most of which we don't have for these logs.
    // why we need to return the original url path is beyond me
    // level is a pointer to one of the Globals logLevels
    // logMode is, I think, a pointer to the ridiculous classes we're using to handle each log type

  
    return new LogLine(logLineInternalIdGenerator++, dateTime, list, originalFile.url().path(),
                       alevel, logMode);

}

inline LogLine *SyslogAnalyzer2::undefinedLogLine(const QString &message, const LogFile &originalFile)
{
    QStringList items;
    items << undefinedHostName() << undefinedProcess() << message;
    return new LogLine(logLineInternalIdGenerator++, QDateTime::currentDateTime(), items,
                       originalFile.url().path(), originalFile.defaultLogLevel(), logMode);
}

inline QString SyslogAnalyzer2::undefinedHostName()
{
    // i18nc("Undefined host name", "undefined");
    return QLatin1String("");
}

inline QString SyslogAnalyzer2::undefinedProcess()
{
    // i18nc("Undefined process", "undefined");
    return QLatin1String("");
}


