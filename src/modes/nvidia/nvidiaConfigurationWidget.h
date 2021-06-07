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

#ifndef _NVIDIA_CONFIGURATION_WIDGET_H_
#define _NVIDIA_CONFIGURATION_WIDGET_H_

#include <KLocalizedString>

#include "globals.h"
#include "logging.h"
#include "fileList.h"

#include "logLevel.h"

#include "nvidiaConfiguration.h"
#include "nvidiaLogMode.h"

#include "logModeConfigurationWidget.h"

class FileList;

class NvidiaConfigurationWidget : public LogModeConfigurationWidget
{
    Q_OBJECT

public:
    NvidiaConfigurationWidget()
        : LogModeConfigurationWidget(i18n("Nvidia"), QStringLiteral(NVIDIA_MODE_ICON),
                                     i18n("Nvidia"))
    {
        QHBoxLayout *layout = new QHBoxLayout();
        this->setLayout(layout);

        fileList = new FileList(
            this, i18n("<p>These files will be analyzed to show the <b>Nvidia Logs</b>.</p>"));
        connect(fileList, &FileList::fileListChanged, this, &LogModeConfigurationWidget::configurationChanged);
        layout->addWidget(fileList);
    }

    ~NvidiaConfigurationWidget() {}

public slots:

    void saveConfig() Q_DECL_OVERRIDE
    {
        NvidiaConfiguration *nvidiaConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(NVIDIA_LOG_MODE_ID))
                                                       ->logModeConfiguration<NvidiaConfiguration *>();

        nvidiaConfiguration->setNvidiaPaths(fileList->paths());
    }

    void readConfig() Q_DECL_OVERRIDE
    {
        NvidiaConfiguration *nvidiaConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(NVIDIA_LOG_MODE_ID))
                                                       ->logModeConfiguration<NvidiaConfiguration *>();

        fileList->removeAllItems();

        fileList->addPaths(nvidiaConfiguration->nvidiaPaths());
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

#endif // _NVIDIA_CONFIGURATION_WIDGET_H_
