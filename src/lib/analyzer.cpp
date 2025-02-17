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

#include "analyzer.h"

#include <KLocalizedString>

#include "logging.h"
#include "ksystemlogConfig.h"

#include "logViewModel.h"

#include "logMode.h"
#include "logFileReader.h"

#include "logFile.h"

Analyzer::Analyzer(LogMode *mode)
    : QObject(NULL)
    , logViewModel(NULL)
    , logMode(mode)
    , insertionLocking(QMutex::Recursive)
    , logLineInternalIdGenerator(0)
{
    parsingPaused = false;
    QDateTime previousDate = QDateTime(QDate(1970, 1, 1), QTime(0, 0, 0));
    QString previousHostName = "";
}

Analyzer::~Analyzer()
{
    // logMode is managed by Globals
    // logViewModel is managed by LogViewWidget
}

bool Analyzer::isParsingPaused() const
{
    return parsingPaused;
}

void Analyzer::setParsingPaused(bool paused)
{
    parsingPaused = paused;

    bool watching;
    // If we resume the parsing, then parse files to know if new lines have been appended.
    if (parsingPaused == true) {
        logDebug() << "Pausing reading";
        watching = false;
    } else {
        logDebug() << "Relaunch reading";
        watching = true;
    }

    watchLogFiles(watching);
}

void Analyzer::setLogViewModel(LogViewModel *logViewModel)
{
    this->logViewModel = logViewModel;
}

void Analyzer::informOpeningProgress(int currentPosition, int total)
{
    int each = total / 100;
    if (each == 0) {
        return;
    }

    if (currentPosition % each == 0) {
        emit openingProgressed();
    }
}
