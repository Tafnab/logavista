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

#ifndef _FORMATUSB_CONFIGURATION_H_
#define _FORMATUSB_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"

class FormatusbConfigurationPrivate
{
public:
    QStringList formatusbPaths;
};

class FormatusbConfiguration : public LogModeConfiguration
{
    Q_OBJECT

public:
    FormatusbConfiguration()
        : d(new FormatusbConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("FormatusbLogMode"));

        // Need only the latest security log.
        QProcess myProcess;
        // This command will only bring up the latest 1 security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/formatusb.log.* | head -n 2 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        //qDebug() << "FormatusbConfiguration secfile " << secfile;
        secfile = secfile.trimmed();


        // QStringList defaultFormatusbPaths;
        // You have to overwrite the list if you only want the latest file
        // defaultFormatusbPaths = QStringList(secfile);
        
		 QStringList defaultFormatusbPaths;
        // You can't add to this list if you only want the latest file
        defaultFormatusbPaths = QStringList(secfile.split('\n'));
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->formatusbPaths, defaultFormatusbPaths,
                                         QStringLiteral("LogFilesPaths"));
    }

    virtual ~FormatusbConfiguration() { delete d; }

    QStringList formatusbPaths() const { return d->formatusbPaths; }

    void setFormatusbPaths(const QStringList &formatusbPaths) { d->formatusbPaths = formatusbPaths; }

private:
    FormatusbConfigurationPrivate *const d;
};

#endif // _FORMATUSB_CONFIGURATION_H_
