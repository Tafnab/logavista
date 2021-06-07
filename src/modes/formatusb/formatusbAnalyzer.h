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

#ifndef _FORMATUSB_ANALYZER_H_
#define _FORMATUSB_ANALYZER_H_

#include "syslogAnalyzer2.h"

#include "formatusbLogMode.h"
#include "formatusbConfiguration.h"

class FormatusbAnalyzer : public SyslogAnalyzer2  // Need to fix this. Create MergeAnalyzer : public FileAnalyzer. Copy one of the others.
{
    Q_OBJECT

public:
    FormatusbAnalyzer(LogMode *logMode)
        : SyslogAnalyzer2(logMode)
    {
        
    }

    virtual ~FormatusbAnalyzer() {}

    // Sends in the LogFile and returns LogLine class (logLine.h) 
    LogLine *adv_parseMessage(const QString &logLine, const LogFile &originalLogFile) 
    {
        // Looks like it's just calling the Syslog parseMessage routine
        // You are passing that the logLine structure that someone else passed in
        LogLine *syslogLine = SyslogAnalyzer2::parseMessage(logLine, originalLogFile);

        // Constructing a message, probably the whole line & line number
        QString message = syslogLine->logItems().at(syslogLine->logItems().count() - 1);

        // Weird. Calling separate functions to determine if Error or Warning are present
        // If so, it calls syslogLine::setLogLevel() and passes it a freaking value from Globals::
//          if (hasErrorKeywords(message))
//              syslogLine->setLogLevel(Globals::instance().errorLogLevel());
//          else if (hasWarningKeywords(message))
//              syslogLine->setLogLevel(Globals::instance().warningLogLevel());

        return syslogLine;
    }

private:
//     bool hasWarningKeywords(const QString &message)
//     {
//         FormatusbConfiguration *configuration
//             = logMode->logModeConfiguration<FormatusbConfiguration *>();
//         return hasKeywords(message, configuration->warningKeywords());
//     }
// 
//     bool hasErrorKeywords(const QString &message)
//     {
//         FormatusbConfiguration *configuration
//             = logMode->logModeConfiguration<FormatusbConfiguration *>();
//         return hasKeywords(message, configuration->errorKeywords());
//     }

    bool hasKeywords(const QString &message, const QStringList &keywords)
    {
        foreach (const QString &keyword, keywords) {
            if (message.contains(keyword, Qt::CaseInsensitive)) {
                return true;
            }
        }

        return false;
    }
};

#endif
