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

#ifndef _POSTFIX_ANALYZER_H_
#define _POSTFIX_ANALYZER_H_

#include <KLocalizedString>
#include "syslogAnalyzer2.h"

#include "logMode.h"
#include "logging.h"

class PostfixAnalyzer : public SyslogAnalyzer2
{
    Q_OBJECT

public:
    PostfixAnalyzer(LogMode *logMode)
        : SyslogAnalyzer2(logMode)
    {
    }

    virtual ~PostfixAnalyzer() {}

    LogViewColumns initColumns() Q_DECL_OVERRIDE
    {
        LogViewColumns columns;
     columns.addColumn(LogViewColumn(i18n("Date"), true, false));
    columns.addColumn(LogViewColumn(i18n("Host"), true, true));
    columns.addColumn(LogViewColumn(i18n("Process"), true, true));
    columns.addColumn(LogViewColumn(i18n("Level"), true, true));
    columns.addColumn(LogViewColumn(i18n("Message"), true, false));
        return columns;
    }    
    
    /*
     * Just a test of multilines log lines (and it works well !)
     */
    /*
    LogLine* parseMessage(const QString& logLine, const LogFile& originalFile) {
        LogLine* syslogLine = SyslogAnalyzer::parseMessage(logLine, originalFile);

        QStringList items = syslogLine->logItems();
        QString message = items.takeLast();

        items.append(message + "\n" + message);

  logDebug() << "Coucou" << items.at(items.count()-1);

        syslogLine->setLogItems(items);
        return syslogLine;
    }
    */
};

#endif
