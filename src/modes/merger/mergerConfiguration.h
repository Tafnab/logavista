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

#ifndef _MERGER_CONFIGURATION_H_
#define _MERGER_CONFIGURATION_H_

#include <QStringList>
#include <QProcess>
#include <QDebug>
#include <QVector>

#include "logModeConfiguration.h"

#include "logging.h"
#include "defaults.h"

#include "ksystemlogConfig.h"



class MergerConfigurationPrivate
{


public:
    QStringList mergerPaths;
};

class MergerConfiguration : public LogModeConfiguration
{
    Q_OBJECT
    
    

friend class FileList;


public:
    
 
    static inline QStringList static_mergerPaths;   
    
    static inline QStringList mergerAddedPaths;
    
    QStringList mergerPaths() const { return d->mergerPaths;}

    void setMergerPaths(const QStringList &mergerPaths) { 
        d->mergerPaths = mergerPaths;
        static_mergerPaths = QStringList();
    };
    //void setFormatusbPaths(const QStringList &formatusbPaths) { d->formatusbPaths = formatusbPaths; }
   
    
    MergerConfiguration() :
        d(new MergerConfigurationPrivate())
    {
        configuration->setCurrentGroup(QStringLiteral("MergerLogMode"));

        mergerAddedPaths = QStringList(); 
        // QStringList defaultMergerPaths;
        // You have to overwrite the list if you only want the latest file
        // defaultMergerPaths = QStringList(secfile);
        
        // Here's the example of what gets pushed onto the objects configuration
        //defaultMergerPaths = QStringList(QStringLiteral("Files"));
        //configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->mergerPaths, defaultMergerPaths,
        //                                 QStringLiteral("LogFilesPaths"));
        // Need only the latest 2 formatusb log.
        QProcess myProcess;
        // This command will only bring up the latest 1 security log, introduces dependence on utility "head"
        QString Command = "/bin/bash -c \"ls -t /var/log/syslog.* | head -n 2 \"";
        myProcess.start(Command);
        myProcess.waitForFinished();
        QString secfile(myProcess.readAllStandardOutput());
        qDebug() << "MergerConfiguration secfile " << secfile;
        secfile = secfile.trimmed();  // trailing newline messes things up tremendously
        
        QStringList defaultMergerPaths;      
        defaultMergerPaths = QStringList(secfile.split('\n'));
 
        // You can't add to this list if you only want the latest file
        configuration->addItemStringList(QStringLiteral("LogFilesPaths"), d->mergerPaths, defaultMergerPaths,
                                         QStringLiteral("LogFilesPaths"));
        

        
        
    }

    virtual ~MergerConfiguration() { }

 

private:
    MergerConfigurationPrivate *const d;
};

#endif // _MERGER_CONFIGURATION_H_
