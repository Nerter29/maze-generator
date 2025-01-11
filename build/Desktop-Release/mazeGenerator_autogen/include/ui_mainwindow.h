/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *mazeGraphicView;
    QLineEdit *delayLineEdit;
    QLabel *delayLabel;
    QLineEdit *mazeRowsLineEdit;
    QPushButton *createButton;
    QLabel *mazeRowsLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #111111"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mazeGraphicView = new QGraphicsView(centralwidget);
        mazeGraphicView->setObjectName("mazeGraphicView");
        mazeGraphicView->setGeometry(QRect(10, -10, 831, 571));
        mazeGraphicView->setStyleSheet(QString::fromUtf8("background-color: #000000"));
        delayLineEdit = new QLineEdit(centralwidget);
        delayLineEdit->setObjectName("delayLineEdit");
        delayLineEdit->setGeometry(QRect(650, 50, 60, 25));
        QFont font;
        font.setFamilies({QString::fromUtf8("Renogare")});
        font.setPointSize(12);
        delayLineEdit->setFont(font);
        delayLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	background-color: #cccccc;\n"
"	color:  #1a1a1a;\n"
"	border-radius: 5px;\n"
" 	border: 2px solid #222222;\n"
"	padding: 0 0 2px\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"	background-color: #eeeeee;\n"
" 	border: 2px solid #666666;\n"
"}\n"
"QLineEdit:focus {\n"
"	background-color: #eeeeee;\n"
" 	border: 2px solid #666666;}"));
        delayLabel = new QLabel(centralwidget);
        delayLabel->setObjectName("delayLabel");
        delayLabel->setGeometry(QRect(360, 50, 205, 20));
        delayLabel->setFont(font);
        delayLabel->setStyleSheet(QString::fromUtf8("	color: #eee;\n"
""));
        mazeRowsLineEdit = new QLineEdit(centralwidget);
        mazeRowsLineEdit->setObjectName("mazeRowsLineEdit");
        mazeRowsLineEdit->setGeometry(QRect(620, 10, 60, 25));
        mazeRowsLineEdit->setFont(font);
        mazeRowsLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"	background-color: #cccccc;\n"
"	color:  #1a1a1a;\n"
"	border-radius: 5px;\n"
" 	border: 2px solid #222222;\n"
"	padding: 0 0 2px\n"
"}\n"
"\n"
"QLineEdit:hover {\n"
"	background-color: #eeeeee;\n"
" 	border: 2px solid #666666;\n"
"}\n"
"QLineEdit:focus {\n"
"	background-color: #eeeeee;\n"
" 	border: 2px solid #666666;}"));
        mazeRowsLineEdit->setFrame(true);
        createButton = new QPushButton(centralwidget);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(130, 20, 90, 40));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createButton->sizePolicy().hasHeightForWidth());
        createButton->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Renogare")});
        font1.setPointSize(16);
        createButton->setFont(font1);
        createButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: #cccccc;\n"
"	color:  #1a1a1a;\n"
"	border-radius: 5px;\n"
" 	border: 2px solid #222222;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"	background-color: #eeeeee;\n"
" 	border: 2px solid #666666;\n"
"}\n"
""));
        mazeRowsLabel = new QLabel(centralwidget);
        mazeRowsLabel->setObjectName("mazeRowsLabel");
        mazeRowsLabel->setGeometry(QRect(360, 10, 181, 20));
        mazeRowsLabel->setFont(font);
        mazeRowsLabel->setStyleSheet(QString::fromUtf8("	color: #eee;\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        delayLineEdit->setText(QString());
        delayLabel->setText(QCoreApplication::translate("MainWindow", "D\303\251lai en millisecondes :", nullptr));
        createButton->setText(QCoreApplication::translate("MainWindow", "Cr\303\251er", nullptr));
        mazeRowsLabel->setText(QCoreApplication::translate("MainWindow", "Nombre de Colones :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
