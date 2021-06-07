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

#ifndef _CRON_ANALYZER_H_
#define _CRON_ANALYZER_H_

#include <KLocalizedString>
#include <QDebug>

#include "syslogAnalyzer.h"

#include "cronLogMode.h"
#include "cronConfiguration.h"

class LogMode;

class CronAnalyzer : public SyslogAnalyzer
{
    Q_OBJECT
private:
    inline QString undefinedHostName();
    inline QString undefinedProcess();
    inline LogLine *undefinedLogLine(const QString &message, const LogFile &originalFile);
public:
    CronAnalyzer(LogMode *logMode)
        : SyslogAnalyzer(logMode)
    {
    }

    virtual ~CronAnalyzer() {}

    LogLine *parseMessage(const QString &logLine, const LogFile &originalFile) Q_DECL_OVERRIDE;
    inline bool isCronLine(LogLine *syslogLine);
    
    LogViewColumns initColumns() Q_DECL_OVERRIDE
    {
        LogViewColumns columns;
        columns.addColumn(LogViewColumn(i18n("Date"), true, false));
        columns.addColumn(LogViewColumn(i18n("Host"), true, true));
        columns.addColumn(LogViewColumn(i18n("Process"), true, true));
        columns.addColumn(LogViewColumn(i18n("User"), true, true));
        columns.addColumn(LogViewColumn(i18n("Message"), true, true));
        //columns.addColumn(LogViewColumn(i18n("Command"), true, false));
        //columns.addColumn(LogViewColumn(i18n("User"), true, false));
        return columns;
    }

    Analyzer::LogFileSortMode logFileSortMode() Q_DECL_OVERRIDE { return Analyzer::FilteredLogFile; };

    /*
     * Cron line example :
     * Sep 16 01:39:01 localhost /USR/SBIN/CRON[11069]: (root) CMD (  [ -d /var/lib/php5 ] && find /var/lib/php5/ -type f -cmin +$(/usr/lib/php5/maxlifetime) -print0 | xargs -r -0 rm)
     * Sep 16 18:39:05 localhost /usr/sbin/cron[5479]: (CRON) INFO (pidfile fd = 3)
     * Sep 16 18:39:05 localhost /usr/sbin/cron[5480]: (CRON) STARTUP (fork ok)
     * Sep 16 18:39:05 localhost /usr/sbin/cron[5480]: (CRON) INFO (Running @reboot jobs)
     *
     */

};

#endif
