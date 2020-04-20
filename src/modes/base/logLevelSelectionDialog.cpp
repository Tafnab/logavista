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

#include "logLevelSelectionDialog.h"

#include <QPushButton>

#include <kstandardguiitem.h>

LogLevelSelectionDialog::LogLevelSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setIcon(KStandardGuiItem::ok().icon());

    QPushButton *cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    cancelButton->setIcon(KStandardGuiItem::cancel().icon());
}

LogLevelSelectionDialog::~LogLevelSelectionDialog()
{
}

QListWidget *LogLevelSelectionDialog::logLevels() const
{
    return logLevelsList;
}
