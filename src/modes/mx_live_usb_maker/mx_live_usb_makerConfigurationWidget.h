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

#ifndef _MX_LIVE_USB_MAKER_CONFIGURATION_WIDGET_H_
#define _MX_LIVE_USB_MAKER_CONFIGURATION_WIDGET_H_

#include <KLocalizedString>

#include "globals.h"
#include "logging.h"
#include "fileList.h"

#include "logLevel.h"

#include "mx_live_usb_makerConfiguration.h"
#include "mx_live_usb_makerLogMode.h"

#include "logModeConfigurationWidget.h"

class FileList;

class Mx_live_usb_makerConfigurationWidget : public LogModeConfigurationWidget
{
    Q_OBJECT

public:
    Mx_live_usb_makerConfigurationWidget()
        : LogModeConfigurationWidget(i18n("Mx_live_usb_maker"), QStringLiteral(MX_LIVE_USB_MAKER_MODE_ICON),
                                     i18n("Mx_live_usb_maker"))
    {
        QHBoxLayout *layout = new QHBoxLayout();
        this->setLayout(layout);

        fileList = new FileList(
            this, i18n("<p>These files will be analyzed to show the <b>Mx_live_usb_maker Security Logs</b>.</p>"));
        connect(fileList, &FileList::fileListChanged, this, &LogModeConfigurationWidget::configurationChanged);
        layout->addWidget(fileList);
    }

    ~Mx_live_usb_makerConfigurationWidget() {}

public slots:

    void saveConfig() Q_DECL_OVERRIDE
    {
        Mx_live_usb_makerConfiguration *mx_live_usb_makerConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(MX_LIVE_USB_MAKER_LOG_MODE_ID))
                                                       ->logModeConfiguration<Mx_live_usb_makerConfiguration *>();

        mx_live_usb_makerConfiguration->setMx_live_usb_makerPaths(fileList->paths());
    }

    void readConfig() Q_DECL_OVERRIDE
    {
        Mx_live_usb_makerConfiguration *mx_live_usb_makerConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(MX_LIVE_USB_MAKER_LOG_MODE_ID))
                                                       ->logModeConfiguration<Mx_live_usb_makerConfiguration *>();

        fileList->removeAllItems();

        fileList->addPaths(mx_live_usb_makerConfiguration->mx_live_usb_makerPaths());
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

#endif // _MX_LIVE_USB_MAKER_CONFIGURATION_WIDGET_H_
