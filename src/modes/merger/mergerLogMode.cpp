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

#include "mergerLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

// #include "syslogAnalyzer.h"
#include "mergerAnalyzer.h"
#include "mergerConfigurationWidget.h"
#include "mergerConfiguration.h"

#include "logModeItemBuilder.h"


void updateWidget() {
        if (LogMode::merger != NULL) {
            MergerConfigurationWidget* tmp_merger = (MergerConfigurationWidget*)LogMode::merger;
            tmp_merger->appendPaths();
        }
    };

MergerLogMode::MergerLogMode()
    : LogMode(QStringLiteral(MERGER_LOG_MODE_ID), i18n("MergedLogs"), QStringLiteral(MERGER_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<MergerConfiguration>(new MergerConfiguration());

    d->logModeConfigurationWidget = new MergerConfigurationWidget();
    LogMode::merger = (LogMode*)d->logModeConfigurationWidget;

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Merger of all log types with timestamp."));
    d->action->setWhatsThis(i18n(
        "The Merge option allows you to align all available log types that have a valid timestamp and aren't too large."
        ));

    MergerConfiguration *configuration = logModeConfiguration<MergerConfiguration *>();
    checkLogFilesPresence(configuration->mergerPaths());
}

MergerLogMode::~MergerLogMode()
{
}

Analyzer *MergerLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new MergerAnalyzer(this);
 
}

QList<LogFile> MergerLogMode::createLogFiles()
{
    MergerConfiguration *configuration = logModeConfiguration<MergerConfiguration *>();
    return configuration->findGenericLogFiles(configuration->mergerPaths());
}

