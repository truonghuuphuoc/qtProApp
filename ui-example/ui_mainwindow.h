/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_27;
    QGridLayout *gridLayout_26;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_21;
    QGridLayout *gridLayout_22;
    QLabel *mAppComport;
    QGroupBox *groupBox_22;
    QGridLayout *gridLayout_23;
    QLabel *mAddressStart;
    QGroupBox *groupBox_23;
    QGridLayout *gridLayout_24;
    QLabel *mAddressDest;
    QGroupBox *groupBox_24;
    QGridLayout *gridLayout_25;
    QPushButton *mAppClean;
    QGroupBox *groupBox_20;
    QGridLayout *gridLayout_21;
    QLabel *mAppStatus;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_6;
    QLabel *mTarget_1_ThirdValue;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_7;
    QLabel *mTarget_1_TotalValue;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QLabel *mTarget_1_SecondValue;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    QLabel *mTarget_1_Status;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QLabel *mTarget_1_FirstValue;
    QPushButton *mTarget_1_Clean;
    QLabel *label_20;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_9;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_10;
    QLabel *mTarget_2_SecondValue;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_11;
    QLabel *mTarget_2_Status;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_13;
    QLabel *mTarget_2_ThirdValue;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_12;
    QLabel *mTarget_2_TotalValue;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_14;
    QLabel *mTarget_2_FirstValue;
    QPushButton *mTarget_2_Clean;
    QLabel *label_21;
    QGroupBox *groupBox_14;
    QGridLayout *gridLayout_15;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout_16;
    QLabel *mTarget_3_SecondValue;
    QGroupBox *groupBox_18;
    QGridLayout *gridLayout_19;
    QLabel *mTarget_3_ThirdValue;
    QGroupBox *groupBox_16;
    QGridLayout *gridLayout_17;
    QLabel *mTarget_3_Status;
    QGroupBox *groupBox_17;
    QGridLayout *gridLayout_18;
    QLabel *mTarget_3_TotalValue;
    QGroupBox *groupBox_19;
    QGridLayout *gridLayout_20;
    QLabel *mTarget_3_FirstValue;
    QPushButton *mTarget_3_Clean;
    QLabel *label_22;
    QWidget *tab_2;
    QGridLayout *gridLayout_28;
    QTableWidget *tableWidget;
    QPushButton *pushButton;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(976, 692);
        QIcon icon;
        icon.addFile(QStringLiteral("system/image/app_100.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_27 = new QGridLayout(tab);
        gridLayout_27->setSpacing(6);
        gridLayout_27->setContentsMargins(11, 11, 11, 11);
        gridLayout_27->setObjectName(QStringLiteral("gridLayout_27"));
        gridLayout_26 = new QGridLayout();
        gridLayout_26->setSpacing(6);
        gridLayout_26->setObjectName(QStringLiteral("gridLayout_26"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 7px;\n"
"    margin-top: 0.7em;\n"
"	font-size: 12pt ;\n"
"    font-weight: bold;\n"
"	border-color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_21 = new QGroupBox(groupBox);
        groupBox_21->setObjectName(QStringLiteral("groupBox_21"));
        gridLayout_22 = new QGridLayout(groupBox_21);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QStringLiteral("gridLayout_22"));
        mAppComport = new QLabel(groupBox_21);
        mAppComport->setObjectName(QStringLiteral("mAppComport"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        mAppComport->setFont(font);
        mAppComport->setAlignment(Qt::AlignCenter);

        gridLayout_22->addWidget(mAppComport, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_21, 0, 1, 1, 1);

        groupBox_22 = new QGroupBox(groupBox);
        groupBox_22->setObjectName(QStringLiteral("groupBox_22"));
        gridLayout_23 = new QGridLayout(groupBox_22);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QStringLiteral("gridLayout_23"));
        mAddressStart = new QLabel(groupBox_22);
        mAddressStart->setObjectName(QStringLiteral("mAddressStart"));
        mAddressStart->setFont(font);
        mAddressStart->setAlignment(Qt::AlignCenter);

        gridLayout_23->addWidget(mAddressStart, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_22, 0, 2, 1, 1);

        groupBox_23 = new QGroupBox(groupBox);
        groupBox_23->setObjectName(QStringLiteral("groupBox_23"));
        gridLayout_24 = new QGridLayout(groupBox_23);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QStringLiteral("gridLayout_24"));
        mAddressDest = new QLabel(groupBox_23);
        mAddressDest->setObjectName(QStringLiteral("mAddressDest"));
        mAddressDest->setFont(font);
        mAddressDest->setAlignment(Qt::AlignCenter);

        gridLayout_24->addWidget(mAddressDest, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_23, 0, 3, 1, 1);

        groupBox_24 = new QGroupBox(groupBox);
        groupBox_24->setObjectName(QStringLiteral("groupBox_24"));
        gridLayout_25 = new QGridLayout(groupBox_24);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QStringLiteral("gridLayout_25"));
        mAppClean = new QPushButton(groupBox_24);
        mAppClean->setObjectName(QStringLiteral("mAppClean"));
        QFont font1;
        font1.setPointSize(11);
        mAppClean->setFont(font1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/24/Delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        mAppClean->setIcon(icon1);
        mAppClean->setIconSize(QSize(27, 27));

        gridLayout_25->addWidget(mAppClean, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_24, 0, 4, 1, 1);

        groupBox_20 = new QGroupBox(groupBox);
        groupBox_20->setObjectName(QStringLiteral("groupBox_20"));
        gridLayout_21 = new QGridLayout(groupBox_20);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QStringLiteral("gridLayout_21"));
        mAppStatus = new QLabel(groupBox_20);
        mAppStatus->setObjectName(QStringLiteral("mAppStatus"));
        mAppStatus->setPixmap(QPixmap(QString::fromUtf8(":/icons/24/Close.png")));
        mAppStatus->setAlignment(Qt::AlignCenter);

        gridLayout_21->addWidget(mAppStatus, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox_20, 0, 0, 1, 1);


        gridLayout_26->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_27->addLayout(gridLayout_26, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 7px;\n"
"    margin-top: 0.7em;\n"
"	font-size: 12pt ;\n"
"    font-weight: bold;\n"
"	border-color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_6 = new QGridLayout(groupBox_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        mTarget_1_ThirdValue = new QLabel(groupBox_5);
        mTarget_1_ThirdValue->setObjectName(QStringLiteral("mTarget_1_ThirdValue"));
        QFont font2;
        font2.setPointSize(24);
        mTarget_1_ThirdValue->setFont(font2);
        mTarget_1_ThirdValue->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(mTarget_1_ThirdValue, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_5, 3, 0, 1, 1);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_7 = new QGridLayout(groupBox_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        mTarget_1_TotalValue = new QLabel(groupBox_6);
        mTarget_1_TotalValue->setObjectName(QStringLiteral("mTarget_1_TotalValue"));
        mTarget_1_TotalValue->setFont(font2);
        mTarget_1_TotalValue->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(mTarget_1_TotalValue, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_6, 4, 0, 1, 1);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        mTarget_1_SecondValue = new QLabel(groupBox_4);
        mTarget_1_SecondValue->setObjectName(QStringLiteral("mTarget_1_SecondValue"));
        mTarget_1_SecondValue->setFont(font2);
        mTarget_1_SecondValue->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(mTarget_1_SecondValue, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_4, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        mTarget_1_Status = new QLabel(groupBox_3);
        mTarget_1_Status->setObjectName(QStringLiteral("mTarget_1_Status"));
        mTarget_1_Status->setPixmap(QPixmap(QString::fromUtf8(":/icons/24/Close.png")));
        mTarget_1_Status->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(mTarget_1_Status, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        mTarget_1_FirstValue = new QLabel(groupBox_7);
        mTarget_1_FirstValue->setObjectName(QStringLiteral("mTarget_1_FirstValue"));
        mTarget_1_FirstValue->setFont(font2);
        mTarget_1_FirstValue->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(mTarget_1_FirstValue, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_7, 1, 0, 1, 1);

        mTarget_1_Clean = new QPushButton(groupBox_2);
        mTarget_1_Clean->setObjectName(QStringLiteral("mTarget_1_Clean"));
        mTarget_1_Clean->setFont(font1);
        mTarget_1_Clean->setIcon(icon1);
        mTarget_1_Clean->setIconSize(QSize(27, 27));

        gridLayout_3->addWidget(mTarget_1_Clean, 6, 0, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        QFont font3;
        font3.setPointSize(14);
        label_20->setFont(font3);
        label_20->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_20, 5, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_2);

        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 7px;\n"
"    margin-top: 0.7em;\n"
"	font-size: 12pt ;\n"
"    font-weight: bold;\n"
"	border-color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        gridLayout_9 = new QGridLayout(groupBox_8);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_10 = new QGridLayout(groupBox_9);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        mTarget_2_SecondValue = new QLabel(groupBox_9);
        mTarget_2_SecondValue->setObjectName(QStringLiteral("mTarget_2_SecondValue"));
        mTarget_2_SecondValue->setFont(font2);
        mTarget_2_SecondValue->setAlignment(Qt::AlignCenter);

        gridLayout_10->addWidget(mTarget_2_SecondValue, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_9, 2, 0, 1, 1);

        groupBox_10 = new QGroupBox(groupBox_8);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_11 = new QGridLayout(groupBox_10);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        mTarget_2_Status = new QLabel(groupBox_10);
        mTarget_2_Status->setObjectName(QStringLiteral("mTarget_2_Status"));
        mTarget_2_Status->setPixmap(QPixmap(QString::fromUtf8(":/icons/24/Close.png")));
        mTarget_2_Status->setAlignment(Qt::AlignCenter);

        gridLayout_11->addWidget(mTarget_2_Status, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_10, 0, 0, 1, 1);

        groupBox_12 = new QGroupBox(groupBox_8);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_13 = new QGridLayout(groupBox_12);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        mTarget_2_ThirdValue = new QLabel(groupBox_12);
        mTarget_2_ThirdValue->setObjectName(QStringLiteral("mTarget_2_ThirdValue"));
        mTarget_2_ThirdValue->setFont(font2);
        mTarget_2_ThirdValue->setAlignment(Qt::AlignCenter);

        gridLayout_13->addWidget(mTarget_2_ThirdValue, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_12, 3, 0, 1, 1);

        groupBox_11 = new QGroupBox(groupBox_8);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_12 = new QGridLayout(groupBox_11);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        mTarget_2_TotalValue = new QLabel(groupBox_11);
        mTarget_2_TotalValue->setObjectName(QStringLiteral("mTarget_2_TotalValue"));
        mTarget_2_TotalValue->setFont(font2);
        mTarget_2_TotalValue->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(mTarget_2_TotalValue, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_11, 4, 0, 1, 1);

        groupBox_13 = new QGroupBox(groupBox_8);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_14 = new QGridLayout(groupBox_13);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        mTarget_2_FirstValue = new QLabel(groupBox_13);
        mTarget_2_FirstValue->setObjectName(QStringLiteral("mTarget_2_FirstValue"));
        mTarget_2_FirstValue->setFont(font2);
        mTarget_2_FirstValue->setAlignment(Qt::AlignCenter);

        gridLayout_14->addWidget(mTarget_2_FirstValue, 0, 0, 1, 1);


        gridLayout_9->addWidget(groupBox_13, 1, 0, 1, 1);

        mTarget_2_Clean = new QPushButton(groupBox_8);
        mTarget_2_Clean->setObjectName(QStringLiteral("mTarget_2_Clean"));
        mTarget_2_Clean->setFont(font1);
        mTarget_2_Clean->setIcon(icon1);
        mTarget_2_Clean->setIconSize(QSize(27, 27));

        gridLayout_9->addWidget(mTarget_2_Clean, 6, 0, 1, 1);

        label_21 = new QLabel(groupBox_8);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setFont(font3);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_21, 5, 0, 1, 1);


        horizontalLayout_2->addWidget(groupBox_8);

        groupBox_14 = new QGroupBox(tab);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 7px;\n"
"    margin-top: 0.7em;\n"
"	font-size: 12pt ;\n"
"    font-weight: bold;\n"
"	border-color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        gridLayout_15 = new QGridLayout(groupBox_14);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        groupBox_15 = new QGroupBox(groupBox_14);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        groupBox_15->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_16 = new QGridLayout(groupBox_15);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        mTarget_3_SecondValue = new QLabel(groupBox_15);
        mTarget_3_SecondValue->setObjectName(QStringLiteral("mTarget_3_SecondValue"));
        mTarget_3_SecondValue->setFont(font2);
        mTarget_3_SecondValue->setAlignment(Qt::AlignCenter);

        gridLayout_16->addWidget(mTarget_3_SecondValue, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_15, 2, 1, 1, 1);

        groupBox_18 = new QGroupBox(groupBox_14);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        groupBox_18->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_19 = new QGridLayout(groupBox_18);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        mTarget_3_ThirdValue = new QLabel(groupBox_18);
        mTarget_3_ThirdValue->setObjectName(QStringLiteral("mTarget_3_ThirdValue"));
        mTarget_3_ThirdValue->setFont(font2);
        mTarget_3_ThirdValue->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(mTarget_3_ThirdValue, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_18, 3, 1, 1, 1);

        groupBox_16 = new QGroupBox(groupBox_14);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        groupBox_16->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_17 = new QGridLayout(groupBox_16);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        mTarget_3_Status = new QLabel(groupBox_16);
        mTarget_3_Status->setObjectName(QStringLiteral("mTarget_3_Status"));
        mTarget_3_Status->setPixmap(QPixmap(QString::fromUtf8(":/icons/24/Close.png")));
        mTarget_3_Status->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(mTarget_3_Status, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_16, 0, 1, 1, 1);

        groupBox_17 = new QGroupBox(groupBox_14);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        groupBox_17->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_18 = new QGridLayout(groupBox_17);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        mTarget_3_TotalValue = new QLabel(groupBox_17);
        mTarget_3_TotalValue->setObjectName(QStringLiteral("mTarget_3_TotalValue"));
        mTarget_3_TotalValue->setFont(font2);
        mTarget_3_TotalValue->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(mTarget_3_TotalValue, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_17, 4, 1, 1, 1);

        groupBox_19 = new QGroupBox(groupBox_14);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        groupBox_19->setStyleSheet(QLatin1String("QGroupBox {\n"
"    font-size: 12pt ;\n"
"	border-color: rgb(135, 135, 135);\n"
"}\n"
""));
        gridLayout_20 = new QGridLayout(groupBox_19);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QStringLiteral("gridLayout_20"));
        mTarget_3_FirstValue = new QLabel(groupBox_19);
        mTarget_3_FirstValue->setObjectName(QStringLiteral("mTarget_3_FirstValue"));
        mTarget_3_FirstValue->setFont(font2);
        mTarget_3_FirstValue->setAlignment(Qt::AlignCenter);

        gridLayout_20->addWidget(mTarget_3_FirstValue, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_19, 1, 1, 1, 1);

        mTarget_3_Clean = new QPushButton(groupBox_14);
        mTarget_3_Clean->setObjectName(QStringLiteral("mTarget_3_Clean"));
        mTarget_3_Clean->setFont(font1);
        mTarget_3_Clean->setIcon(icon1);
        mTarget_3_Clean->setIconSize(QSize(27, 27));

        gridLayout_15->addWidget(mTarget_3_Clean, 6, 1, 1, 1);

        label_22 = new QLabel(groupBox_14);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setFont(font3);
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_22, 5, 1, 1, 1);


        horizontalLayout_2->addWidget(groupBox_14);


        gridLayout_27->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_28 = new QGridLayout(tab_2);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QStringLiteral("gridLayout_28"));
        tableWidget = new QTableWidget(tab_2);
        if (tableWidget->columnCount() < 14)
            tableWidget->setColumnCount(14);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(12, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(13, __qtablewidgetitem13);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(14);

        gridLayout_28->addWidget(tableWidget, 2, 0, 1, 1);

        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);

        gridLayout_28->addWidget(pushButton, 0, 0, 1, 1);

        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_28->addWidget(label, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 976, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TARGET", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Tr\341\272\241ng Th\303\241i", Q_NULLPTR));
        groupBox_21->setTitle(QApplication::translate("MainWindow", "C\341\273\225ng COM", Q_NULLPTR));
        mAppComport->setText(QString());
        groupBox_22->setTitle(QApplication::translate("MainWindow", "ID Thu", Q_NULLPTR));
        mAddressStart->setText(QString());
        groupBox_23->setTitle(QApplication::translate("MainWindow", "ID Ph\303\241t", Q_NULLPTR));
        mAddressDest->setText(QString());
        groupBox_24->setTitle(QApplication::translate("MainWindow", "X\303\263a d\341\273\257 li\341\273\207u", Q_NULLPTR));
        mAppClean->setText(QApplication::translate("MainWindow", "X\303\263a", Q_NULLPTR));
        groupBox_20->setTitle(QApplication::translate("MainWindow", "K\341\272\277t n\341\273\221i", Q_NULLPTR));
        mAppStatus->setText(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Bia s\341\273\221 4", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 3", Q_NULLPTR));
        mTarget_1_ThirdValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "T\341\273\225ng", Q_NULLPTR));
        mTarget_1_TotalValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 2", Q_NULLPTR));
        mTarget_1_SecondValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "K\341\272\277t n\341\273\221i", Q_NULLPTR));
        mTarget_1_Status->setText(QString());
        groupBox_7->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 1", Q_NULLPTR));
        mTarget_1_FirstValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        mTarget_1_Clean->setText(QApplication::translate("MainWindow", "X\303\263a", Q_NULLPTR));
        label_20->setText(QString());
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Bia s\341\273\221 7", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 2", Q_NULLPTR));
        mTarget_2_SecondValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "K\341\272\277t n\341\273\221i", Q_NULLPTR));
        mTarget_2_Status->setText(QString());
        groupBox_12->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 3", Q_NULLPTR));
        mTarget_2_ThirdValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "T\341\273\225ng", Q_NULLPTR));
        mTarget_2_TotalValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 1", Q_NULLPTR));
        mTarget_2_FirstValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        mTarget_2_Clean->setText(QApplication::translate("MainWindow", "X\303\263a", Q_NULLPTR));
        label_21->setText(QString());
        groupBox_14->setTitle(QApplication::translate("MainWindow", "Bia s\341\273\221 8", Q_NULLPTR));
        groupBox_15->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 2", Q_NULLPTR));
        mTarget_3_SecondValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_18->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 3", Q_NULLPTR));
        mTarget_3_ThirdValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_16->setTitle(QApplication::translate("MainWindow", "K\341\272\277t n\341\273\221i", Q_NULLPTR));
        mTarget_3_Status->setText(QString());
        groupBox_17->setTitle(QApplication::translate("MainWindow", "T\341\273\225ng", Q_NULLPTR));
        mTarget_3_TotalValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        groupBox_19->setTitle(QApplication::translate("MainWindow", "L\341\272\247n 1", Q_NULLPTR));
        mTarget_3_FirstValue->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        mTarget_3_Clean->setText(QApplication::translate("MainWindow", "X\303\263a", Q_NULLPTR));
        label_22->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\304\220i\341\273\203m bia", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "STT", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "T\303\252n", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "B\341\273\207", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "B4 - L\341\272\247n 1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "B4 - L\341\272\247n 2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "B4 - L\341\272\247n 3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "B7 - L\341\272\247n 1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "B7 - L\341\272\247n 2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "B7 - L\341\272\247n 3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "B8 - L\341\272\247n 1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "B8 - L\341\272\247n 2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "B8 - L\341\272\247n 3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(12);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "T\341\273\225ng", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->horizontalHeaderItem(13);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "X\341\272\277p Lo\341\272\241i", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "L\306\260u", Q_NULLPTR));
        label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "K\341\272\277t qu\341\272\243", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
