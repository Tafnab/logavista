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

#ifndef _KERNEL_ANALYZER_H_
#define _KERNEL_ANALYZER_H_

#include <QRegExp>
#include <QFile>
#include <QRegularExpression>

#include <KLocalizedString>

#include "logging.h"

#include "fileAnalyzer.h"

#include "localLogFileReader.h"
#include "processOutputLogFileReader.h"
#include "kernelLogMode.h"

class LogMode;

class KernelAnalyzer : public FileAnalyzer
{
    Q_OBJECT

public:
    KernelAnalyzer(LogMode *logMode)
        : FileAnalyzer(logMode)
    {
        startupTime();
    }

    virtual ~KernelAnalyzer() {}

    LogViewColumns initColumns() Q_DECL_OVERRIDE
    {
        LogViewColumns columns;
        columns.addColumn(LogViewColumn(i18n("Date"), true, false));
        columns.addColumn(LogViewColumn(i18n("Component"), true, false));
        columns.addColumn(LogViewColumn(i18n("Message"), true, false));

        return columns;
    }

protected:
    
       inline LogLevel* level_from_message(const QString &level_message) {
        
            if (level_message == "" || level_message.length() < 3) {Globals::instance().informationLogLevel(); };

    const QRegularExpression* pattern_emergency = new QRegularExpression(R"Q(EMERG|EMRG|Emergency[:\ ]|emergency:|\ emerg\ |\.emerg[:\.\ ])Q");
    const QRegularExpression* pattern_alert =  new QRegularExpression(R"Q(ALERT|ALRT|Alert[:\ ]|\.alert[:\.\ ])Q");
    const QRegularExpression* pattern_critical =  new QRegularExpression(R"Q(CRIT|Critical[:\ ]|\ critical\ |\.crit[\.\ ]|\.critical[:\.\ ]| PANIC[:\ ]| panic[:\ ])Q");
    const QRegularExpression* pattern_error = new  QRegularExpression(R"Q(ERR|\ Error[:\ ]|\ error\ |\ err\ |\.err[\.\ ]|\.error[:\.\ ])Q");
    const QRegularExpression* pattern_warning = new  QRegularExpression(R"Q(WARN|WRN|\ Warning[:\ ]|\ warn\ |\ warning\ |\ warning:|\.warn[\.\ ]|\.warning[:\.\ ])Q");
    const QRegularExpression* pattern_notice = new  QRegularExpression(R"Q(NOTICE|\ Notice[:\ ]|\ notice\ |\.notice[:\.\ ])Q");
    const QRegularExpression* pattern_debug = new  QRegularExpression(R"Q(DBG|DEBUG|\ Debug[:\ ]|\.debug[:\.\ ])Q");
    
    // Massive screwup in Qt
    if (level_message == "") { return(Globals::instance().informationLogLevel()); };
        
        if ((pattern_emergency->match(level_message).hasMatch())) {
            return Globals::instance().emergencyLogLevel();
        } else if ((pattern_critical->match(level_message).hasMatch())) {
            return Globals::instance().criticalLogLevel();
        } else if ((pattern_alert->match(level_message).hasMatch())) {
            return Globals::instance().alertLogLevel();
        } else if ((pattern_error->match(level_message).hasMatch())) {
            return Globals::instance().errorLogLevel();
        } else if ((pattern_warning->match(level_message).hasMatch())) {
            return Globals::instance().warningLogLevel();
        } else if ((pattern_notice->match(level_message).hasMatch())) {
            return Globals::instance().noticeLogLevel();
        } else if ((pattern_debug->match(level_message).hasMatch())) {
            return Globals::instance().debugLogLevel();
        }

        return Globals::instance().informationLogLevel();
    }    
       
    
    LogFileReader *createLogFileReader(const LogFile &logFile) Q_DECL_OVERRIDE
    {
        return new ProcessOutputLogFileReader(logFile);
    }

    Analyzer::LogFileSortMode logFileSortMode() Q_DECL_OVERRIDE { return Analyzer::AscendingSortedLogFile; }

    void startupTime()
    {
        QFile file(QStringLiteral(UPTIME_FILE));

        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&file);
        QString line = in.readLine();

        // Format : 1618.72 1382.98 (uptime / something)
        QStringList times = line.split(QStringLiteral(" "));

        QString secondsString = times.at(0);
        QString pureSecondsString = secondsString.left(secondsString.indexOf(QLatin1String(".")));
        long updateSeconds = pureSecondsString.toLong();

        startupDateTime = QDateTime::currentDateTime().addSecs(-updateSeconds);
        logDebug() << "Startup time : " << startupDateTime;
    }

    LogLine *parseMessage(const QString &logLine, const LogFile &originalLogFile) Q_DECL_OVERRIDE
    {
        QRegExp timeRegex(QStringLiteral("\\[\\ *(\\d*)\\.(\\d*)\\]\\s+(.*)"));

        //			QRegExp componentRegexp(timeRegex + "([^\\s:]{,20})[:\\s\\t]+(.*)");
        //			QRegExp messageRegexp(timeRegex + "(.*)");

        QDateTime dateTime(startupDateTime);
        QStringList messages;

        int timeExists = timeRegex.indexIn(logLine);

        // If we have the date, we are able to update the start date
        if (timeExists != -1) {
            // logDebug() << componentRegexp.cap(1).toInt() << "and" << componentRegexp.cap(2).toInt();
            dateTime = dateTime.addSecs(timeRegex.cap(1).toInt());
            dateTime = dateTime.addMSecs(timeRegex.cap(2).toInt() / 1000);

            parseComponentMessage(timeRegex.cap(3), messages);

        }
        // Else, the date will never change
        else {
            parseComponentMessage(logLine, messages);
        }

        /*
  logDebug() << "--------------------------------";
  logDebug() << logLine;
  logDebug() << "Secs : " << dateTime.time().second();
  logDebug() << "MSec : " << dateTime.time().msec();
  logDebug() << "Comp : " << messages.at(0);
  logDebug() << "Msg  : " << messages.at(1);
  logDebug() << "--------------------------------";
        */

        LogLine *line
            = new LogLine(logLineInternalIdGenerator++, dateTime, messages, originalLogFile.url().path(),
                          level_from_message(logLine), logMode);

        return line;
    }

    inline void parseComponentMessage(const QString &logLine, QStringList &messages)
    {
        QString message(logLine);
        QString component;

        int doublePointPosition = message.indexOf(QLatin1String(":"));

        // Estimate the max size of a component
        if (doublePointPosition != -1 && doublePointPosition < 20) {
            component = message.left(doublePointPosition);
            // Remove component length + ": "
            message = message.remove(0, doublePointPosition + 2);
        }

        messages.append(component);
        messages.append(message.simplified());
    }

protected:
    QDateTime startupDateTime;
};

#endif
