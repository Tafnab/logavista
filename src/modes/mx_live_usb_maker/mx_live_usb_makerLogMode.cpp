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

#include "mx_live_usb_makerLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "mx_live_usb_makerConfigurationWidget.h"
#include "mx_live_usb_makerConfiguration.h"

#include "logModeItemBuilder.h"

Mx_live_usb_makerLogMode::Mx_live_usb_makerLogMode()
    : LogMode(QStringLiteral(MX_LIVE_USB_MAKER_LOG_MODE_ID), i18n("Mx_live_usb_maker"), QStringLiteral(MX_LIVE_USB_MAKER_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<Mx_live_usb_makerConfiguration>(new Mx_live_usb_makerConfiguration());

    d->logModeConfigurationWidget = new Mx_live_usb_makerConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Mx_live_usb_maker security audit logs /var/log/mx_live_usb_maker/security.report.*"));
    d->action->setWhatsThis(i18n(
        "The Mx_live_usb_maker UNIX security tool looks for vulnerabilities in your installed OS. The summary logs give "
        "recommendations about vulnerabilities and fixes. Other Mx_live_usb_maker logs contained in /var/log/mx_live_usb_maker are "
        " not displayed."
        ));

    Mx_live_usb_makerConfiguration *configuration = logModeConfiguration<Mx_live_usb_makerConfiguration *>();
    checkLogFilesPresence(configuration->mx_live_usb_makerPaths());
}

Mx_live_usb_makerLogMode::~Mx_live_usb_makerLogMode()
{
}

Analyzer *Mx_live_usb_makerLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer2(this);
}

QList<LogFile> Mx_live_usb_makerLogMode::createLogFiles()
{
    Mx_live_usb_makerConfiguration *configuration = logModeConfiguration<Mx_live_usb_makerConfiguration *>();
    return configuration->findGenericLogFiles(configuration->mx_live_usb_makerPaths());
}
