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

#include "firewallLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer.h"
#include "firewallConfigurationWidget.h"
#include "firewallConfiguration.h"

#include "logModeItemBuilder.h"

FirewallLogMode::FirewallLogMode()
    : LogMode(QStringLiteral(FIREWALL_LOG_MODE_ID), i18n("Firewall"), QStringLiteral(FIREWALL_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<FirewallConfiguration>(new FirewallConfiguration());

    d->logModeConfigurationWidget = new FirewallConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Firewall log ufw.log"));
    d->action->setWhatsThis(i18n(
        "Examine logs from the Uncomplicated Firewall program to determine what is being reported."
        ));

    FirewallConfiguration *configuration = logModeConfiguration<FirewallConfiguration *>();
    checkLogFilesPresence(configuration->firewallPaths());
}

FirewallLogMode::~FirewallLogMode()
{
}

Analyzer *FirewallLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer(this);
}

QList<LogFile> FirewallLogMode::createLogFiles()
{
    FirewallConfiguration *configuration = logModeConfiguration<FirewallConfiguration *>();
    return configuration->findGenericLogFiles(configuration->firewallPaths());
}
