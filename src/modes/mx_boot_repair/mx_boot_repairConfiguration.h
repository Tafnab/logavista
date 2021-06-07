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

#ifndef _MX_BOOT_REPAIR_CONFIGURATION_H_
#define _MX_BOOT_REPAIR_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class Mx_boot_repairConfigurationPrivate
{
public:
    QStringList mx_boot_repairPaths;
};

class Mx_boot_repairConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    Mx_boot_repairConfiguration()
        : d(new Mx_boot_repairConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("Mx_boot_repairLogMode"));

        // Need only the latest logs
        QProcess myProcess;
        // This command will only bring up the latest security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/mx-boot-repair* | head  \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString filelist(myProcess.readAllStandardOutput());
        filelist = filelist.trimmed();


        QStringList defaultMx_boot_repairPaths;
        // You can't add to this list if you only want the latest file
        //defaultMx_boot_repairPaths = QStringList(filelist);
        //  Trying out the split function of QString to make a QList
        defaultMx_boot_repairPaths = filelist.split('\n');
        
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->mx_boot_repairPaths, defaultMx_boot_repairPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~Mx_boot_repairConfiguration() { delete d; }

    QStringList mx_boot_repairPaths() const { return d->mx_boot_repairPaths; }

    void setMx_boot_repairPaths(const QStringList &mx_boot_repairPaths) { d->mx_boot_repairPaths = mx_boot_repairPaths; }

private:
    Mx_boot_repairConfigurationPrivate *const d;
};

#endif // _MX_BOOT_REPAIR_CONFIGURATION_H_
