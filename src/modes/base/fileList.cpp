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

#include "fileList.h"
#include "../merger/mergerConfiguration.h"
#include "../merger/mergerConfigurationWidget.h"

#include <QListWidget>

#include <QPushButton>
#include <QDebug>

#include <kactioncollection.h>
#include <kmessagebox.h>
#include <QIcon>
#include <QMenu>
#include <QFileInfo>

#include "defaults.h"
#include "globals.h"

#include "logging.h"

FileList::FileList(QWidget *parent, const QString &descriptionText)
    : QWidget(parent)
    , fileListHelper(this)
{
    logDebug() << "Initializing file list...";

    setupUi(this);

    warningBox = new KMessageWidget(this);
    warningBox->setVisible(false);
    warningBox->setMessageType(KMessageWidget::Warning);
    warningBox->setText(i18n("Some log files do not exist.\n"
                             "If all log files are missing, this mode will be unavailable."));
    warningBox->setCloseButtonVisible(false);
    warningBox->setIcon(QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/dialog-warning.svg")));
    vboxLayout->insertWidget(1, warningBox);

    description->setText(descriptionText);

    fileListHelper.prepareButton(add, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/document-new.svg")), this, SLOT(addItem()),
                                 fileList);

    fileListHelper.prepareButton(modify, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/document-open.svg")), this,
                                 SLOT(modifyItem()), fileList);

    // Add a separator in the FileList
    QAction *separator = new QAction(this);
    separator->setSeparator(true);
    fileList->addAction(separator);

    fileListHelper.prepareButton(remove, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/list-remove-all-symbolic.svg")), this,
                                 SLOT(removeSelectedItem()), fileList);

    
    fileListHelper.prepareButton(merge, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/merge.png")), this,
                                 SLOT(mergeSelectedItem()), fileList);
    
    fileListHelper.prepareButton(up, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/go-up.svg")), this, SLOT(moveUpItem()),
                                 fileList);

    fileListHelper.prepareButton(down, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/go-down.svg")), this, SLOT(moveDownItem()),
                                 fileList);

    fileListHelper.prepareButton(removeAll, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/trash-empty.png")), this,
                                 SLOT(removeAllItems()), fileList);

    fileListHelper.prepareButton(mergeAll, QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/merge.png")), this,
                                 SLOT(mergeAllItems()), fileList);

    connect(fileList, &QListWidget::itemSelectionChanged, this, &FileList::updateButtons);
    connect(fileList, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this,
            SLOT(modifyItem(QListWidgetItem *)));
    connect(this, &FileList::fileListChanged, this, &FileList::updateButtons);
    
    // Trying to connect whatever FileList object this is to a slot on MergerLogModeWidget.
    // To that end, I have stuffed a pointer to MergerLogModeWidget (there's only one) into the base class, LogMode
    //  LogMode can't call any functions on the derived classes (no access to the data).
    //  However, MergerLogMode has a private data member that knows about MergerConfigurationWidget.
    //  So, I make the slot on MergerLogMode, which then uses the pointer at LogMode::merger (MergerConfiguartionWidget*)
    //    to call the appendPaths() member function.

    //connect(this, SIGNAL(appendMergePaths), 
    //        Globals::instance().findLogMode(QString("MergerLogMode")), SLOT(appendPaths));
    //LogMode* tmp_logmode = Globals::instance().findLogMode(QStringLiteral(MERGER_LOG_MODE_ID));
    //MergerConfigurationWidget* tmp_widget = (MergerConfigurationWidget*)tmp_logmode->merger;
    // connect(this, &FileList::appendMergePaths, tmp_logmode, &MergerLogMode::updateWidget);
    //connect(this, &FileList::appendMergePaths, &MergerConfigurationWidget::appendPaths);
    // Giving up on Qt's ability to use signals. Maybe get a new GUI library. Piece of Garbage.
    
    updateButtons();

    logDebug() << "File list initialized";
}

FileList::~FileList()
{
    
}

int FileList::count() const
{
    return fileList->count();
}

bool FileList::isEmpty() const
{
    return (fileList->count() == 0);
}

void FileList::addItem()
{
    // Open a standard Filedialog
    QList<QUrl> urls = fileListHelper.openUrls();

    QStringList paths = fileListHelper.findPaths(urls);
    foreach (const QString &path, paths) {
        fileList->addItem(path);
    }

    emit fileListChanged();
}

    void FileList::addQStringList(QStringList charlie) 
    {

    if (charlie.isEmpty()) return;
    foreach (const QString &path, charlie) {
        fileList->addItem(path);
    }

    emit fileListChanged();
    }   

void FileList::modifyItem()
{
    modifyItem(fileList->item(fileList->currentRow()));
}

void FileList::modifyItem(QListWidgetItem *item)
{
    QString previousPath = item->text();

    // Open a standard Filedialog
    QUrl url = fileListHelper.openUrl(previousPath);

    QList<QUrl> urls;
    urls.append(url);
    QStringList paths = fileListHelper.findPaths(urls);

    // We only take the first path
    if (paths.count() >= 1) {
        item->setText(paths.at(0));
    }

    emit fileListChanged();
}

void FileList::removeSelectedItem()
{
    QList<QListWidgetItem *> selectedItems = fileList->selectedItems();

    foreach (QListWidgetItem *item, selectedItems) {
        delete fileList->takeItem(fileList->row(item));
    }

    fileList->setCurrentRow(fileList->count()-1);


    emit fileListChanged();
}


void FileList::mergeSelectedItem()
{
    QList<QListWidgetItem *> selectedItems = fileList->selectedItems();
    QStringList added_files;
    foreach (QListWidgetItem *item, selectedItems) {
        MergerConfiguration::static_mergerPaths << item->text();
    }
    //qDebug() << "FileList::mergeSelectedItem complete";

}


void FileList::unselectAllItems()
{
    QList<QListWidgetItem *> selectedItems = fileList->selectedItems();
    foreach (QListWidgetItem *item, selectedItems) {
        item->setSelected(false);
    }
}

void FileList::moveItem(int direction)
{
    QList<QListWidgetItem *> selectedItems = fileList->selectedItems();

    QListWidgetItem *item = selectedItems.at(0);

    int itemIndex = fileList->row(item);

    fileList->takeItem(itemIndex);

    unselectAllItems();

    fileList->insertItem(itemIndex + direction, item);

    fileList->setCurrentRow(fileList->row(item));

    emit fileListChanged();
}

void FileList::moveUpItem()
{
    moveItem(-1);
}

void FileList::moveDownItem()
{
    moveItem(+1);
}

void FileList::removeAllItems()
{
    fileList->clear();

    emit fileListChanged();
}

void FileList::mergeAllItems()
{
    uint count = fileList->count();
    for (uint i = 0; i < count; ++i) {
        MergerConfiguration::static_mergerPaths << fileList->item(i)->text();
    };

    //qDebug() << "FileList::mergeAllItems complete";

}


void FileList::updateButtons()
{
    if (fileList->count() == 0)
        fileListHelper.setEnabledAction(removeAll, false);
    else
        fileListHelper.setEnabledAction(removeAll, true);

    QList<QListWidgetItem *> selectedItems = fileList->selectedItems();
    if (selectedItems.isEmpty() == false) {
        fileListHelper.setEnabledAction(remove, true);
        fileListHelper.setEnabledAction(merge, true);
        fileListHelper.setEnabledAction(mergeAll, true);
        fileListHelper.setEnabledAction(modify, true);

        QListWidgetItem *selection = selectedItems.at(0);

        // If the item is at the top of the list, it could not be upped anymore
        if (fileList->row(selection) == 0)
            fileListHelper.setEnabledAction(up, false);
        else
            fileListHelper.setEnabledAction(up, true);

        // If the item is at bottom of the list, it could not be downed anymore
        if (fileList->row(selection) == fileList->count() - 1)
            fileListHelper.setEnabledAction(down, false);
        else
            fileListHelper.setEnabledAction(down, true);
    }
    // If nothing is selected, disabled special buttons
    else {
        fileListHelper.setEnabledAction(remove, false);
        fileListHelper.setEnabledAction(merge, false);
        fileListHelper.setEnabledAction(modify, false);
        fileListHelper.setEnabledAction(up, false);
        fileListHelper.setEnabledAction(down, false);
    }
}

QVBoxLayout *FileList::buttonsLayout()
{
    return vboxLayout1;
}

void FileList::addPaths(const QStringList &paths)
{
    bool missingFiles = false;
    foreach (const QString &path, paths) {
        QListWidgetItem *item = new QListWidgetItem(path);
        QFileInfo checkFile(path);
        if (!checkFile.exists()) {
            item->setForeground(Qt::red);
            missingFiles = true;
        }
        fileList->addItem(item);
    }
    warningBox->setVisible(missingFiles);

    updateButtons();
}

QStringList FileList::paths()
{
    QStringList paths;
    for (int i = 0; i < fileList->count(); i++) {
        paths.append(fileList->item(i)->text());
    }

    return paths;
}
