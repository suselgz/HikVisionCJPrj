/********************************************************************************
** Form generated from reading UI file 'QHikVisionTest.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHIKVISIONTEST_H
#define UI_QHIKVISIONTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QHikVisionTestClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_Init;
    QPushButton *pushButton_softTrigger;
    QPushButton *pushButton_close;
    QGroupBox *groupBox_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QHikVisionTestClass)
    {
        if (QHikVisionTestClass->objectName().isEmpty())
            QHikVisionTestClass->setObjectName(QStringLiteral("QHikVisionTestClass"));
        QHikVisionTestClass->resize(568, 339);
        centralWidget = new QWidget(QHikVisionTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_Init = new QPushButton(groupBox);
        pushButton_Init->setObjectName(QStringLiteral("pushButton_Init"));

        verticalLayout->addWidget(pushButton_Init);

        pushButton_softTrigger = new QPushButton(groupBox);
        pushButton_softTrigger->setObjectName(QStringLiteral("pushButton_softTrigger"));

        verticalLayout->addWidget(pushButton_softTrigger);

        pushButton_close = new QPushButton(groupBox);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));

        verticalLayout->addWidget(pushButton_close);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));

        horizontalLayout->addWidget(groupBox_2);

        QHikVisionTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QHikVisionTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 568, 23));
        QHikVisionTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QHikVisionTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QHikVisionTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QHikVisionTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QHikVisionTestClass->setStatusBar(statusBar);

        retranslateUi(QHikVisionTestClass);

        QMetaObject::connectSlotsByName(QHikVisionTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QHikVisionTestClass)
    {
        QHikVisionTestClass->setWindowTitle(QApplication::translate("QHikVisionTestClass", "QHikVisionTest", 0));
        groupBox->setTitle(QApplication::translate("QHikVisionTestClass", "GroupBox", 0));
        pushButton_Init->setText(QApplication::translate("QHikVisionTestClass", "\345\210\235\345\247\213\345\214\226\347\233\270\346\234\272", 0));
        pushButton_softTrigger->setText(QApplication::translate("QHikVisionTestClass", "\350\275\257\350\247\246\345\217\221\351\207\207\351\233\206", 0));
        pushButton_close->setText(QApplication::translate("QHikVisionTestClass", "\345\205\263\351\227\255\347\233\270\346\234\272", 0));
        groupBox_2->setTitle(QApplication::translate("QHikVisionTestClass", "GroupBox", 0));
    } // retranslateUi

};

namespace Ui {
    class QHikVisionTestClass: public Ui_QHikVisionTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHIKVISIONTEST_H
