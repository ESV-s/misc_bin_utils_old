/********************************************************************************
** Form generated from reading UI file 'notepad_window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_WINDOW_H
#define UI_NOTEPAD_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotepadWindow
{
public:
    QTextEdit *textEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *findButton;

    void setupUi(QWidget *NotepadWindow)
    {
        if (NotepadWindow->objectName().isEmpty())
            NotepadWindow->setObjectName(QStringLiteral("NotepadWindow"));
        NotepadWindow->resize(641, 937);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NotepadWindow->sizePolicy().hasHeightForWidth());
        NotepadWindow->setSizePolicy(sizePolicy);
        textEdit = new QTextEdit(NotepadWindow);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(2, 40, 636, 891));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy1);
        textEdit->setStyleSheet(QLatin1String("border-color: rgb(0, 0, 0);\n"
"font: 10pt \"Arial\";"));
        layoutWidget = new QWidget(NotepadWindow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 4, 591, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        findButton = new QPushButton(layoutWidget);
        findButton->setObjectName(QStringLiteral("findButton"));

        horizontalLayout->addWidget(findButton);


        retranslateUi(NotepadWindow);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), findButton, SLOT(animateClick()));

        QMetaObject::connectSlotsByName(NotepadWindow);
    } // setupUi

    void retranslateUi(QWidget *NotepadWindow)
    {
        NotepadWindow->setWindowTitle(QApplication::translate("NotepadWindow", "Notepad", Q_NULLPTR));
        label->setText(QApplication::translate("NotepadWindow", "Keyword:", Q_NULLPTR));
        findButton->setText(QApplication::translate("NotepadWindow", "Find", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NotepadWindow: public Ui_NotepadWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_WINDOW_H
