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

#ifndef _MX_SNAPSHOT_CONFIGURATION_H_
#define _MX_SNAPSHOT_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class Mx_snapshotConfigurationPrivate
{
public:
    QStringList mx_snapshotPaths;
};

class Mx_snapshotConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    Mx_snapshotConfiguration()
        : d(new Mx_snapshotConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("Mx_snapshotLogMode"));

        // Need only the latest security log.
        QProcess myProcess;
        // This command will only bring up the latest security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/mx-snapshot* | head -n 1 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        secfile = secfile.trimmed();


        QStringList defaultMx_snapshotPaths;
        // You can't add to this list if you only want the latest file
        defaultMx_snapshotPaths = QStringList(secfile.split('\n'));
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->mx_snapshotPaths, defaultMx_snapshotPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~Mx_snapshotConfiguration() { delete d; }

    QStringList mx_snapshotPaths() const { return d->mx_snapshotPaths; }

    void setMx_snapshotPaths(const QStringList &mx_snapshotPaths) { d->mx_snapshotPaths = mx_snapshotPaths; }

private:
    Mx_snapshotConfigurationPrivate *const d;
};

#endif // _MX_SNAPSHOT_CONFIGURATION_H_
