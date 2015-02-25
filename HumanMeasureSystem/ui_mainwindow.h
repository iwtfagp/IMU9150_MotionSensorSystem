/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qwt_dial.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QwtDial *Dial_left_hip;
    QwtDial *Dial_right_knee;
    QwtDial *Dial_right_hip;
    QwtDial *Dial_left_knee;
    QLCDNumber *lcdNumber_left_hip;
    QLCDNumber *lcdNumber_right_hip;
    QLCDNumber *lcdNumber_left_knee;
    QLCDNumber *lcdNumber_right_knee;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLCDNumber *lcdNumber_back;
    QLineEdit *lineEdit_lpmsPortName;
    QComboBox *comboBoxIMU_left_thigh;
    QComboBox *comboBoxIMU_right_thigh;
    QComboBox *comboBoxIMU_left_shank;
    QComboBox *comboBoxIMU_right_shank;
    QPushButton *pushButton_deviceConnect;
    QLCDNumber *lcdNumber_right_shank;
    QLCDNumber *lcdNumber_left_shank;
    QLCDNumber *lcdNumber_right_thigh;
    QLCDNumber *lcdNumber_left_thigh;
    QTextBrowser *textBrowser;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    QLineEdit *lineEdit_username;
    QPushButton *pushButton_newFile;
    QLineEdit *file_path;
    QPushButton *pushButton_saveFile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(720, 629);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        Dial_left_hip = new QwtDial(centralWidget);
        Dial_left_hip->setObjectName(QStringLiteral("Dial_left_hip"));
        Dial_left_hip->setAutoFillBackground(false);
        Dial_left_hip->setLowerBound(-180);
        Dial_left_hip->setUpperBound(180);
        Dial_left_hip->setScaleMaxMajor(20);
        Dial_left_hip->setScaleMaxMinor(2);
        Dial_left_hip->setReadOnly(true);
        Dial_left_hip->setWrapping(false);
        Dial_left_hip->setInvertedControls(false);
        Dial_left_hip->setLineWidth(3);
        Dial_left_hip->setMinScaleArc(0);
        Dial_left_hip->setMaxScaleArc(360);

        gridLayout_4->addWidget(Dial_left_hip, 0, 0, 1, 1);

        Dial_right_knee = new QwtDial(centralWidget);
        Dial_right_knee->setObjectName(QStringLiteral("Dial_right_knee"));
        Dial_right_knee->setAutoFillBackground(false);
        Dial_right_knee->setLowerBound(-180);
        Dial_right_knee->setUpperBound(180);
        Dial_right_knee->setScaleMaxMajor(20);
        Dial_right_knee->setScaleMaxMinor(2);
        Dial_right_knee->setValue(0);
        Dial_right_knee->setTotalSteps(100u);
        Dial_right_knee->setReadOnly(true);
        Dial_right_knee->setWrapping(false);
        Dial_right_knee->setInvertedControls(false);
        Dial_right_knee->setLineWidth(3);
        Dial_right_knee->setMinScaleArc(0);
        Dial_right_knee->setMaxScaleArc(360);

        gridLayout_4->addWidget(Dial_right_knee, 2, 1, 1, 1);

        Dial_right_hip = new QwtDial(centralWidget);
        Dial_right_hip->setObjectName(QStringLiteral("Dial_right_hip"));
        Dial_right_hip->setAutoFillBackground(false);
        Dial_right_hip->setLowerBound(-180);
        Dial_right_hip->setUpperBound(180);
        Dial_right_hip->setScaleMaxMajor(20);
        Dial_right_hip->setScaleMaxMinor(2);
        Dial_right_hip->setReadOnly(true);
        Dial_right_hip->setWrapping(false);
        Dial_right_hip->setInvertedControls(false);
        Dial_right_hip->setLineWidth(3);
        Dial_right_hip->setMinScaleArc(0);
        Dial_right_hip->setMaxScaleArc(360);

        gridLayout_4->addWidget(Dial_right_hip, 0, 1, 1, 1);

        Dial_left_knee = new QwtDial(centralWidget);
        Dial_left_knee->setObjectName(QStringLiteral("Dial_left_knee"));
        Dial_left_knee->setAutoFillBackground(false);
        Dial_left_knee->setLowerBound(-180);
        Dial_left_knee->setUpperBound(180);
        Dial_left_knee->setScaleMaxMajor(20);
        Dial_left_knee->setScaleMaxMinor(2);
        Dial_left_knee->setReadOnly(true);
        Dial_left_knee->setWrapping(false);
        Dial_left_knee->setInvertedControls(false);
        Dial_left_knee->setLineWidth(3);
        Dial_left_knee->setMinScaleArc(0);
        Dial_left_knee->setMaxScaleArc(360);

        gridLayout_4->addWidget(Dial_left_knee, 2, 0, 1, 1);

        lcdNumber_left_hip = new QLCDNumber(centralWidget);
        lcdNumber_left_hip->setObjectName(QStringLiteral("lcdNumber_left_hip"));

        gridLayout_4->addWidget(lcdNumber_left_hip, 1, 0, 1, 1);

        lcdNumber_right_hip = new QLCDNumber(centralWidget);
        lcdNumber_right_hip->setObjectName(QStringLiteral("lcdNumber_right_hip"));

        gridLayout_4->addWidget(lcdNumber_right_hip, 1, 1, 1, 1);

        lcdNumber_left_knee = new QLCDNumber(centralWidget);
        lcdNumber_left_knee->setObjectName(QStringLiteral("lcdNumber_left_knee"));

        gridLayout_4->addWidget(lcdNumber_left_knee, 3, 0, 1, 1);

        lcdNumber_right_knee = new QLCDNumber(centralWidget);
        lcdNumber_right_knee->setObjectName(QStringLiteral("lcdNumber_right_knee"));

        gridLayout_4->addWidget(lcdNumber_right_knee, 3, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 3, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lcdNumber_back = new QLCDNumber(centralWidget);
        lcdNumber_back->setObjectName(QStringLiteral("lcdNumber_back"));
        lcdNumber_back->setDigitCount(3);

        gridLayout_2->addWidget(lcdNumber_back, 2, 0, 1, 1);

        lineEdit_lpmsPortName = new QLineEdit(centralWidget);
        lineEdit_lpmsPortName->setObjectName(QStringLiteral("lineEdit_lpmsPortName"));

        gridLayout_2->addWidget(lineEdit_lpmsPortName, 3, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 2);

        comboBoxIMU_left_thigh = new QComboBox(centralWidget);
        comboBoxIMU_left_thigh->setObjectName(QStringLiteral("comboBoxIMU_left_thigh"));

        gridLayout->addWidget(comboBoxIMU_left_thigh, 2, 0, 1, 1);

        comboBoxIMU_right_thigh = new QComboBox(centralWidget);
        comboBoxIMU_right_thigh->setObjectName(QStringLiteral("comboBoxIMU_right_thigh"));

        gridLayout->addWidget(comboBoxIMU_right_thigh, 2, 1, 1, 1);

        comboBoxIMU_left_shank = new QComboBox(centralWidget);
        comboBoxIMU_left_shank->setObjectName(QStringLiteral("comboBoxIMU_left_shank"));

        gridLayout->addWidget(comboBoxIMU_left_shank, 4, 0, 1, 1);

        comboBoxIMU_right_shank = new QComboBox(centralWidget);
        comboBoxIMU_right_shank->setObjectName(QStringLiteral("comboBoxIMU_right_shank"));

        gridLayout->addWidget(comboBoxIMU_right_shank, 4, 1, 1, 1);

        pushButton_deviceConnect = new QPushButton(centralWidget);
        pushButton_deviceConnect->setObjectName(QStringLiteral("pushButton_deviceConnect"));

        gridLayout->addWidget(pushButton_deviceConnect, 5, 0, 1, 2);

        lcdNumber_right_shank = new QLCDNumber(centralWidget);
        lcdNumber_right_shank->setObjectName(QStringLiteral("lcdNumber_right_shank"));
        lcdNumber_right_shank->setDigitCount(3);

        gridLayout->addWidget(lcdNumber_right_shank, 3, 1, 1, 1);

        lcdNumber_left_shank = new QLCDNumber(centralWidget);
        lcdNumber_left_shank->setObjectName(QStringLiteral("lcdNumber_left_shank"));
        lcdNumber_left_shank->setSmallDecimalPoint(false);
        lcdNumber_left_shank->setDigitCount(3);

        gridLayout->addWidget(lcdNumber_left_shank, 3, 0, 1, 1);

        lcdNumber_right_thigh = new QLCDNumber(centralWidget);
        lcdNumber_right_thigh->setObjectName(QStringLiteral("lcdNumber_right_thigh"));
        lcdNumber_right_thigh->setDigitCount(3);

        gridLayout->addWidget(lcdNumber_right_thigh, 1, 1, 1, 1);

        lcdNumber_left_thigh = new QLCDNumber(centralWidget);
        lcdNumber_left_thigh->setObjectName(QStringLiteral("lcdNumber_left_thigh"));
        lcdNumber_left_thigh->setDigitCount(3);

        gridLayout->addWidget(lcdNumber_left_thigh, 1, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout, 0, 1, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout_5->addWidget(textBrowser, 1, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        lineEdit_username = new QLineEdit(centralWidget);
        lineEdit_username->setObjectName(QStringLiteral("lineEdit_username"));

        gridLayout_3->addWidget(lineEdit_username, 0, 1, 1, 1);

        pushButton_newFile = new QPushButton(centralWidget);
        pushButton_newFile->setObjectName(QStringLiteral("pushButton_newFile"));
        pushButton_newFile->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pushButton_newFile->setFont(font);

        gridLayout_3->addWidget(pushButton_newFile, 1, 0, 1, 2);

        file_path = new QLineEdit(centralWidget);
        file_path->setObjectName(QStringLiteral("file_path"));

        gridLayout_3->addWidget(file_path, 2, 0, 1, 2);

        pushButton_saveFile = new QPushButton(centralWidget);
        pushButton_saveFile->setObjectName(QStringLiteral("pushButton_saveFile"));
        pushButton_saveFile->setMinimumSize(QSize(0, 50));
        pushButton_saveFile->setFont(font);

        gridLayout_3->addWidget(pushButton_saveFile, 3, 0, 1, 2);


        gridLayout_5->addLayout(gridLayout_3, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 720, 22));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "HumanMeasureSystem", 0));
        lineEdit_lpmsPortName->setText(QApplication::translate("MainWindow", "00:06:66:4B:24:D2", 0));
        comboBoxIMU_left_thigh->clear();
        comboBoxIMU_left_thigh->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM10", 0)
        );
        comboBoxIMU_right_thigh->clear();
        comboBoxIMU_right_thigh->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM11", 0)
        );
        comboBoxIMU_left_shank->clear();
        comboBoxIMU_left_shank->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM12", 0)
        );
        comboBoxIMU_right_shank->clear();
        comboBoxIMU_right_shank->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "COM13", 0)
        );
        pushButton_deviceConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        label_6->setText(QApplication::translate("MainWindow", "Name", 0));
        lineEdit_username->setText(QApplication::translate("MainWindow", "William", 0));
        pushButton_newFile->setText(QApplication::translate("MainWindow", "NEW", 0));
        pushButton_saveFile->setText(QApplication::translate("MainWindow", "SAVE", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
