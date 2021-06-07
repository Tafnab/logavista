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

#ifndef _SYSLOG_ANALYZER2_H_
#define _SYSLOG_ANALYZER2_H_

#include <QString>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QDebug>

#include "fileAnalyzer.h"

#include "logFile.h"

class LogFileReader;

class LogMode;
class LogLine;

class SyslogAnalyzer2 : public FileAnalyzer
{
    Q_OBJECT

public:
    explicit SyslogAnalyzer2(LogMode *logMode);

    virtual ~SyslogAnalyzer2();

    LogViewColumns initColumns() Q_DECL_OVERRIDE;
    


                                     
    // Just a fun little function to return one of the logLevel pointers based on searching the message
    //      in cases where the log file format isn't recognized or where the message level isn't indicated in a standard way. 
    // It returns informationLogLevel if it doesn't find anything.

    inline LogLevel* level_from_message(const QString &level_message) ;
    inline QString get_standard_level(const QString &level_message);   

protected:
    LogFileReader *createLogFileReader(const LogFile &logFile) Q_DECL_OVERRIDE;
    Analyzer::LogFileSortMode logFileSortMode() Q_DECL_OVERRIDE;
    LogLine *parseMessage(const QString &logLine, const LogFile &originalFile) Q_DECL_OVERRIDE;
    // LogLine *adv_parseMessage(const QString &logLine, const LogFile &originalFile, const LogLine* logLinePrevious );
    
private:
    inline QString undefinedHostName();
    inline QString undefinedProcess();
    inline LogLine *undefinedLogLine(const QString &message, const LogFile &originalFile);
};

extern QDateTime previousDate;
extern QString previousHostName;

#endif // _SYSLOG_ANALYZER2_H_
