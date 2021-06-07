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

#ifndef _SYSTEM_CONFIGURATION_WIDGET_H_
#define _SYSTEM_CONFIGURATION_WIDGET_H_

#include "logModeConfigurationWidget.h"

#include <QVBoxLayout>

#include <KLocalizedString>

#include "globals.h"
#include "logging.h"

#include "logLevelFileList.h"

#include "logLevel.h"

#include "systemConfiguration.h"

#include "systemLogMode.h"

class SystemConfigurationWidget : public LogModeConfigurationWidget
{
    Q_OBJECT

public:
    SystemConfigurationWidget()
        : LogModeConfigurationWidget(i18n("System Log"), QStringLiteral(SYSTEM_MODE_ICON), i18n("System Log"))
    {
        QVBoxLayout *layout = new QVBoxLayout();
        this->setLayout(layout);

        QString description = i18n("<p>These files will be analyzed to show the <b>System logs</b>.</p>");

        fileList = new LogLevelFileList(this, description);

        connect(fileList, &FileList::fileListChanged, this, &LogModeConfigurationWidget::configurationChanged);

        layout->addWidget(fileList);
    }

    virtual ~SystemConfigurationWidget() {}

    bool isValid() const Q_DECL_OVERRIDE
    {
        if (fileList->isEmpty() == false) {
            logDebug() << "System configuration valid";
            return true;
        }

        logDebug() << "System configuration not valid";
        return false;
    }

    void saveConfig() Q_DECL_OVERRIDE
    {
        logDebug() << "Saving config from System Options...";

        SystemConfiguration *systemConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(SYSTEM_LOG_MODE_ID))
                                                       ->logModeConfiguration<SystemConfiguration *>();
        systemConfiguration->setLogFilesPaths(fileList->paths());
        systemConfiguration->setLogFilesLevels(fileList->levels());
    }

    void readConfig() Q_DECL_OVERRIDE
    {
        SystemConfiguration *systemConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(SYSTEM_LOG_MODE_ID))
                                                       ->logModeConfiguration<SystemConfiguration *>();

        fileList->removeAllItems();

        fileList->addPaths(systemConfiguration->logFilesPaths(), systemConfiguration->logFilesLevels());
    }

    void defaultConfig() Q_DECL_OVERRIDE
    {
        // TODO Find a way to read the configuration per default
        readConfig();
    }

private:
    LogLevelFileList *fileList;
};

#endif // _SYSTEM_CONFIGURATION_WIDGET_H_
