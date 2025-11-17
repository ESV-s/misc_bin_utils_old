/********************************************************************************
** Form generated from reading UI file 'first_window.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRST_WINDOW_H
#define UI_FIRST_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FirstWindow
{
public:
    QCheckBox *checkBox_Scylla;
    QCheckBox *checkBox_MSSQL;
    QCheckBox *checkBox_Start_after_debug;
    QCheckBox *checkBox_coloring;
    QCheckBox *checkBox_PrintInfo;
    QCheckBox *checkBox_FunctionData;
    QCheckBox *checkBox_MangledName;
    QCheckBox *checkBox_OutputCleaning;
    QCheckBox *checkBox_FixedLocation;
    QCheckBox *checkBox_ContainerSize;

    void setupUi(QWidget *FirstWindow)
    {
        if (FirstWindow->objectName().isEmpty())
            FirstWindow->setObjectName(QStringLiteral("FirstWindow"));
        FirstWindow->resize(703, 459);
        FirstWindow->setStyleSheet(QLatin1String("QCheckBox::hover {\n"
"	color: rgb(85, 0, 255);\n"
"}\n"
""));
        checkBox_Scylla = new QCheckBox(FirstWindow);
        checkBox_Scylla->setObjectName(QStringLiteral("checkBox_Scylla"));
        checkBox_Scylla->setGeometry(QRect(30, 30, 141, 20));
        QFont font;
        font.setPointSize(10);
        checkBox_Scylla->setFont(font);
        checkBox_Scylla->setStyleSheet(QStringLiteral(""));
        checkBox_MSSQL = new QCheckBox(FirstWindow);
        checkBox_MSSQL->setObjectName(QStringLiteral("checkBox_MSSQL"));
        checkBox_MSSQL->setGeometry(QRect(30, 60, 141, 20));
        checkBox_MSSQL->setFont(font);
        checkBox_Start_after_debug = new QCheckBox(FirstWindow);
        checkBox_Start_after_debug->setObjectName(QStringLiteral("checkBox_Start_after_debug"));
        checkBox_Start_after_debug->setGeometry(QRect(30, 90, 131, 20));
        checkBox_Start_after_debug->setFont(font);
        checkBox_coloring = new QCheckBox(FirstWindow);
        checkBox_coloring->setObjectName(QStringLiteral("checkBox_coloring"));
        checkBox_coloring->setGeometry(QRect(30, 120, 141, 20));
        checkBox_coloring->setFont(font);
        checkBox_PrintInfo = new QCheckBox(FirstWindow);
        checkBox_PrintInfo->setObjectName(QStringLiteral("checkBox_PrintInfo"));
        checkBox_PrintInfo->setGeometry(QRect(30, 150, 111, 20));
        checkBox_PrintInfo->setFont(font);
        checkBox_FunctionData = new QCheckBox(FirstWindow);
        checkBox_FunctionData->setObjectName(QStringLiteral("checkBox_FunctionData"));
        checkBox_FunctionData->setEnabled(false);
        checkBox_FunctionData->setGeometry(QRect(60, 185, 121, 20));
        checkBox_FunctionData->setFont(font);
        checkBox_MangledName = new QCheckBox(FirstWindow);
        checkBox_MangledName->setObjectName(QStringLiteral("checkBox_MangledName"));
        checkBox_MangledName->setEnabled(false);
        checkBox_MangledName->setGeometry(QRect(60, 200, 121, 20));
        checkBox_MangledName->setFont(font);
        checkBox_OutputCleaning = new QCheckBox(FirstWindow);
        checkBox_OutputCleaning->setObjectName(QStringLiteral("checkBox_OutputCleaning"));
        checkBox_OutputCleaning->setEnabled(false);
        checkBox_OutputCleaning->setGeometry(QRect(60, 215, 121, 20));
        checkBox_OutputCleaning->setFont(font);
        checkBox_FixedLocation = new QCheckBox(FirstWindow);
        checkBox_FixedLocation->setObjectName(QStringLiteral("checkBox_FixedLocation"));
        checkBox_FixedLocation->setGeometry(QRect(30, 235, 141, 20));
        checkBox_FixedLocation->setFont(font);
        checkBox_ContainerSize = new QCheckBox(FirstWindow);
        checkBox_ContainerSize->setObjectName(QStringLiteral("checkBox_ContainerSize"));
        checkBox_ContainerSize->setEnabled(false);
        checkBox_ContainerSize->setGeometry(QRect(60, 170, 121, 20));
        checkBox_ContainerSize->setFont(font);

        retranslateUi(FirstWindow);
        QObject::connect(checkBox_Scylla, SIGNAL(clicked()), FirstWindow, SLOT(AddScylla()));
        QObject::connect(checkBox_MSSQL, SIGNAL(clicked()), FirstWindow, SLOT(AddMSSQL()));
        QObject::connect(checkBox_Start_after_debug, SIGNAL(clicked()), FirstWindow, SLOT(StartAfterDebug()));
        QObject::connect(checkBox_coloring, SIGNAL(clicked()), FirstWindow, SLOT(ColorFunctions()));
        QObject::connect(checkBox_PrintInfo, SIGNAL(clicked()), FirstWindow, SLOT(PrintInfo()));
        QObject::connect(checkBox_FunctionData, SIGNAL(clicked()), FirstWindow, SLOT(PrintInfoFunctionData()));
        QObject::connect(checkBox_MangledName, SIGNAL(clicked()), FirstWindow, SLOT(PrintInfoMangledName()));
        QObject::connect(checkBox_OutputCleaning, SIGNAL(clicked()), FirstWindow, SLOT(PrintInfoOutputCleaning()));
        QObject::connect(checkBox_FixedLocation, SIGNAL(clicked()), FirstWindow, SLOT(FixedLocation()));
        QObject::connect(checkBox_ContainerSize, SIGNAL(clicked()), FirstWindow, SLOT(PrintInfoContainerSize()));

        QMetaObject::connectSlotsByName(FirstWindow);
    } // setupUi

    void retranslateUi(QWidget *FirstWindow)
    {
        FirstWindow->setWindowTitle(QApplication::translate("FirstWindow", "Setting Window", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_Scylla->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>if you use ScyllaHide - install this checkbox and the plugin will know about Scylla ...<br/><br/>\320\265\321\201\320\273\320\270 \320\262\321\213 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\320\265 ScyllaHide - \321\203\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\320\265 \321\215\321\202\320\276\321\202 \321\207\320\265\320\272 \320\261\320\276\320\272\321\201 <br/>\320\270 \320\277\320\273\320\260\320\263\320\270\320\275 \320\261\321\203\320\264\320\265\321\202 \320\267\320\275\320\260\321\202\321\214 \320\276 Scylla ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_Scylla->setText(QApplication::translate("FirstWindow", "Using Scylla Hide", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_MSSQL->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>this checkbox will allow you to use a connection to a MSSQL database ...<br/><br/>\320\264\320\260\320\275\320\275\321\213\320\271 \321\207\320\265\320\272 \320\261\320\276\320\272\321\201 \320\277\320\276\320\267\320\262\320\276\320\273\320\270\321\202 \320\262\320\260\320\274 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214 \321\201\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265 \321\201 \320\261\320\260\320\267\320\276\320\271 \320\264\320\260\320\275\320\275\321\213\321\205 MSSQL ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_MSSQL->setText(QApplication::translate("FirstWindow", "Using MSSQL db", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_Start_after_debug->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>automatic launch of the plug-in after debugging is completed ...<br/><br/>\320\260\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\267\320\260\320\277\321\203\321\201\320\272 \320\277\320\273\320\260\320\263\320\270\320\275\320\260 \320\277\320\276\321\201\320\273\320\265 \320\267\320\260\320\262\320\265\321\200\321\210\320\265\320\275\320\270\321\217 \320\276\321\202\320\273\320\260\320\264\320\272\320\270 ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_Start_after_debug->setText(QApplication::translate("FirstWindow", "Start after debug", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_coloring->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>highlight functions by color based on data received from binexport ...<br/><br/>\320\262\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \321\204\321\203\320\275\320\272\321\206\320\270\320\270 \321\206\320\262\320\265\321\202\320\276\320\274 \320\275\320\260 \320\276\321\201\320\275\320\276\320\262\320\260\320\275\320\270\320\270 \320\264\320\260\320\275\320\275\321\213\321\205 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\321\205 \320\276\321\202 binexport ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_coloring->setText(QApplication::translate("FirstWindow", "Functions into color", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_PrintInfo->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>output information into window ...<br/><br/>\320\262\321\213\320\262\320\276\320\264 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\262 output \320\276\320\272\320\275\320\276  ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_PrintInfo->setText(QApplication::translate("FirstWindow", "Print Info", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_FunctionData->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>output information about functions ...<br/><br/>\320\262\321\213\320\262\320\276\320\264 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\276 \321\204\321\203\320\275\320\272\321\206\320\270\321\217\321\205 ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_FunctionData->setText(QApplication::translate("FirstWindow", "Functions Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_MangledName->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>show mangled function name ...<br/><br/>\320\277\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\270\321\201\320\272\320\260\320\266\320\265\320\275\320\275\321\213\320\265 \320\270\320\274\320\265\320\275\320\260 \321\204\321\203\320\275\320\272\321\206\320\270\320\271 ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_MangledName->setText(QApplication::translate("FirstWindow", "Mangled Name", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_OutputCleaning->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>clean output window before start plugin ...<br/><br/>\320\276\321\207\320\270\321\211\320\260\321\202\321\214 Output Window \320\277\320\265\321\200\320\265\320\264 \320\267\320\260\320\277\321\203\321\201\320\272\320\276\320\274 \320\277\320\273\320\260\320\263\320\270\320\275\320\260 ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_OutputCleaning->setText(QApplication::translate("FirstWindow", "Output Cleaning", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_FixedLocation->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>Plugin Window has fixed location ...<br/><br/>\320\236\320\272\320\275\320\276 \320\277\320\273\320\260\320\263\320\270\320\275\320\260 \320\270\320\274\320\265\320\265\321\202 \321\204\320\270\320\272\321\201\320\270\321\200\320\276\320\262\320\260\320\275\320\275\320\276\320\265 \321\200\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265  ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_FixedLocation->setText(QApplication::translate("FirstWindow", "Fixed Location View ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_ContainerSize->setToolTip(QApplication::translate("FirstWindow", "<html><head/><body><p>output information about container size ...<br/><br/>\320\262\321\213\320\262\320\276\320\264 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270 \320\276 \321\200\320\260\320\267\320\274\320\265\321\200\320\260\321\205 \320\272\320\276\320\275\321\202\320\265\320\270\320\275\320\265\321\200\320\276\320\262 \320\264\320\260\320\275\320\275\321\213\321\205 ...</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_ContainerSize->setText(QApplication::translate("FirstWindow", "Container size", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FirstWindow: public Ui_FirstWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRST_WINDOW_H
