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

#include "nvidiaLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "nvidiaConfigurationWidget.h"
#include "nvidiaConfiguration.h"

#include "logModeItemBuilder.h"

NvidiaLogMode::NvidiaLogMode()
    : LogMode(QStringLiteral(NVIDIA_LOG_MODE_ID), i18n("Nvidia"), QStringLiteral(NVIDIA_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<NvidiaConfiguration>(new NvidiaConfiguration());

    d->logModeConfigurationWidget = new NvidiaConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Nvidia log /var/log/ddm.log"));
    d->action->setWhatsThis(i18n(
        "The Nvidia driver installation and operation occurs if you have an NVidia graphics device."
        " This tab displays the log files from the operation of the driver and/or installation package."
        ));

    NvidiaConfiguration *configuration = logModeConfiguration<NvidiaConfiguration *>();
    checkLogFilesPresence(configuration->nvidiaPaths());
}

NvidiaLogMode::~NvidiaLogMode()
{
}

Analyzer *NvidiaLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer2(this);
}

QList<LogFile> NvidiaLogMode::createLogFiles()
{
    NvidiaConfiguration *configuration = logModeConfiguration<NvidiaConfiguration *>();
    return configuration->findGenericLogFiles(configuration->nvidiaPaths());
}
