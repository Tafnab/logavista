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

#ifndef _POSTFIX_CONFIGURATION_H_
#define _POSTFIX_CONFIGURATION_H_

#include <QStringList>
#include <QList>

#include "genericConfiguration.h"
#include "globals.h"
#include "defaults.h"

#include "postfixLogMode.h"

class PostfixConfiguration : public GenericLogModeConfiguration
{
    Q_OBJECT

public:
    PostfixConfiguration()
        : GenericLogModeConfiguration(
              QStringLiteral(POSTFIX_LOG_MODE_ID),
              QStringList() << QStringLiteral("/var/log/mail.log") << QStringLiteral("/var/log/mail.info")
                            << QStringLiteral("/var/log/mail.warn") << QStringLiteral("/var/log/mail.err")
                            << QStringLiteral("/var/log/mail.log.1") << QStringLiteral("/var/log/mail.info.1")
                            << QStringLiteral("/var/log/mail.warn.1") << QStringLiteral("/var/log/mail.err.1")
                            << QStringLiteral("/var/log/mail.log.2.gz") << QStringLiteral("/var/log/mail.info.2.gz")
                            << QStringLiteral("/var/log/mail.warn.2.gz") << QStringLiteral("/var/log/mail.err.2.gz"),
              QList<int>() << Globals::NOTICE_LOG_LEVEL_ID << Globals::INFORMATION_LOG_LEVEL_ID << Globals::WARNING_LOG_LEVEL_ID
                           << Globals::ERROR_LOG_LEVEL_ID)
    {
    }

    virtual ~PostfixConfiguration() {}
};

#endif // _POSTFIX_CONFIGURATION_H_
