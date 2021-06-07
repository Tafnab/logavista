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

#include "teamviewerLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "teamviewerConfigurationWidget.h"
#include "teamviewerConfiguration.h"

#include "logModeItemBuilder.h"

TeamviewerLogMode::TeamviewerLogMode()
    : LogMode(QStringLiteral(TEAMVIEWER_LOG_MODE_ID), i18n("Teamviewer"), QStringLiteral(TEAMVIEWER_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<TeamviewerConfiguration>(new TeamviewerConfiguration());

    d->logModeConfigurationWidget = new TeamviewerConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Teamviewer log /var/log/TeamViewer*.log*"));
    d->action->setWhatsThis(i18n(
        "Teamviewer is an optional software product which allows one user to view and control"
        " the screen of another computer. It also allows file transfers between machines. The"
        " log files keep you informed as to its activity."
        ));

    TeamviewerConfiguration *configuration = logModeConfiguration<TeamviewerConfiguration *>();
    checkLogFilesPresence(configuration->teamviewerPaths());
}

TeamviewerLogMode::~TeamviewerLogMode()
{
}

Analyzer *TeamviewerLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer2(this);
}

QList<LogFile> TeamviewerLogMode::createLogFiles()
{
    TeamviewerConfiguration *configuration = logModeConfiguration<TeamviewerConfiguration *>();
    return configuration->findGenericLogFiles(configuration->teamviewerPaths());
}
