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

#include "authenticationLogMode.h"

#include <QList>

#include <KLocalizedString>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer.h"
#include "authenticationConfigurationWidget.h"
#include "authenticationConfiguration.h"

#include "logModeItemBuilder.h"

AuthenticationLogMode::AuthenticationLogMode()
    : LogMode(QStringLiteral(AUTHENTICATION_LOG_MODE_ID), i18n("Authentication"), QStringLiteral(AUTHENTICATION_MODE_ICON))
{
    d->logModeConfiguration = QSharedPointer<AuthenticationConfiguration>(new AuthenticationConfiguration());

    d->logModeConfigurationWidget = new AuthenticationConfigurationWidget();

    d->itemBuilder = new LogModeItemBuilder();

    d->action = createDefaultAction();
    d->action->setToolTip(i18n("Authentication security audit logs /var/log/authentication/security.report.*"));
    d->action->setWhatsThis(i18n(
        "The Authentication UNIX security tool looks for vulnerabilities in your installed OS. The summary logs give "
        "recommendations about vulnerabilities and fixes. Other Authentication logs contained in /var/log/authentication are "
        " not displayed."
        ));

    AuthenticationConfiguration *configuration = logModeConfiguration<AuthenticationConfiguration *>();
    checkLogFilesPresence(configuration->authenticationPaths());
}

AuthenticationLogMode::~AuthenticationLogMode()
{
}

Analyzer *AuthenticationLogMode::createAnalyzer(const QVariant &options)
{
    Q_UNUSED(options)
    return new SyslogAnalyzer(this);
}

QList<LogFile> AuthenticationLogMode::createLogFiles()
{
    AuthenticationConfiguration *configuration = logModeConfiguration<AuthenticationConfiguration *>();
    return configuration->findGenericLogFiles(configuration->authenticationPaths());
}
