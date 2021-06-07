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

#ifndef _MX_BOOT_REPAIR_CONFIGURATION_WIDGET_H_
#define _MX_BOOT_REPAIR_CONFIGURATION_WIDGET_H_

#include <KLocalizedString>

#include "globals.h"
#include "logging.h"
#include "fileList.h"

#include "logLevel.h"

#include "mx_boot_repairConfiguration.h"
#include "mx_boot_repairLogMode.h"

#include "logModeConfigurationWidget.h"

class FileList;

class Mx_boot_repairConfigurationWidget : public LogModeConfigurationWidget
{
    Q_OBJECT

public:
    Mx_boot_repairConfigurationWidget()
        : LogModeConfigurationWidget(i18n("Mx_boot_repair"), QStringLiteral(MX_BOOT_REPAIR_MODE_ICON),
                                     i18n("Mx_boot_repair"))
    {
        QHBoxLayout *layout = new QHBoxLayout();
        this->setLayout(layout);

        fileList = new FileList(
            this, i18n("<p>These files will be analyzed to show the <b>Mx_boot_repair Logs</b>.</p>"));
        connect(fileList, &FileList::fileListChanged, this, &LogModeConfigurationWidget::configurationChanged);
        layout->addWidget(fileList);
    }

    ~Mx_boot_repairConfigurationWidget() {}

public slots:

    void saveConfig() Q_DECL_OVERRIDE
    {
        Mx_boot_repairConfiguration *mx_boot_repairConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(MX_BOOT_REPAIR_LOG_MODE_ID))
                                                       ->logModeConfiguration<Mx_boot_repairConfiguration *>();

        mx_boot_repairConfiguration->setMx_boot_repairPaths(fileList->paths());
    }

    void readConfig() Q_DECL_OVERRIDE
    {
        Mx_boot_repairConfiguration *mx_boot_repairConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(MX_BOOT_REPAIR_LOG_MODE_ID))
                                                       ->logModeConfiguration<Mx_boot_repairConfiguration *>();

        fileList->removeAllItems();

        fileList->addPaths(mx_boot_repairConfiguration->mx_boot_repairPaths());
    }

    void defaultConfig() Q_DECL_OVERRIDE
    {
        // TODO Find a way to read the configuration per default
        readConfig();
    }

protected:
    bool isValid() const Q_DECL_OVERRIDE
    {
        if (fileList->isEmpty() == false) {
            return true;
        }

        return false;
    }

private:
    FileList *fileList;
};

#endif // _MX_BOOT_REPAIR_CONFIGURATION_WIDGET_H_
