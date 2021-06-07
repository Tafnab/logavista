#include <klocalizedstring.h>

/********************************************************************************
** Form generated from reading UI file 'fileListBase.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILELISTBASE_H
#define UI_FILELISTBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileListBase
{
public:
    QAction *addAction;
    QVBoxLayout *vboxLayout;
    QLabel *description;
    QGroupBox *filesBox;
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout1;
    QPushButton *add;
    QPushButton *modify;
    QPushButton *remove;
    QPushButton *removeAll;
    QPushButton *merge;
    QPushButton *mergeAll;
    QPushButton *up;
    QPushButton *down;
    QSpacerItem *spacerItem;
    QLabel *notes;
    QListWidget *fileList;

    void setupUi(QWidget *FileListBase)
    {
        if (FileListBase->objectName().isEmpty())
            FileListBase->setObjectName(QStringLiteral("FileListBase"));
        FileListBase->resize(487, 476);
        FileListBase->setBaseSize(QSize(200, 400));
        addAction = new QAction(FileListBase);
        addAction->setObjectName(QStringLiteral("addAction"));
        vboxLayout = new QVBoxLayout(FileListBase);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, -1);
        description = new QLabel(FileListBase);
        description->setObjectName(QStringLiteral("description"));
        description->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        description->setWordWrap(true);

        vboxLayout->addWidget(description);

        filesBox = new QGroupBox(FileListBase);
        filesBox->setObjectName(QStringLiteral("filesBox"));
        gridLayout = new QGridLayout(filesBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QStringLiteral("vboxLayout1"));
        add = new QPushButton(filesBox);
        add->setObjectName(QStringLiteral("add"));

        vboxLayout1->addWidget(add);

        modify = new QPushButton(filesBox);
        modify->setObjectName(QStringLiteral("modify"));

        vboxLayout1->addWidget(modify);

        remove = new QPushButton(filesBox);
        remove->setObjectName(QStringLiteral("remove"));

        vboxLayout1->addWidget(remove);

        removeAll = new QPushButton(filesBox);
        removeAll->setObjectName(QStringLiteral("removeAll"));

        vboxLayout1->addWidget(removeAll);

        merge = new QPushButton(filesBox);
        merge->setObjectName(QStringLiteral("merge"));

        vboxLayout1->addWidget(merge);

        mergeAll = new QPushButton(filesBox);
        mergeAll->setObjectName(QStringLiteral("mergeAll"));

        vboxLayout1->addWidget(mergeAll);

        up = new QPushButton(filesBox);
        up->setObjectName(QStringLiteral("up"));
        up->setEnabled(true);

        vboxLayout1->addWidget(up);

        down = new QPushButton(filesBox);
        down->setObjectName(QStringLiteral("down"));

        vboxLayout1->addWidget(down);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        vboxLayout1->addItem(spacerItem);


        gridLayout->addLayout(vboxLayout1, 0, 1, 1, 1);

        notes = new QLabel(filesBox);
        notes->setObjectName(QStringLiteral("notes"));
        notes->setWordWrap(true);

        gridLayout->addWidget(notes, 1, 0, 1, 2);

        fileList = new QListWidget(filesBox);
        fileList->setObjectName(QStringLiteral("fileList"));
        fileList->setContextMenuPolicy(Qt::ActionsContextMenu);
        fileList->setDragDropMode(QAbstractItemView::InternalMove);

        gridLayout->addWidget(fileList, 0, 0, 1, 1);


        vboxLayout->addWidget(filesBox);


        retranslateUi(FileListBase);

        QMetaObject::connectSlotsByName(FileListBase);
    } // setupUi

    void retranslateUi(QWidget *FileListBase)
    {
        addAction->setText(tr2i18n("add", nullptr));
        description->setText(tr2i18n("File List Description", nullptr));
        filesBox->setTitle(tr2i18n("Log Files", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        add->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Choose a new file</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        add->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Opens a dialog box to choose a new file to be added to the list.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        add->setText(tr2i18n("&Add File...", nullptr));
        modify->setText(tr2i18n("&Modify File...", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        remove->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Delete the current file(s)</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        remove->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Deletes the files selected on the list.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        remove->setText(tr2i18n("&Remove", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        removeAll->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Remove all files</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        removeAll->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Remove all the files on the list, even if they are not selected.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        removeAll->setText(tr2i18n("Rem&ove All", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        merge->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Delete the current file(s)</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        merge->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Deletes the files selected on the list.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        merge->setText(tr2i18n("&Merge", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        mergeAll->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Remove all files</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        mergeAll->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Remove all the files on the list, even if they are not selected.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        mergeAll->setText(tr2i18n("Mer&ge All", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        up->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Move up the current file(s)</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        up->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Moves the selected files up in the list. This option allows the files to be read <span style=\" font-weight:600;\">in first</span> by KSystemLog.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        up->setText(tr2i18n("Move &Up", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        down->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Move down the current file(s)</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        down->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Moves the selected files down in the list. This option allows the files to be read <span style=\" font-weight:600;\">in last</span> by KSystemLog.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        down->setText(tr2i18n("Move &Down", nullptr));
        notes->setText(tr2i18n("<p style='margin-top:0px;margin-bottom:0px;'><b>Notes:</b></p><ul style='margin-top:0px'><li>Files are read using the order of this list.</li><li>Compressed and plain text files are accepted <i>(*.log, *.gz, *.bz2,...)</i>.</li><li>Use the <b>'*'</b> wildcard to select multiple log files when adding files.</li></ul>", nullptr));
#ifndef UI_QT_NO_TOOLTIP
        fileList->setToolTip(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">List of files used by this log type.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef UI_QT_NO_WHATSTHIS
        fileList->setWhatsThis(tr2i18n("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Here is a list of every file that will be read by KSystemLog to display the current log lines.</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        Q_UNUSED(FileListBase);
    } // retranslateUi

};

namespace Ui {
    class FileListBase: public Ui_FileListBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FILELISTBASE_H

