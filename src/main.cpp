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

#include <QApplication>
#include <QCommandLineParser>
#include <QDateTime>

#include <KAboutData>
#include <KLocalizedString>

#include "ksystemlog_version.h"
#include "mainWindow.h"
#include "logging.h"


Q_LOGGING_CATEGORY(KSYSTEMLOG, "logavista", QtWarningMsg)



int main(int argc, char **argv)
{
    // Enable debug output:
    // QLoggingCategory::setFilterRules(QStringLiteral("ksystemlog.debug = true"));

    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain("ksystemlog");

    KAboutData about(QStringLiteral("logavista"), i18n("Logavista"), QStringLiteral(KSYSTEMLOG_VERSION_STRING),
                     i18n("System Logs Viewer forked from KDE"), KAboutLicense::GPL_V2,
                     i18n("(C) 2021, J.D. Nicholson, (C) 2007-2015, Nicolas Ternisien"),
                     i18n("Do not report bugs and problems to Nicolas Ternisien. Visit https://github.com/Tafnab/logavista"),
                     QStringLiteral("https://github.com/Tafnab/logavista"), QString());

    about.setOrganizationDomain("kde.org");

    about.addAuthor(i18n("J. D. Nicholson"), i18n("Rogue Developer"),
                    QStringLiteral("Tafnab on Github.com"),
                    QStringLiteral("https://github.com/Tafnab?tab=repositories"));
    about.addAuthor(i18n("Nicolas Ternisien"), i18n("Main developer"),
                    QStringLiteral("nicolas.ternisien@gmail.com"),
                    QStringLiteral("http://www.forum-software.org"));
    about.addCredit(i18n("Bojan Djurkovic"), i18n("Log Printing"), QStringLiteral("dbojan@gmail.com"));

    KAboutData::setApplicationData(about);

    app.setApplicationName(about.componentName());
    app.setApplicationDisplayName(about.displayName());
    app.setOrganizationDomain(about.organizationDomain());
    app.setApplicationVersion(about.version());

    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("/usr/local/share/icons/logavista/Faenza-utilities-log-viewer.svg")));

    QCommandLineParser parser;
    about.setupCommandLine(&parser);
    parser.setApplicationDescription(about.shortDescription());

    // url to open
    parser.addPositionalArgument(QStringLiteral("URL"), i18n("Document to open."));

    // do the command line parsing
    parser.process(app);

    // handle standard options
    about.processCommandLine(&parser);

    // See if we are starting with session management
    if (app.isSessionRestored()) {
        RESTORE(KSystemLog::MainWindow);
    } else {
        // No session... Just start up normally

        const QStringList args = parser.positionalArguments();

        if (args.count() == 0) {
            new KSystemLog::MainWindow();
        } else {
            // KSystemLog::MainWindow* mainWindow;
            new KSystemLog::MainWindow();
            for (int i = 0; i < args.count(); i++) {
                logDebug() << "Loading file " << args.at(i);

                // TODO Implement this kind of loading
                // LogManager* firstLogManager = d->tabs->createTab();
                // d->tabs->load(Globals::instance().findLogMode("openLogMode"), firstLogManager);
                // Open log mode need to automatically find the passed url : args->url(i)
            }
        }
    }

    return app.exec();
}
