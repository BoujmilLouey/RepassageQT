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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
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
    QGroupBox *groupRechercheClients;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineRechercheNomClient;
    QLineEdit *lineRechercheEmailClient;
    QLineEdit *lineRechercheTelClient;
    QLabel *label_4;
    QComboBox *comboTriClient;
    QLabel *label_5;
    QComboBox *comboOrdreClient;
    QPushButton *btnRechercheClient;
    QPushButton *btnStatsClients;
    QPushButton *btnExporterClientsPdf;
    QPushButton *btnTotalDepenseClient;
    QPushButton *btnFideliteClient;
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
        tabWidget->setGeometry(QRect(10, 9, 791, 561));
        tabClients = new QWidget();
        tabClients->setObjectName("tabClients");
        lineIdClient = new QLineEdit(tabClients);
        lineIdClient->setObjectName("lineIdClient");
        lineIdClient->setGeometry(QRect(90, 30, 113, 24));
        lineNomClient = new QLineEdit(tabClients);
        lineNomClient->setObjectName("lineNomClient");
        lineNomClient->setGeometry(QRect(90, 60, 113, 24));
        linePrenomClient = new QLineEdit(tabClients);
        linePrenomClient->setObjectName("linePrenomClient");
        linePrenomClient->setGeometry(QRect(90, 90, 113, 24));
        lineEmailClient = new QLineEdit(tabClients);
        lineEmailClient->setObjectName("lineEmailClient");
        lineEmailClient->setGeometry(QRect(90, 120, 113, 24));
        lineTelClient = new QLineEdit(tabClients);
        lineTelClient->setObjectName("lineTelClient");
        lineTelClient->setGeometry(QRect(90, 150, 113, 24));
        lineAdresseClient = new QLineEdit(tabClients);
        lineAdresseClient->setObjectName("lineAdresseClient");
        lineAdresseClient->setGeometry(QRect(90, 180, 113, 24));
        ID = new QLabel(tabClients);
        ID->setObjectName("ID");
        ID->setGeometry(QRect(20, 30, 61, 20));
        Nom = new QLabel(tabClients);
        Nom->setObjectName("Nom");
        Nom->setGeometry(QRect(20, 60, 49, 16));
        Prenom = new QLabel(tabClients);
        Prenom->setObjectName("Prenom");
        Prenom->setGeometry(QRect(20, 90, 49, 16));
        Email = new QLabel(tabClients);
        Email->setObjectName("Email");
        Email->setGeometry(QRect(20, 120, 49, 16));
        Telephone = new QLabel(tabClients);
        Telephone->setObjectName("Telephone");
        Telephone->setGeometry(QRect(20, 150, 61, 20));
        Adresse = new QLabel(tabClients);
        Adresse->setObjectName("Adresse");
        Adresse->setGeometry(QRect(20, 180, 49, 16));
        btnModifierClient = new QPushButton(tabClients);
        btnModifierClient->setObjectName("btnModifierClient");
        btnModifierClient->setGeometry(QRect(600, 410, 80, 24));
        btnSupprimerClient = new QPushButton(tabClients);
        btnSupprimerClient->setObjectName("btnSupprimerClient");
        btnSupprimerClient->setGeometry(QRect(680, 410, 80, 24));
        btnAjouterClient = new QPushButton(tabClients);
        btnAjouterClient->setObjectName("btnAjouterClient");
        btnAjouterClient->setGeometry(QRect(520, 410, 80, 24));
        tableViewClients = new QTableView(tabClients);
        tableViewClients->setObjectName("tableViewClients");
        tableViewClients->setGeometry(QRect(300, 40, 471, 351));
        groupRechercheClients = new QGroupBox(tabClients);
        groupRechercheClients->setObjectName("groupRechercheClients");
        groupRechercheClients->setGeometry(QRect(10, 219, 251, 291));
        label = new QLabel(groupRechercheClients);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 81, 16));
        label_2 = new QLabel(groupRechercheClients);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 70, 91, 16));
        label_3 = new QLabel(groupRechercheClients);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 110, 111, 16));
        lineRechercheNomClient = new QLineEdit(groupRechercheClients);
        lineRechercheNomClient->setObjectName("lineRechercheNomClient");
        lineRechercheNomClient->setGeometry(QRect(130, 30, 113, 24));
        lineRechercheEmailClient = new QLineEdit(groupRechercheClients);
        lineRechercheEmailClient->setObjectName("lineRechercheEmailClient");
        lineRechercheEmailClient->setGeometry(QRect(130, 80, 113, 24));
        lineRechercheTelClient = new QLineEdit(groupRechercheClients);
        lineRechercheTelClient->setObjectName("lineRechercheTelClient");
        lineRechercheTelClient->setGeometry(QRect(130, 130, 113, 24));
        label_4 = new QLabel(groupRechercheClients);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(10, 210, 49, 16));
        comboTriClient = new QComboBox(groupRechercheClients);
        comboTriClient->addItem(QString());
        comboTriClient->addItem(QString());
        comboTriClient->addItem(QString());
        comboTriClient->setObjectName("comboTriClient");
        comboTriClient->setGeometry(QRect(70, 210, 131, 24));
        label_5 = new QLabel(groupRechercheClients);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(10, 250, 49, 16));
        comboOrdreClient = new QComboBox(groupRechercheClients);
        comboOrdreClient->addItem(QString());
        comboOrdreClient->addItem(QString());
        comboOrdreClient->setObjectName("comboOrdreClient");
        comboOrdreClient->setGeometry(QRect(70, 250, 131, 24));
        btnRechercheClient = new QPushButton(groupRechercheClients);
        btnRechercheClient->setObjectName("btnRechercheClient");
        btnRechercheClient->setGeometry(QRect(90, 170, 80, 24));
        btnStatsClients = new QPushButton(tabClients);
        btnStatsClients->setObjectName("btnStatsClients");
        btnStatsClients->setGeometry(QRect(640, 460, 121, 24));
        btnExporterClientsPdf = new QPushButton(tabClients);
        btnExporterClientsPdf->setObjectName("btnExporterClientsPdf");
        btnExporterClientsPdf->setGeometry(QRect(520, 460, 121, 24));
        btnTotalDepenseClient = new QPushButton(tabClients);
        btnTotalDepenseClient->setObjectName("btnTotalDepenseClient");
        btnTotalDepenseClient->setGeometry(QRect(400, 460, 121, 24));
        btnFideliteClient = new QPushButton(tabClients);
        btnFideliteClient->setObjectName("btnFideliteClient");
        btnFideliteClient->setGeometry(QRect(280, 460, 121, 24));
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
        groupRechercheClients->setTitle(QCoreApplication::translate("MainWindow", "Recherche / Tri", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom contient :", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Email contient :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone contient :", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Trier par :", nullptr));
        comboTriClient->setItemText(0, QCoreApplication::translate("MainWindow", "Nom", nullptr));
        comboTriClient->setItemText(1, QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        comboTriClient->setItemText(2, QCoreApplication::translate("MainWindow", "Email", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "Ordre :", nullptr));
        comboOrdreClient->setItemText(0, QCoreApplication::translate("MainWindow", "Croissant", nullptr));
        comboOrdreClient->setItemText(1, QCoreApplication::translate("MainWindow", "D\303\251croissant", nullptr));

        btnRechercheClient->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        btnStatsClients->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        btnExporterClientsPdf->setText(QCoreApplication::translate("MainWindow", "Exporter en PDF", nullptr));
        btnTotalDepenseClient->setText(QCoreApplication::translate("MainWindow", "Total d\303\251pens\303\251", nullptr));
        btnFideliteClient->setText(QCoreApplication::translate("MainWindow", "Niveau fid\303\251lit\303\251", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClients), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCommandes), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
