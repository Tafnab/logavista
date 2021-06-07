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

#include "mx_snapshotLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "mx_snapshotConfigurationWidget.h"
#include "mx_snapshotConfiguration.h"

#include "logModeItemBuilder.h"

Mx_snapshotLogMode::Mx_snapshotLogMode()
    : LogMode(QStringLiteral(MX_SNAPSHOT_LOG_MODE_ID), i18n("Mx_snapshot"), QStringLiteral(MX_SNAPSHOT_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<Mx_snapshotConfiguration>(new Mx_snapshotConfiguration());

    d->logModeConfigurationWidget = new Mx_snapshotConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Mx_snapshot security audit logs /var/log/mx_snapshot/security.report.*"));
    d->action->setWhatsThis(i18n(
        "The Mx_snapshot UNIX security tool looks for vulnerabilities in your installed OS. The summary logs give "
        "recommendations about vulnerabilities and fixes. Other Mx_snapshot logs contained in /var/log/mx_snapshot are "
        " not displayed."
        ));

    Mx_snapshotConfiguration *configuration = logModeConfiguration<Mx_snapshotConfiguration *>();
    checkLogFilesPresence(configuration->mx_snapshotPaths());
}

Mx_snapshotLogMode::~Mx_snapshotLogMode()
{
}

Analyzer *Mx_snapshotLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer2(this);
}

QList<LogFile> Mx_snapshotLogMode::createLogFiles()
{
    Mx_snapshotConfiguration *configuration = logModeConfiguration<Mx_snapshotConfiguration *>();
    return configuration->findGenericLogFiles(configuration->mx_snapshotPaths());
}
