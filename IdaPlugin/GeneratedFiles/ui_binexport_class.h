/********************************************************************************
** Form generated from reading UI file 'binexport_class.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINEXPORT_CLASS_H
#define UI_BINEXPORT_CLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinExportClass
{
public:
    QLabel *label;
    QPushButton *button_bin_export;
    QPushButton *button_text_export;
    QPushButton *button_statistic_export;

    void setupUi(QWidget *BinExportClass)
    {
        if (BinExportClass->objectName().isEmpty())
            BinExportClass->setObjectName(QStringLiteral("BinExportClass"));
        BinExportClass->resize(470, 130);
        BinExportClass->setMinimumSize(QSize(470, 130));
        BinExportClass->setMaximumSize(QSize(470, 130));
        label = new QLabel(BinExportClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 581, 31));
        button_bin_export = new QPushButton(BinExportClass);
        button_bin_export->setObjectName(QStringLiteral("button_bin_export"));
        button_bin_export->setGeometry(QRect(20, 70, 100, 23));
        button_text_export = new QPushButton(BinExportClass);
        button_text_export->setObjectName(QStringLiteral("button_text_export"));
        button_text_export->setGeometry(QRect(140, 70, 100, 23));
        button_statistic_export = new QPushButton(BinExportClass);
        button_statistic_export->setObjectName(QStringLiteral("button_statistic_export"));
        button_statistic_export->setGeometry(QRect(260, 70, 100, 23));

        retranslateUi(BinExportClass);
        QObject::connect(button_bin_export, SIGNAL(clicked()), BinExportClass, SLOT(binary_export()));
        QObject::connect(button_text_export, SIGNAL(clicked()), BinExportClass, SLOT(text_export()));
        QObject::connect(button_statistic_export, SIGNAL(clicked()), BinExportClass, SLOT(statistic_export()));

        QMetaObject::connectSlotsByName(BinExportClass);
    } // setupUi

    void retranslateUi(QWidget *BinExportClass)
    {
        BinExportClass->setWindowTitle(QApplication::translate("BinExportClass", "BinExport Realisation", Q_NULLPTR));
        label->setText(QApplication::translate("BinExportClass", "This realization became possible thanks to the project google/binexport. \n"
"More details at https://github.com/google/binexport", Q_NULLPTR));
        button_bin_export->setText(QApplication::translate("BinExportClass", "Binary Export", Q_NULLPTR));
        button_text_export->setText(QApplication::translate("BinExportClass", "Text Export", Q_NULLPTR));
        button_statistic_export->setText(QApplication::translate("BinExportClass", "Statistics Export", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BinExportClass: public Ui_BinExportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINEXPORT_CLASS_H
