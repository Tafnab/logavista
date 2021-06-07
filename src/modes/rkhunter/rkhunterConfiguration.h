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

#ifndef _RKHUNTER_CONFIGURATION_H_
#define _RKHUNTER_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class RkhunterConfigurationPrivate
{
public:
    QStringList rkhunterPaths;
};

class RkhunterConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    RkhunterConfiguration()
        : d(new RkhunterConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("RkhunterLogMode"));

        // Need only the latest logs
        QProcess myProcess;
        // This command will only bring up the latest security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/mx_boot_repair* | head -n 3 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString filelist(myProcess.readAllStandardOutput());
        filelist = filelist.trimmed();


        QStringList defaultRkhunterPaths;
        // You can't add to this list if you only want the latest file
        //defaultMx_boot_repairPaths = QStringList(filelist);
        //  Trying out the split function of QString to make a QList
        defaultRkhunterPaths = filelist.split('\n');
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->rkhunterPaths, defaultRkhunterPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~RkhunterConfiguration() { delete d; }

    QStringList rkhunterPaths() const { return d->rkhunterPaths; }

    void setRkhunterPaths(const QStringList &rkhunterPaths) { d->rkhunterPaths = rkhunterPaths; }

private:
    RkhunterConfigurationPrivate *const d;
};

#endif // _RKHUNTER_CONFIGURATION_H_
