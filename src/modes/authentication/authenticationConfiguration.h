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

#ifndef _AUTHENTICATION_CONFIGURATION_H_
#define _AUTHENTICATION_CONFIGURATION_H_

#include <QStringList>
#include <QString>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class AuthenticationConfigurationPrivate
{
public:
    QStringList authenticationPaths;
};

class AuthenticationConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    AuthenticationConfiguration()
        : d(new AuthenticationConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("AuthenticationLogMode"));

        // Need only the latest security log.
        QProcess myProcess;
        // This command will only bring up the latest 3 authentications logs, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/auth.log.* | head -n 3 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        secfile = secfile.trimmed();
        
		// QStringList defaultAuthenticationPaths = QStringList(secfile.split('\n'));
        // Push the new files onto the default*Paths using <<, otherwise they will be ignored
//         for (auto i = 0; i < default_files.length(); i++) {
//             defaultAuthenticationPaths << default_files[i];
//         }
         QStringList defaultAuthenticationPaths; 
         defaultAuthenticationPaths << QString("/var/log/auth.log") << QString("/var/log/auth.log.1") << QString("/var/log/auth.log.2.gz");

        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->authenticationPaths, defaultAuthenticationPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~AuthenticationConfiguration() { delete d; }

    QStringList authenticationPaths() const { return d->authenticationPaths; }

    void setAuthenticationPaths(const QStringList &authenticationPaths) { d->authenticationPaths = authenticationPaths; }

private:
    AuthenticationConfigurationPrivate *const d;
};

#endif // _AUTHENTICATION_CONFIGURATION_H_
