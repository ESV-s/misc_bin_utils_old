/********************************************************************************
** Form generated from reading UI file 'db_connection.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DB_CONNECTION_H
#define UI_DB_CONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBConnection
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label_link;
    QPushButton *pushButton;
    QToolButton *toolButton_HelpShow;

    void setupUi(QWidget *DBConnection)
    {
        if (DBConnection->objectName().isEmpty())
            DBConnection->setObjectName(QStringLiteral("DBConnection"));
        DBConnection->resize(719, 155);
        label = new QLabel(DBConnection);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 221, 16));
        lineEdit = new QLineEdit(DBConnection);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(40, 50, 291, 20));
        label_2 = new QLabel(DBConnection);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 90, 121, 16));
        label_link = new QLabel(DBConnection);
        label_link->setObjectName(QStringLiteral("label_link"));
        label_link->setGeometry(QRect(190, 90, 611, 16));
        label_link->setToolTipDuration(2);
        pushButton = new QPushButton(DBConnection);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(570, 110, 75, 23));
        toolButton_HelpShow = new QToolButton(DBConnection);
        toolButton_HelpShow->setObjectName(QStringLiteral("toolButton_HelpShow"));
        toolButton_HelpShow->setGeometry(QRect(160, 20, 15, 15));

        retranslateUi(DBConnection);
        QObject::connect(pushButton, SIGNAL(clicked()), DBConnection, SLOT(AddSetting()));
        QObject::connect(toolButton_HelpShow, SIGNAL(clicked()), DBConnection, SLOT(FormSetHelp()));

        QMetaObject::connectSlotsByName(DBConnection);
    } // setupUi

    void retranslateUi(QWidget *DBConnection)
    {
        DBConnection->setWindowTitle(QApplication::translate("DBConnection", "DBConnection", Q_NULLPTR));
        label->setText(QApplication::translate("DBConnection", "SQL instance name", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("DBConnection", "<html><head/><body><p>The plugin uses the default connection <br/>Current Windows user (built-in security). <br/>All you need to do is specify the name of the SQL instance ...<br/>LOCALHOST will be added automatically...</p><p>\320\237\320\273\320\260\320\263\320\270\320\275 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265 \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216 <br/>\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214 Windows (\320\262\321\201\321\202\321\200\320\276\320\265\320\275\320\275\320\260\321\217 \320\261\320\265\320\267\320\276\320\277\320\260\321\201\320\275\320\276\321\201\321\202\321\214). <br/>\320\222\321\201\321\221 \321\207\321\202\320\276 \320\275\321\203\320\266\320\275\320\276 \321\201\320\264\320\265\320\273\320\260\321\202\321\214"
                        " - \321\215\321\202\320\276 \321\203\320\272\320\260\320\267\320\260\321\202\321\214 \320\270\320\274\321\217 \321\215\320\272\320\267\320\265\320\274\320\277\320\273\321\217\321\200\320\260 SQL ...<br/>LOCALHOST \320\261\321\203\320\264\320\265\321\202 \320\264\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\276 \320\260\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270 ...</p><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("DBConnection", "<html><head/><body><p>If this doesn't work for you, check in the ODBC Custom DSN settings with the name &quot;SQL Server&quot;.<br/><br/>\320\225\321\201\320\273\320\270 \321\203 \320\262\320\260\321\201 \321\215\321\202\320\276 \320\275\320\265 \321\200\320\260\320\261\320\276\321\202\320\260\320\265\321\202, \320\277\321\200\320\276\320\262\320\265\321\200\321\214\321\202\320\265 \320\262 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260\321\205 ODBC \320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\214\321\201\320\272\320\270\320\271 DSN \321\201 \320\270\320\274\320\265\320\275\320\265\320\274 &quot;SQL Server&quot;.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("DBConnection", "DRIVER={SQL Server};", Q_NULLPTR));
        label_link->setText(QApplication::translate("DBConnection", "About ODBC drivers", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DBConnection", "Ok", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        toolButton_HelpShow->setToolTip(QApplication::translate("DBConnection", "<html><head/><body><p align=\"justify\">Show Help about ODBC and SQL instance name ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolButton_HelpShow->setText(QApplication::translate("DBConnection", "?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DBConnection: public Ui_DBConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DB_CONNECTION_H
