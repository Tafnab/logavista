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

#ifndef _TRIM_CONFIGURATION_H_
#define _TRIM_CONFIGURATION_H_

#include <QStringList>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class TrimConfigurationPrivate
{
public:
    QStringList trimPaths;
};

class TrimConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    TrimConfiguration()
        : d(new TrimConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("TrimLogMode"));

        QStringList defaultTrimPaths;
        defaultTrimPaths << QStringLiteral("/var/log/trim.log");
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->trimPaths, defaultTrimPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~TrimConfiguration() { delete d; }

    QStringList trimPaths() const { return d->trimPaths; }

    void setTrimPaths(const QStringList &trimPaths) { d->trimPaths = trimPaths; }

private:
    TrimConfigurationPrivate *const d;
};

#endif // _TRIM_CONFIGURATION_H_
