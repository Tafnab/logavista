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

#ifndef _FIREWALL_CONFIGURATION_H_
#define _FIREWALL_CONFIGURATION_H_

#include <QStringList>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class FirewallConfigurationPrivate
{
public:
    QStringList firewallPaths;
};

class FirewallConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    FirewallConfiguration()
        : d(new FirewallConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("FirewallLogMode"));

        QStringList defaultFirewallPaths;
        defaultFirewallPaths << QStringLiteral("/var/log/ufw.log");
        defaultFirewallPaths << QStringLiteral("/var/log/ufw.log.1");
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->firewallPaths, defaultFirewallPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~FirewallConfiguration() { delete d; }

    QStringList firewallPaths() const { return d->firewallPaths; }

    void setFirewallPaths(const QStringList &firewallPaths) { d->firewallPaths = firewallPaths; }

private:
    FirewallConfigurationPrivate *const d;
};

#endif // _FIREWALL_CONFIGURATION_H_
