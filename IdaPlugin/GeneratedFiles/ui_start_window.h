/********************************************************************************
** Form generated from reading UI file 'start_window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_WINDOW_H
#define UI_START_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QRadioButton *radioButton;
    QPushButton *pushButton_2;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_3;
    QRadioButton *radioButton_3;
    QPushButton *pushButton_4;
    QRadioButton *radioButton_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *binexport_button;
    QSpacerItem *horizontalSpacer;
    QPushButton *setting_button;
    QPushButton *notepad_button;
    QLabel *label;
    QLineEdit *lineEdit_CMDLine;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName(QStringLiteral("StartWindow"));
        StartWindow->setWindowModality(Qt::ApplicationModal);
        StartWindow->resize(785, 819);
        StartWindow->setStyleSheet(QLatin1String("QPushButton {\n"
"    border: 2px solid rgb(100,100,100);\n"
"    border-radius: 3px;\n"
"    background-color: rgb(200,225,225);\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton::hover{\n"
"	 background-color: rgb(200,200,200);\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(StartWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(StartWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        radioButton = new QRadioButton(StartWindow);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout->addWidget(radioButton);

        pushButton_2 = new QPushButton(StartWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        radioButton_2 = new QRadioButton(StartWindow);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        pushButton_3 = new QPushButton(StartWindow);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        radioButton_3 = new QRadioButton(StartWindow);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);

        pushButton_4 = new QPushButton(StartWindow);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        radioButton_4 = new QRadioButton(StartWindow);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout->addWidget(radioButton_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        binexport_button = new QPushButton(StartWindow);
        binexport_button->setObjectName(QStringLiteral("binexport_button"));
        binexport_button->setMinimumSize(QSize(84, 20));

        horizontalLayout->addWidget(binexport_button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        setting_button = new QPushButton(StartWindow);
        setting_button->setObjectName(QStringLiteral("setting_button"));
        setting_button->setEnabled(true);
        setting_button->setMinimumSize(QSize(84, 20));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(200, 225, 225, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(201, 201, 201, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(167, 167, 167, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(67, 67, 67, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(89, 89, 89, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(70, 113, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(194, 194, 194, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(165, 165, 165, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush8);
        QBrush brush9(QColor(255, 255, 220, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush10(QColor(134, 134, 134, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush10);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush9);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        setting_button->setPalette(palette);
        setting_button->setAcceptDrops(false);
        setting_button->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(setting_button);

        notepad_button = new QPushButton(StartWindow);
        notepad_button->setObjectName(QStringLiteral("notepad_button"));
        notepad_button->setMinimumSize(QSize(84, 20));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        QBrush brush11(QColor(120, 120, 120, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        notepad_button->setPalette(palette1);

        horizontalLayout->addWidget(notepad_button);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(StartWindow);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);
        label->setCursor(QCursor(Qt::IBeamCursor));
        label->setMargin(2);

        verticalLayout->addWidget(label);

        lineEdit_CMDLine = new QLineEdit(StartWindow);
        lineEdit_CMDLine->setObjectName(QStringLiteral("lineEdit_CMDLine"));
        lineEdit_CMDLine->setFont(font);

        verticalLayout->addWidget(lineEdit_CMDLine);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QWidget *StartWindow)
    {
        StartWindow->setWindowTitle(QApplication::translate("StartWindow", "StartWindow", Q_NULLPTR));
        pushButton->setText(QApplication::translate("StartWindow", "PushButton", Q_NULLPTR));
        radioButton->setText(QApplication::translate("StartWindow", "RadioButton", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("StartWindow", "PushButton", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("StartWindow", "RadioButton", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("StartWindow", "PushButton", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("StartWindow", "RadioButton", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("StartWindow", "PushButton", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("StartWindow", "RadioButton", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        binexport_button->setToolTip(QApplication::translate("StartWindow", "Functionality added thanks to the BinExport project. \n"
"More information can be found at https://github.com/google/binexport", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        binexport_button->setText(QApplication::translate("StartWindow", "BinExport", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        setting_button->setToolTip(QApplication::translate("StartWindow", "<html><head/><body><p>Open settings form ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        setting_button->setText(QApplication::translate("StartWindow", "Setting", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        notepad_button->setToolTip(QApplication::translate("StartWindow", "<html><head/><body><p>Create your own notepad, which will be available when working with the plugin ...<br/>Ida has its own notepad, but it is only available for the specific file being disassembled...<br/><br/>Ida \320\270\320\274\320\265\320\265\321\202 \321\201\320\262\320\276\320\271 \321\201\320\276\320\261\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\271 \320\261\320\273\320\276\320\272\320\275\320\276\321\202, \320\275\320\276 \320\276\320\275 \320\264\320\276\321\201\321\202\321\203\320\277\320\265\320\275 \321\202\320\276\320\273\321\214\320\272\320\276 \320\264\320\273\321\217 \320\272\320\276\320\275\320\272\321\200\320\265\321\202\320\275\320\276\320\263\320\276 \320\264\320\270\320\267\320\260\321\201\321\201\320\265\320\274\320\261\320\273\320\270\321\200\321\203\320\265\320\274\320\276\320\263\320\276 \321\204\320\260\320\271\320\273\320\260...<br/>\320\241\320\276\320\267\320\264\320\260\320\271\321\202\320\265 \321\201\320\262\320\276\320\271 \321\201\320\276\320\261\321\201\321"
                        "\202\320\262\320\265\320\275\320\275\321\213\320\271 \320\261\320\273\320\276\320\272\320\275\320\276\321\202, \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \320\261\321\203\320\264\320\265\321\202 \320\264\320\276\321\201\321\202\321\203\320\277\320\265\320\275 \320\277\321\200\320\270 \321\200\320\260\320\261\320\276\321\202\320\265 \321\201 \320\277\320\273\320\260\320\263\320\270\320\275\320\276\320\274 ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        notepad_button->setText(QApplication::translate("StartWindow", "Notepad", Q_NULLPTR));
        label->setText(QApplication::translate("StartWindow", "CMD Line", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_WINDOW_H
