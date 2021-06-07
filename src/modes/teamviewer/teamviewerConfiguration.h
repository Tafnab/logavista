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

#ifndef _TEAMVIEWER_CONFIGURATION_H_
#define _TEAMVIEWER_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class TeamviewerConfigurationPrivate
{
public:
    QStringList teamviewerPaths;
};

class TeamviewerConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    TeamviewerConfiguration()
        : d(new TeamviewerConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("TeamviewerLogMode"));

        // Need only the latest security log.
        QProcess myProcess;
        // This command will only bring up the latest 1 security log, introduces dependence on utility "head"
        // QString Command = "/bin/bash -c \"ls -t /var/log/teamviewer*/TeamViewer*_Logfile.log | head \"";
        QString Command = "/bin/bash -c \"find -L /var/log/teamviewer* -name '*_*.log' -print \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        secfile = secfile.trimmed();


        // QStringList defaultTeamviewerPaths;
        // You have to overwrite the list if you only want the latest file
        // defaultTeamviewerPaths = QStringList(secfile);


		 QStringList defaultTeamviewerPaths;
        // You can't add to this list if you only want the latest file
        defaultTeamviewerPaths = QStringList(secfile.split('\n'));
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->teamviewerPaths, defaultTeamviewerPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~TeamviewerConfiguration() { delete d; }

    QStringList teamviewerPaths() const { return d->teamviewerPaths; }

    void setTeamviewerPaths(const QStringList &teamviewerPaths) { d->teamviewerPaths = teamviewerPaths; }

private:
    TeamviewerConfigurationPrivate *const d;
};

#endif // _TEAMVIEWER_CONFIGURATION_H_
