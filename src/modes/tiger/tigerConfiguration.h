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

#ifndef _TIGER_CONFIGURATION_H_
#define _TIGER_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class TigerConfigurationPrivate
{
public:
    QStringList tigerPaths;
};

class TigerConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    TigerConfiguration()
        : d(new TigerConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("TigerLogMode"));

        // Need only the latest security log.
        QProcess myProcess;
        // This command will only bring up the latest 1 security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/tiger/security.report.* | head -n 1 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        secfile = secfile.trimmed();


        QStringList defaultTigerPaths;
        // You have to overwrite the list if you only want the latest file
        defaultTigerPaths = QStringList(secfile.split('\n'));

        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->tigerPaths, defaultTigerPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~TigerConfiguration() { delete d; }

    QStringList tigerPaths() const { return d->tigerPaths; }

    void setTigerPaths(const QStringList &tigerPaths) { d->tigerPaths = tigerPaths; }

private:
    TigerConfigurationPrivate *const d;
};

#endif // _TIGER_CONFIGURATION_H_
