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

#ifndef _TEAMVIEWER_LOG_MODE_H_
#define _TEAMVIEWER_LOG_MODE_H_

/**
 * Teamviewer Log Mode Identifier
 */
#define TEAMVIEWER_LOG_MODE_ID "teamviewerLogMode"

/**
 * Teamviewer Log Icon
 */
#define TEAMVIEWER_MODE_ICON "/usr/local/share/icons/logavista/teamviewer.svg"

#include <QList>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer2.h"
#include "teamviewerConfigurationWidget.h"
#include "teamviewerConfiguration.h"

#include "logModeItemBuilder.h"

class TeamviewerLogMode : public LogMode
{
    Q_OBJECT

public:
    explicit TeamviewerLogMode();

    ~TeamviewerLogMode();

    Analyzer *createAnalyzer(const QVariant &options = QVariant()) Q_DECL_OVERRIDE;

    QList<LogFile> createLogFiles() Q_DECL_OVERRIDE;
};

#endif // _TEAMVIEWER_LOG_MODE_H_
