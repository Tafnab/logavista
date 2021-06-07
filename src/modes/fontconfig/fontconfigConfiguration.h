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

#ifndef _FONTCONFIG_CONFIGURATION_H_
#define _FONTCONFIG_CONFIGURATION_H_

#include <QStringList>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class FontconfigConfigurationPrivate
{
public:
    QStringList fontconfigPaths;
};

class FontconfigConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    FontconfigConfiguration()
        : d(new FontconfigConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("FontconfigLogMode"));

        QStringList defaultFontconfigPaths;
        defaultFontconfigPaths << QStringLiteral("/var/log/fontconfig.log");
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->fontconfigPaths, defaultFontconfigPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~FontconfigConfiguration() { delete d; }

    QStringList fontconfigPaths() const { return d->fontconfigPaths; }

    void setFontconfigPaths(const QStringList &fontconfigPaths) { d->fontconfigPaths = fontconfigPaths; }

private:
    FontconfigConfigurationPrivate *const d;
};

#endif // _FONTCONFIG_CONFIGURATION_H_
