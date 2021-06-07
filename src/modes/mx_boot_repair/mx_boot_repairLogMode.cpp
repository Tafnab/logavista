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

#include "mx_boot_repairLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "mx_boot_repairConfigurationWidget.h"
#include "mx_boot_repairConfiguration.h"

#include "logModeItemBuilder.h"

Mx_boot_repairLogMode::Mx_boot_repairLogMode()
    : LogMode(QStringLiteral(MX_BOOT_REPAIR_LOG_MODE_ID), i18n("Mx_boot_repair"), QStringLiteral(MX_BOOT_REPAIR_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<Mx_boot_repairConfiguration>(new Mx_boot_repairConfiguration());

    d->logModeConfigurationWidget = new Mx_boot_repairConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Mx_boot_repair logs /var/log/mx_boot_repair*"));
    d->action->setWhatsThis(i18n(
        "The mx_boot_repair tool is supplied by MX Linux. It attempts to correct problems with grub configuration and the MBR."
        " The logs from the previous runs are shown."
        ));

    Mx_boot_repairConfiguration *configuration = logModeConfiguration<Mx_boot_repairConfiguration *>();
    checkLogFilesPresence(configuration->mx_boot_repairPaths());
}

Mx_boot_repairLogMode::~Mx_boot_repairLogMode()
{
}

Analyzer *Mx_boot_repairLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    // return new SyslogAnalyzer(this);
    return new SyslogAnalyzer2(this);
}

QList<LogFile> Mx_boot_repairLogMode::createLogFiles()
{
    Mx_boot_repairConfiguration *configuration = logModeConfiguration<Mx_boot_repairConfiguration *>();
    return configuration->findGenericLogFiles(configuration->mx_boot_repairPaths());
}
