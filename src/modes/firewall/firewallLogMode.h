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

#ifndef _FIREWALL_LOG_MODE_H_
#define _FIREWALL_LOG_MODE_H_

/**
 * Firewall Log Mode Identifier
 */
#define FIREWALL_LOG_MODE_ID "firewallLogMode"

/**
 * Firewall Log Icon
 */
#define FIREWALL_MODE_ICON "/usr/local/share/icons/logavista/gufw.svg"

#include <QList>

#include "logging.h"
#include "logMode.h"

#include "syslogAnalyzer.h"
#include "firewallConfigurationWidget.h"
#include "firewallConfiguration.h"

#include "logModeItemBuilder.h"

class FirewallLogMode : public LogMode
{
    Q_OBJECT

public:
    explicit FirewallLogMode();

    ~FirewallLogMode();

    Analyzer *createAnalyzer(const QVariant &options = QVariant()) Q_DECL_OVERRIDE;

    QList<LogFile> createLogFiles() Q_DECL_OVERRIDE;
};

#endif // _FIREWALL_LOG_MODE_H_
