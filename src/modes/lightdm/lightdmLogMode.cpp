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

#include "lightdmLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "lightdmConfigurationWidget.h"
#include "lightdmConfiguration.h"

#include "logModeItemBuilder.h"

LightdmLogMode::LightdmLogMode()
    : LogMode(QStringLiteral(LIGHTDM_LOG_MODE_ID), i18n("Lightdm"), QStringLiteral(LIGHTDM_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<LightdmConfiguration>(new LightdmConfiguration());

    d->logModeConfigurationWidget = new LightdmConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Login Screen issues: /var/log/lightdm.log"));
    d->action->setWhatsThis(i18n(
        "Examines messages from the login screen process."
        ));

    LightdmConfiguration *configuration = logModeConfiguration<LightdmConfiguration *>();
    checkLogFilesPresence(configuration->lightdmPaths());
}

LightdmLogMode::~LightdmLogMode()
{
}

Analyzer *LightdmLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer2(this);
}

QList<LogFile> LightdmLogMode::createLogFiles()
{
    LightdmConfiguration *configuration = logModeConfiguration<LightdmConfiguration *>();
    return configuration->findGenericLogFiles(configuration->lightdmPaths());
}
