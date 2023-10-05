/********************************************************************************
** Form generated from reading UI file 'qtplot.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTPLOT_H
#define UI_QTPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtPlot
{
public:

    void setupUi(QWidget *QtPlot)
    {
        if (QtPlot->objectName().isEmpty())
            QtPlot->setObjectName(QString::fromUtf8("QtPlot"));
        QtPlot->resize(400, 300);

        retranslateUi(QtPlot);

        QMetaObject::connectSlotsByName(QtPlot);
    } // setupUi

    void retranslateUi(QWidget *QtPlot)
    {
        QtPlot->setWindowTitle(QCoreApplication::translate("QtPlot", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtPlot: public Ui_QtPlot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTPLOT_H
