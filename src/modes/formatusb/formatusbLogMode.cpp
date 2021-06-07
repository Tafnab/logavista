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

#include "formatusbLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

// #include "syslogAnalyzer.h"
#include "formatusbAnalyzer.h"
#include "formatusbConfigurationWidget.h"
#include "formatusbConfiguration.h"

#include "logModeItemBuilder.h"

FormatusbLogMode::FormatusbLogMode()
    : LogMode(QStringLiteral(FORMATUSB_LOG_MODE_ID), i18n("Formatusb"), QStringLiteral(FORMATUSB_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<FormatusbConfiguration>(new FormatusbConfiguration());

    d->logModeConfigurationWidget = new FormatusbConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Formatusb log /var/log/formatusb.log*"));
    d->action->setWhatsThis(i18n(
        "The Formatusb utility is used to format removable drives. This item display the log files from this utility."
        ));

    FormatusbConfiguration *configuration = logModeConfiguration<FormatusbConfiguration *>();
    checkLogFilesPresence(configuration->formatusbPaths());
}

FormatusbLogMode::~FormatusbLogMode()
{
}

Analyzer *FormatusbLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new FormatusbAnalyzer(this);
 
}

QList<LogFile> FormatusbLogMode::createLogFiles()
{
    FormatusbConfiguration *configuration = logModeConfiguration<FormatusbConfiguration *>();
    return configuration->findGenericLogFiles(configuration->formatusbPaths());
}
