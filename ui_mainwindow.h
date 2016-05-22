/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qimagelabel.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *LE_img_path;
    QPushButton *PB_load;
    QImageLabel *QL_imgview;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *LE_curr;
    QLineEdit *LE_start;
    QVBoxLayout *verticalLayout_3;
    QPushButton *PB_start;
    QPushButton *PB_reset;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *LE_goal;
    QLineEdit *LE_status;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpinBox *SB_max_nodes;
    QLabel *label_6;
    QSpinBox *SB_goal_radius;
    QLabel *label_7;
    QSpinBox *SB_new_state_dis;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(790, 822);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        LE_img_path = new QLineEdit(centralWidget);
        LE_img_path->setObjectName(QStringLiteral("LE_img_path"));

        horizontalLayout->addWidget(LE_img_path);

        PB_load = new QPushButton(centralWidget);
        PB_load->setObjectName(QStringLiteral("PB_load"));

        horizontalLayout->addWidget(PB_load);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        QL_imgview = new QImageLabel(centralWidget);
        QL_imgview->setObjectName(QStringLiteral("QL_imgview"));
        QL_imgview->setAutoFillBackground(true);

        gridLayout->addWidget(QL_imgview, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        LE_curr = new QLineEdit(centralWidget);
        LE_curr->setObjectName(QStringLiteral("LE_curr"));

        verticalLayout->addWidget(LE_curr);

        LE_start = new QLineEdit(centralWidget);
        LE_start->setObjectName(QStringLiteral("LE_start"));

        verticalLayout->addWidget(LE_start);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        PB_start = new QPushButton(centralWidget);
        PB_start->setObjectName(QStringLiteral("PB_start"));

        verticalLayout_3->addWidget(PB_start);

        PB_reset = new QPushButton(centralWidget);
        PB_reset->setObjectName(QStringLiteral("PB_reset"));

        verticalLayout_3->addWidget(PB_reset);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_4->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        LE_goal = new QLineEdit(centralWidget);
        LE_goal->setObjectName(QStringLiteral("LE_goal"));

        verticalLayout_5->addWidget(LE_goal);

        LE_status = new QLineEdit(centralWidget);
        LE_status->setObjectName(QStringLiteral("LE_status"));

        verticalLayout_5->addWidget(LE_status);


        horizontalLayout_2->addLayout(verticalLayout_5);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        SB_max_nodes = new QSpinBox(centralWidget);
        SB_max_nodes->setObjectName(QStringLiteral("SB_max_nodes"));
        SB_max_nodes->setMaximum(100000);

        horizontalLayout_3->addWidget(SB_max_nodes);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_3->addWidget(label_6);

        SB_goal_radius = new QSpinBox(centralWidget);
        SB_goal_radius->setObjectName(QStringLiteral("SB_goal_radius"));
        SB_goal_radius->setMaximum(1000);

        horizontalLayout_3->addWidget(SB_goal_radius);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7);

        SB_new_state_dis = new QSpinBox(centralWidget);
        SB_new_state_dis->setObjectName(QStringLiteral("SB_new_state_dis"));
        SB_new_state_dis->setMaximum(10000);

        horizontalLayout_3->addWidget(SB_new_state_dis);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        gridLayout->setRowStretch(1, 9);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 790, 25));
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
        PB_load->setText(QApplication::translate("MainWindow", "Load", 0));
        QL_imgview->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Current position (x,y)", 0));
        label_2->setText(QApplication::translate("MainWindow", "Start position (x,y)", 0));
        PB_start->setText(QApplication::translate("MainWindow", "Start", 0));
        PB_reset->setText(QApplication::translate("MainWindow", "Reset", 0));
        label_3->setText(QApplication::translate("MainWindow", "Goal position (x,y)", 0));
        label_4->setText(QApplication::translate("MainWindow", "Status Msg:", 0));
        label_5->setText(QApplication::translate("MainWindow", "Max Nodes", 0));
        label_6->setText(QApplication::translate("MainWindow", "Goal Radius", 0));
        label_7->setText(QApplication::translate("MainWindow", "Distance of new state", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
