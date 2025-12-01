/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabClients;
    QLineEdit *lineIdClient;
    QLineEdit *lineNomClient;
    QLineEdit *linePrenomClient;
    QLineEdit *lineEmailClient;
    QLineEdit *lineTelClient;
    QLineEdit *lineAdresseClient;
    QLabel *ID;
    QLabel *Nom;
    QLabel *Prenom;
    QLabel *Email;
    QLabel *Telephone;
    QLabel *Adresse;
    QPushButton *btnModifierClient;
    QPushButton *btnSupprimerClient;
    QPushButton *btnAjouterClient;
    QTableView *tableViewClients;
    QWidget *tabCommandes;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(120, 120, 511, 301));
        tabClients = new QWidget();
        tabClients->setObjectName("tabClients");
        lineIdClient = new QLineEdit(tabClients);
        lineIdClient->setObjectName("lineIdClient");
        lineIdClient->setGeometry(QRect(90, 50, 113, 24));
        lineNomClient = new QLineEdit(tabClients);
        lineNomClient->setObjectName("lineNomClient");
        lineNomClient->setGeometry(QRect(90, 80, 113, 24));
        linePrenomClient = new QLineEdit(tabClients);
        linePrenomClient->setObjectName("linePrenomClient");
        linePrenomClient->setGeometry(QRect(90, 110, 113, 24));
        lineEmailClient = new QLineEdit(tabClients);
        lineEmailClient->setObjectName("lineEmailClient");
        lineEmailClient->setGeometry(QRect(90, 140, 113, 24));
        lineTelClient = new QLineEdit(tabClients);
        lineTelClient->setObjectName("lineTelClient");
        lineTelClient->setGeometry(QRect(90, 170, 113, 24));
        lineAdresseClient = new QLineEdit(tabClients);
        lineAdresseClient->setObjectName("lineAdresseClient");
        lineAdresseClient->setGeometry(QRect(90, 200, 113, 24));
        ID = new QLabel(tabClients);
        ID->setObjectName("ID");
        ID->setGeometry(QRect(20, 50, 61, 20));
        Nom = new QLabel(tabClients);
        Nom->setObjectName("Nom");
        Nom->setGeometry(QRect(20, 80, 49, 16));
        Prenom = new QLabel(tabClients);
        Prenom->setObjectName("Prenom");
        Prenom->setGeometry(QRect(20, 110, 49, 16));
        Email = new QLabel(tabClients);
        Email->setObjectName("Email");
        Email->setGeometry(QRect(20, 140, 49, 16));
        Telephone = new QLabel(tabClients);
        Telephone->setObjectName("Telephone");
        Telephone->setGeometry(QRect(20, 170, 61, 20));
        Adresse = new QLabel(tabClients);
        Adresse->setObjectName("Adresse");
        Adresse->setGeometry(QRect(20, 200, 49, 16));
        btnModifierClient = new QPushButton(tabClients);
        btnModifierClient->setObjectName("btnModifierClient");
        btnModifierClient->setGeometry(QRect(330, 240, 80, 24));
        btnSupprimerClient = new QPushButton(tabClients);
        btnSupprimerClient->setObjectName("btnSupprimerClient");
        btnSupprimerClient->setGeometry(QRect(410, 240, 80, 24));
        btnAjouterClient = new QPushButton(tabClients);
        btnAjouterClient->setObjectName("btnAjouterClient");
        btnAjouterClient->setGeometry(QRect(250, 240, 80, 24));
        tableViewClients = new QTableView(tabClients);
        tableViewClients->setObjectName("tableViewClients");
        tableViewClients->setGeometry(QRect(220, 30, 271, 201));
        tabWidget->addTab(tabClients, QString());
        tabCommandes = new QWidget();
        tabCommandes->setObjectName("tabCommandes");
        tabWidget->addTab(tabCommandes, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineIdClient->setText(QString());
        lineNomClient->setText(QString());
        linePrenomClient->setText(QString());
        lineEmailClient->setText(QString());
        lineTelClient->setText(QString());
        lineAdresseClient->setText(QString());
        ID->setText(QCoreApplication::translate("MainWindow", "ID Client :", nullptr));
        Nom->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        Prenom->setText(QCoreApplication::translate("MainWindow", "Pr\303\251nom :", nullptr));
        Email->setText(QCoreApplication::translate("MainWindow", "Email :", nullptr));
        Telephone->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone :", nullptr));
        Adresse->setText(QCoreApplication::translate("MainWindow", "Adresse :", nullptr));
        btnModifierClient->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        btnSupprimerClient->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnAjouterClient->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCommandes), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
