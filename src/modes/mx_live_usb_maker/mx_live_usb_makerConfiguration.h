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

#ifndef _MX_LIVE_USB_MAKER_CONFIGURATION_H_
#define _MX_LIVE_USB_MAKER_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class Mx_live_usb_makerConfigurationPrivate
{
public:
    QStringList mx_live_usb_makerPaths;
};

class Mx_live_usb_makerConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    Mx_live_usb_makerConfiguration()
        : d(new Mx_live_usb_makerConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("Mx_live_usb_makerLogMode"));

        // Need only the latest security log.
        QProcess myProcess;
        // This command will only bring up the latest security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/mx-live-usb-maker* | head -n 1 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        secfile = secfile.trimmed();

        QStringList defaultMx_live_usb_makerPaths;
        // You can't add to this list if you only want the latest file
        defaultMx_live_usb_makerPaths = QStringList(secfile);
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->mx_live_usb_makerPaths, defaultMx_live_usb_makerPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~Mx_live_usb_makerConfiguration() { delete d; }

    QStringList mx_live_usb_makerPaths() const { return d->mx_live_usb_makerPaths; }

    void setMx_live_usb_makerPaths(const QStringList &mx_live_usb_makerPaths) { d->mx_live_usb_makerPaths = mx_live_usb_makerPaths; }

private:
    Mx_live_usb_makerConfigurationPrivate *const d;
};

#endif // _MX_LIVE_USB_MAKER_CONFIGURATION_H_
