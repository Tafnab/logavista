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

#include "mx_boot_repairFactory.h"

#include <QList>

#include "logMode.h"
#include "logging.h"

#include "simpleAction.h"
#include "mx_boot_repairLogMode.h"

#include "logModeFactory.h"

QList<LogMode *> Mx_boot_repairLogModeFactory::createLogModes() const
{
    QList<LogMode *> logModes;
    logModes.append(new Mx_boot_repairLogMode());
    return logModes;
}

LogModeAction *Mx_boot_repairLogModeFactory::createLogModeAction() const
{
    LogMode *logMode = Globals::instance().findLogMode(QStringLiteral(MX_BOOT_REPAIR_LOG_MODE_ID));

    if (!logMode->filesExist())
        return nullptr;

    SimpleAction *logModeAction = new SimpleAction(logMode->action(), logMode);
     logModeAction->setCategory(LogModeAction::MX_LinuxCategory);

    return logModeAction;
}
