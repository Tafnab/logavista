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

#include "cronAnalyzer.h"
#include "syslogAnalyzer.h"

inline LogLine *CronAnalyzer::undefinedLogLine(const QString &message, const LogFile &originalFile)
{
    QStringList items;
    items << undefinedHostName() << undefinedProcess() << message;
    return new LogLine(logLineInternalIdGenerator++, QDateTime::currentDateTime(), items,
                       originalFile.url().path(), originalFile.defaultLogLevel(), logMode);
}


inline QString CronAnalyzer::undefinedHostName()
{
    // i18nc("Undefined host name", "undefined");
    return QLatin1String("");
}

inline QString CronAnalyzer::undefinedProcess()
{
    // i18nc("Undefined process", "undefined");
    return QLatin1String("");
}

    LogLine *CronAnalyzer::parseMessage(const QString &logLine, const LogFile &originalFile) 
    {
        //qDebug() << "Entering cron's parseMessage " << logLine << " from file " << originalFile.url();
        // Use the default parsing
        LogLine *syslogLine = SyslogAnalyzer::parseMessage(logLine, originalFile);

        QStringList list = syslogLine->logItems();

        // Looks like isCronLine() is broken.
        // Just going to recognize CRON and anacron
        if (!(list.at(1).indexOf("CRON") >= 0 || list.at(1).indexOf("anacron") >= 0)) {
            delete syslogLine;
            //qDebug() << "CronAnalyzer parseMessage about to return undefinedLogLine pointer";
            return NULL;
        }
        //qDebug() << "CronAnalyzer parseMessage list before additions " << list;

        // Gets the message column (last item) and deletes it
        QString message = list.takeLast();
        if (message.length() < 2) return NULL;  // Really need to clean up non-messages


        int leftBracket = message.indexOf(QLatin1Char('('));
        int rightBracket = message.indexOf(QLatin1Char(')'));
        
        // Only CRON jobs have a user in their logfile. anacron does not.
        QString user = "";
        if (list.at(1).indexOf("CRON") >= 0) user = message.mid(leftBracket + 1, rightBracket - leftBracket - 1);

        list.append(user);

/*  Going to ignore this for now. I think the original intention was to pull out the command line into a separate column
 *  Not sure what that will accomplish, since you can just search for CMD or the command yourself if you need that info.
        if (message.indexOf(QLatin1String("CMD")) != -1) {
            Ignore this : ") CMD (" (length = 7)
            message = message.right(message.length() - rightBracket - 7);
            message = message.simplified();
            syslogLine->setLogLevel(Globals::instance().informationLogLevel());
        } else {
            Ignore this : ") " (for INFO and STARTUP cases)
            message = message.right(message.length() - rightBracket - 2);
            syslogLine->setLogLevel(Globals::instance().noticeLogLevel());
        }*/
    
        list.append(message);

        syslogLine->setLogItems(list);
        syslogLine->setLogLevel(SyslogAnalyzer::level_from_message(message));

        return syslogLine;
    }

    inline bool CronAnalyzer::isCronLine(LogLine *syslogLine)
    {
        //qDebug() << "Entered CronAnalyzer isCronLine routine " << syslogLine->logItems();
        CronConfiguration *cronConfiguration = logMode->logModeConfiguration<CronConfiguration *>();

        if (cronConfiguration->processFilter().isEmpty()) {
            return true;
        }

        // If the process line does not match the cron process, then ignore this line
        const QStringList list = syslogLine->logItems();
        //qDebug() << "IN CronAnalyzer::isCronLine, list = " << list;
        //qDebug() << " --- Apparently looking for cronConfiguration->processFilter()s " << cronConfiguration->processFilter();
        QString processLine = list.at(1);
        if (processLine.contains(cronConfiguration->processFilter(), Qt::CaseInsensitive) == true) {
            return true;
        }
        //qDebug() << "CronAnalyzer isCronLine about to return false";
        return false;
    }
