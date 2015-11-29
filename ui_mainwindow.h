/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *open_cam;
    QPushButton *grabcut;
    QPushButton *loadpicture;
    QPushButton *goal;
    QPushButton *coin;
    QPushButton *count;
    QLabel *label;
    QLCDNumber *goalnumber;
    QLabel *label_2;
    QLCDNumber *coinnumber;
    QLCDNumber *answernumber;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        open_cam = new QPushButton(centralWidget);
        open_cam->setObjectName(QStringLiteral("open_cam"));
        open_cam->setGeometry(QRect(50, 70, 75, 23));
        grabcut = new QPushButton(centralWidget);
        grabcut->setObjectName(QStringLiteral("grabcut"));
        grabcut->setEnabled(false);
        grabcut->setGeometry(QRect(50, 100, 75, 23));
        loadpicture = new QPushButton(centralWidget);
        loadpicture->setObjectName(QStringLiteral("loadpicture"));
        loadpicture->setGeometry(QRect(50, 40, 75, 23));
        goal = new QPushButton(centralWidget);
        goal->setObjectName(QStringLiteral("goal"));
        goal->setGeometry(QRect(140, 40, 75, 23));
        coin = new QPushButton(centralWidget);
        coin->setObjectName(QStringLiteral("coin"));
        coin->setGeometry(QRect(140, 70, 75, 23));
        count = new QPushButton(centralWidget);
        count->setObjectName(QStringLiteral("count"));
        count->setEnabled(false);
        count->setGeometry(QRect(140, 100, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(230, 40, 71, 21));
        goalnumber = new QLCDNumber(centralWidget);
        goalnumber->setObjectName(QStringLiteral("goalnumber"));
        goalnumber->setGeometry(QRect(290, 20, 91, 41));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 100, 47, 12));
        coinnumber = new QLCDNumber(centralWidget);
        coinnumber->setObjectName(QStringLiteral("coinnumber"));
        coinnumber->setGeometry(QRect(290, 80, 91, 41));
        answernumber = new QLCDNumber(centralWidget);
        answernumber->setObjectName(QStringLiteral("answernumber"));
        answernumber->setGeometry(QRect(140, 150, 181, 51));
        answernumber->setDigitCount(8);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 160, 111, 31));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(330, 161, 47, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        open_cam->setText(QApplication::translate("MainWindow", "open cam", 0));
        grabcut->setText(QApplication::translate("MainWindow", "grabcut", 0));
        loadpicture->setText(QApplication::translate("MainWindow", "load picture", 0));
        goal->setText(QApplication::translate("MainWindow", "goal", 0));
        coin->setText(QApplication::translate("MainWindow", "coin", 0));
        count->setText(QApplication::translate("MainWindow", "count", 0));
        label->setText(QApplication::translate("MainWindow", "goal pixel:", 0));
        label_2->setText(QApplication::translate("MainWindow", "coin pixel:", 0));
        label_3->setText(QApplication::translate("MainWindow", "the area of the goal:", 0));
        label_4->setText(QApplication::translate("MainWindow", "square", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
