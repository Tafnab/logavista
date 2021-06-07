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

#ifndef _POWERLOGS_CONFIGURATION_H_
#define _POWERLOGS_CONFIGURATION_H_

#include <QStringList>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class PowerlogsConfigurationPrivate
{
public:
    QStringList powerlogsPaths;
};

class PowerlogsConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    PowerlogsConfiguration()
        : d(new PowerlogsConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("PowerlogsLogMode"));

        QStringList defaultPowerlogsPaths;
        defaultPowerlogsPaths << QStringLiteral("/var/log/sleep.log");
		defaultPowerlogsPaths << QStringLiteral("/var/log/hibernate.log");
		defaultPowerlogsPaths << QStringLiteral("/var/log/pm-suspend.log");
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->powerlogsPaths, defaultPowerlogsPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~PowerlogsConfiguration() { delete d; }

    QStringList powerlogsPaths() const { return d->powerlogsPaths; }

    void setPowerlogsPaths(const QStringList &powerlogsPaths) { d->powerlogsPaths = powerlogsPaths; }

private:
    PowerlogsConfigurationPrivate *const d;
};

#endif // _POWERLOGS_CONFIGURATION_H_
