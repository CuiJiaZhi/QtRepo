/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtDesigner/QDesignerCustomWidgetCollectionInterface>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSplitter *splitter;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QSpinBox *spinBox_row;
    QLabel *label_rowSpan;
    QLabel *label_row;
    QLabel *label_col;
    QSpinBox *spinBox_col;
    QLabel *label_colSpan;
    QSpinBox *spinBox_rowSpan;
    QSpinBox *spinBox_colSpan;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_del;
    customWidget *customwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(593, 416);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(5, 5, 254, 361));
        splitter->setOrientation(Qt::Horizontal);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(250, 0));
        frame->setMaximumSize(QSize(250, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBox_row = new QSpinBox(frame);
        spinBox_row->setObjectName(QString::fromUtf8("spinBox_row"));
        QFont font;
        font.setPointSize(10);
        spinBox_row->setFont(font);

        gridLayout->addWidget(spinBox_row, 0, 1, 1, 1);

        label_rowSpan = new QLabel(frame);
        label_rowSpan->setObjectName(QString::fromUtf8("label_rowSpan"));
        label_rowSpan->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_rowSpan, 1, 0, 1, 1);

        label_row = new QLabel(frame);
        label_row->setObjectName(QString::fromUtf8("label_row"));
        label_row->setFont(font);
        label_row->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_row, 0, 0, 1, 1);

        label_col = new QLabel(frame);
        label_col->setObjectName(QString::fromUtf8("label_col"));
        label_col->setFont(font);
        label_col->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_col, 2, 0, 1, 1);

        spinBox_col = new QSpinBox(frame);
        spinBox_col->setObjectName(QString::fromUtf8("spinBox_col"));
        spinBox_col->setFont(font);

        gridLayout->addWidget(spinBox_col, 2, 1, 1, 1);

        label_colSpan = new QLabel(frame);
        label_colSpan->setObjectName(QString::fromUtf8("label_colSpan"));
        label_colSpan->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_colSpan, 3, 0, 1, 1);

        spinBox_rowSpan = new QSpinBox(frame);
        spinBox_rowSpan->setObjectName(QString::fromUtf8("spinBox_rowSpan"));
        spinBox_rowSpan->setFont(font);

        gridLayout->addWidget(spinBox_rowSpan, 1, 1, 1, 1);

        spinBox_colSpan = new QSpinBox(frame);
        spinBox_colSpan->setObjectName(QString::fromUtf8("spinBox_colSpan"));
        spinBox_colSpan->setFont(font);

        gridLayout->addWidget(spinBox_colSpan, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_add = new QPushButton(frame);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));
        pushButton_add->setFont(font);

        horizontalLayout->addWidget(pushButton_add);

        pushButton_del = new QPushButton(frame);
        pushButton_del->setObjectName(QString::fromUtf8("pushButton_del"));
        pushButton_del->setFont(font);

        horizontalLayout->addWidget(pushButton_del);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        splitter->addWidget(frame);
        customwidget = new customWidget(splitter);
        customwidget->setObjectName(QString::fromUtf8("customwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customwidget->sizePolicy().hasHeightForWidth());
        customwidget->setSizePolicy(sizePolicy);
        splitter->addWidget(customwidget);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 593, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_rowSpan->setText(QCoreApplication::translate("MainWindow", "rowSpan", nullptr));
        label_row->setText(QCoreApplication::translate("MainWindow", "row", nullptr));
        label_col->setText(QCoreApplication::translate("MainWindow", "col", nullptr));
        label_colSpan->setText(QCoreApplication::translate("MainWindow", "colSpan", nullptr));
        pushButton_add->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        pushButton_del->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
