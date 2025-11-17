/********************************************************************************
** Form generated from reading UI file 'tree_window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREE_WINDOW_H
#define UI_TREE_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TreeWindow
{
public:

    void setupUi(QWidget *TreeWindow)
    {
        if (TreeWindow->objectName().isEmpty())
            TreeWindow->setObjectName(QStringLiteral("TreeWindow"));
        TreeWindow->resize(400, 300);

        retranslateUi(TreeWindow);

        QMetaObject::connectSlotsByName(TreeWindow);
    } // setupUi

    void retranslateUi(QWidget *TreeWindow)
    {
        TreeWindow->setWindowTitle(QApplication::translate("TreeWindow", "TreeWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TreeWindow: public Ui_TreeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREE_WINDOW_H
