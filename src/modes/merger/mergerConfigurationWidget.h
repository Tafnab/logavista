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

#ifndef _MERGER_CONFIGURATION_WIDGET_H_
#define _MERGER_CONFIGURATION_WIDGET_H_

#include <KLocalizedString>
#include <QDebug>
#include <QThread>

#include "globals.h"
#include "logging.h"
#include "fileList.h"

#include "logLevel.h"

#include "mergerConfiguration.h"
#include "mergerLogMode.h"

#include "logModeConfigurationWidget.h"
#include <unistd.h>

class FileList;

class MergerConfigurationWidget : public LogModeConfigurationWidget
{
    Q_OBJECT
    
friend class FileList;
friend class LogMode;
friend class MergerLogMode;
    
public:
    
    QThread *thread;
    
    MergerConfigurationWidget()
        : LogModeConfigurationWidget(i18n("MergerLogs"), QStringLiteral(MERGER_MODE_ICON),
                                     i18n("MergerLogs"))
    {
        QHBoxLayout *layout = new QHBoxLayout();
        this->setLayout(layout);

        fileList = new FileList(
            this, i18n("<p>All available log types are merged into one log, provided that they have a timestamp and aren't too large.</p>"));
        connect(fileList, &FileList::fileListChanged, this, &LogModeConfigurationWidget::configurationChanged);
        layout->addWidget(fileList);

        //qDebug() << "MergerConfigurationWidget:: constructor, about to start thread";
        this->thread = QThread::create([this]{ while(true){sleep(1); if (!MergerConfiguration::static_mergerPaths.isEmpty()) this->appendPaths(); }});
        this->thread->start();
        //qDebug() << "MergerConfigurationWidget:: constructor, just started thread " << this->thread;
 
        
    }

    ~MergerConfigurationWidget() {
        this->thread->quit();
    }
 
public slots:

    void saveConfig() Q_DECL_OVERRIDE
    {
        MergerConfiguration *mergerConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(MERGER_LOG_MODE_ID))
                                                       ->logModeConfiguration<MergerConfiguration *>();


        mergerConfiguration->setMergerPaths(fileList->paths());
        
         //qDebug() << "In MergerConfigurationWidget::saveConfig()";



    }

    void readConfig() Q_DECL_OVERRIDE
    {
        // This is OO at it's finest. Grabbing the related Configuration object from a Globals object
        // because there's no way to just know it.
        MergerConfiguration *mergerConfiguration = Globals::instance()
                                                       .findLogMode(QStringLiteral(MERGER_LOG_MODE_ID))
                                                       ->logModeConfiguration<MergerConfiguration *>();
        // fileList is a private data member of this object
        // It's just a pointer, probably pointing to the actual file list contained in the control
        // that FileList creates.
                                                       // Remove everything.
                                                       //qDebug() << "In MergerConfigurationWidget::readConfig(), here's the paths we're adding from the mergerConfiguration->mergerPaths() function" << mergerConfiguration->mergerPaths();
        fileList->removeAllItems();
        fileList->addPaths(mergerConfiguration->mergerPaths());
        

        
        
        //qDebug() << "Just finished MergerConfigurationWidget::readConfig()";
    }

    void defaultConfig() Q_DECL_OVERRIDE
    {
        // TODO Find a way to read the configuration per default
        readConfig();
        //qDebug() << "MergerConfigurationWidget::defaultConfig() just readConfig()";
    }
    
        void appendPaths()
    {
        // Add the paths to the configuration & re-read the configuration
        // Make sure that the paths to add aren't empty.
        //   Empty lines give this program a lot of trouble.
        if (!MergerConfiguration::static_mergerPaths.isEmpty()) {
            //qDebug() << "Just started MergerConfiguartionWidget::appendPaths(),added " << MergerConfiguration::static_mergerPaths; 
                
            // Push the new paths onto the current list of paths
            QStringList paths = MergerConfiguration::static_mergerPaths;
            fileList->addQStringList(paths);
             
            // Reset the static_mergerPaths to an empty QStringList
            MergerConfiguration::static_mergerPaths = QStringList() ;
            saveConfig();

            //qDebug() << "done";
            } else {
            //qDebug() << "Just finished MergerConfiguartionWidget::appendPaths(),nothing to add";
            };
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

#endif // _MERGER_CONFIGURATION_WIDGET_H_
