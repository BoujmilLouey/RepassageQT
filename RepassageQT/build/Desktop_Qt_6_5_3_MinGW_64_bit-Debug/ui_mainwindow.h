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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *lineIdCommande;
    QLineEdit *lineMontantCommande;
    QLineEdit *lineIdClientCommande;
    QDateEdit *dateCommande;
    QComboBox *comboStatutCommande;
    QComboBox *comboModePaiement;
    QTableView *tableViewCommandes;
    QPushButton *btnAjouterCommande;
    QPushButton *btnSupprimerCommande;
    QPushButton *btnModifierCommande;
    QGroupBox *groupBox;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QDateEdit *dateMinCommande;
    QDateEdit *dateMaxCommande;
    QComboBox *comboModePaiementFiltre;
    QLineEdit *lineIdClientFiltreCommande;
    QPushButton *btnRechercheCommande;
    QLabel *label_16;
    QLabel *label_17;
    QComboBox *comboTriCommande;
    QComboBox *comboOrdreCommande;
    QPushButton *btnExporterCommandesPdf;
    QPushButton *btnCommandesPourClient;
    QPushButton *btnStatsCommandes;
    QPushButton *btnChiffreAffairesTotal;
    QMenuBar *menubar;
    QMenu *menuRattrappage;
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
        label_6 = new QLabel(tabCommandes);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 30, 91, 16));
        label_7 = new QLabel(tabCommandes);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 60, 101, 16));
        label_8 = new QLabel(tabCommandes);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(20, 90, 91, 16));
        label_9 = new QLabel(tabCommandes);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(20, 120, 61, 16));
        label_10 = new QLabel(tabCommandes);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 150, 111, 16));
        label_11 = new QLabel(tabCommandes);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(20, 180, 61, 16));
        lineIdCommande = new QLineEdit(tabCommandes);
        lineIdCommande->setObjectName("lineIdCommande");
        lineIdCommande->setGeometry(QRect(140, 30, 113, 24));
        lineMontantCommande = new QLineEdit(tabCommandes);
        lineMontantCommande->setObjectName("lineMontantCommande");
        lineMontantCommande->setGeometry(QRect(140, 90, 113, 24));
        lineIdClientCommande = new QLineEdit(tabCommandes);
        lineIdClientCommande->setObjectName("lineIdClientCommande");
        lineIdClientCommande->setGeometry(QRect(140, 180, 113, 24));
        dateCommande = new QDateEdit(tabCommandes);
        dateCommande->setObjectName("dateCommande");
        dateCommande->setGeometry(QRect(140, 60, 111, 25));
        comboStatutCommande = new QComboBox(tabCommandes);
        comboStatutCommande->addItem(QString());
        comboStatutCommande->addItem(QString());
        comboStatutCommande->addItem(QString());
        comboStatutCommande->setObjectName("comboStatutCommande");
        comboStatutCommande->setGeometry(QRect(140, 120, 111, 24));
        comboModePaiement = new QComboBox(tabCommandes);
        comboModePaiement->addItem(QString());
        comboModePaiement->addItem(QString());
        comboModePaiement->addItem(QString());
        comboModePaiement->addItem(QString());
        comboModePaiement->addItem(QString());
        comboModePaiement->setObjectName("comboModePaiement");
        comboModePaiement->setGeometry(QRect(140, 150, 111, 24));
        tableViewCommandes = new QTableView(tabCommandes);
        tableViewCommandes->setObjectName("tableViewCommandes");
        tableViewCommandes->setGeometry(QRect(300, 40, 471, 331));
        btnAjouterCommande = new QPushButton(tabCommandes);
        btnAjouterCommande->setObjectName("btnAjouterCommande");
        btnAjouterCommande->setGeometry(QRect(680, 410, 80, 24));
        btnSupprimerCommande = new QPushButton(tabCommandes);
        btnSupprimerCommande->setObjectName("btnSupprimerCommande");
        btnSupprimerCommande->setGeometry(QRect(520, 410, 80, 24));
        btnModifierCommande = new QPushButton(tabCommandes);
        btnModifierCommande->setObjectName("btnModifierCommande");
        btnModifierCommande->setGeometry(QRect(600, 410, 80, 24));
        groupBox = new QGroupBox(tabCommandes);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 240, 271, 261));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(10, 40, 61, 16));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 130, 71, 16));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(10, 100, 111, 16));
        label_15 = new QLabel(groupBox);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(10, 70, 61, 16));
        dateMinCommande = new QDateEdit(groupBox);
        dateMinCommande->setObjectName("dateMinCommande");
        dateMinCommande->setGeometry(QRect(120, 40, 110, 25));
        dateMaxCommande = new QDateEdit(groupBox);
        dateMaxCommande->setObjectName("dateMaxCommande");
        dateMaxCommande->setGeometry(QRect(120, 70, 110, 25));
        comboModePaiementFiltre = new QComboBox(groupBox);
        comboModePaiementFiltre->addItem(QString());
        comboModePaiementFiltre->addItem(QString());
        comboModePaiementFiltre->addItem(QString());
        comboModePaiementFiltre->addItem(QString());
        comboModePaiementFiltre->addItem(QString());
        comboModePaiementFiltre->addItem(QString());
        comboModePaiementFiltre->setObjectName("comboModePaiementFiltre");
        comboModePaiementFiltre->setGeometry(QRect(120, 100, 111, 24));
        lineIdClientFiltreCommande = new QLineEdit(groupBox);
        lineIdClientFiltreCommande->setObjectName("lineIdClientFiltreCommande");
        lineIdClientFiltreCommande->setGeometry(QRect(120, 130, 113, 24));
        btnRechercheCommande = new QPushButton(groupBox);
        btnRechercheCommande->setObjectName("btnRechercheCommande");
        btnRechercheCommande->setGeometry(QRect(70, 160, 101, 24));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(10, 200, 61, 16));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(10, 230, 61, 16));
        comboTriCommande = new QComboBox(groupBox);
        comboTriCommande->addItem(QString());
        comboTriCommande->addItem(QString());
        comboTriCommande->addItem(QString());
        comboTriCommande->addItem(QString());
        comboTriCommande->setObjectName("comboTriCommande");
        comboTriCommande->setGeometry(QRect(80, 200, 121, 24));
        comboOrdreCommande = new QComboBox(groupBox);
        comboOrdreCommande->addItem(QString());
        comboOrdreCommande->addItem(QString());
        comboOrdreCommande->setObjectName("comboOrdreCommande");
        comboOrdreCommande->setGeometry(QRect(80, 230, 121, 24));
        btnExporterCommandesPdf = new QPushButton(tabCommandes);
        btnExporterCommandesPdf->setObjectName("btnExporterCommandesPdf");
        btnExporterCommandesPdf->setGeometry(QRect(570, 480, 121, 24));
        btnCommandesPourClient = new QPushButton(tabCommandes);
        btnCommandesPourClient->setObjectName("btnCommandesPourClient");
        btnCommandesPourClient->setGeometry(QRect(400, 480, 151, 24));
        btnStatsCommandes = new QPushButton(tabCommandes);
        btnStatsCommandes->setObjectName("btnStatsCommandes");
        btnStatsCommandes->setGeometry(QRect(490, 450, 121, 24));
        btnChiffreAffairesTotal = new QPushButton(tabCommandes);
        btnChiffreAffairesTotal->setObjectName("btnChiffreAffairesTotal");
        btnChiffreAffairesTotal->setGeometry(QRect(350, 450, 121, 24));
        tabWidget->addTab(tabCommandes, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuRattrappage = new QMenu(menubar);
        menuRattrappage->setObjectName("menuRattrappage");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuRattrappage->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


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
        label_6->setText(QCoreApplication::translate("MainWindow", "ID Commande :", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Date commande :", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Montant total :", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Statut :", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Mode de paiement :", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "ID Client :", nullptr));
        comboStatutCommande->setItemText(0, QCoreApplication::translate("MainWindow", "En cours", nullptr));
        comboStatutCommande->setItemText(1, QCoreApplication::translate("MainWindow", "Pay\303\251e", nullptr));
        comboStatutCommande->setItemText(2, QCoreApplication::translate("MainWindow", "Annul\303\251e", nullptr));

        comboModePaiement->setItemText(0, QCoreApplication::translate("MainWindow", "Esp\303\250ces", nullptr));
        comboModePaiement->setItemText(1, QCoreApplication::translate("MainWindow", "Carte", nullptr));
        comboModePaiement->setItemText(2, QCoreApplication::translate("MainWindow", "Ch\303\250que", nullptr));
        comboModePaiement->setItemText(3, QCoreApplication::translate("MainWindow", "Virement", nullptr));
        comboModePaiement->setItemText(4, QCoreApplication::translate("MainWindow", "En ligne", nullptr));

        btnAjouterCommande->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        btnSupprimerCommande->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        btnModifierCommande->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Recherche / Tri", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Date min :", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "ID Client :", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Mode de paiement :", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Date max :", nullptr));
        comboModePaiementFiltre->setItemText(0, QCoreApplication::translate("MainWindow", "Tous", nullptr));
        comboModePaiementFiltre->setItemText(1, QCoreApplication::translate("MainWindow", "Esp\303\250ces", nullptr));
        comboModePaiementFiltre->setItemText(2, QCoreApplication::translate("MainWindow", "Carte", nullptr));
        comboModePaiementFiltre->setItemText(3, QCoreApplication::translate("MainWindow", "Ch\303\250que", nullptr));
        comboModePaiementFiltre->setItemText(4, QCoreApplication::translate("MainWindow", "Virement", nullptr));
        comboModePaiementFiltre->setItemText(5, QCoreApplication::translate("MainWindow", "En ligne", nullptr));

        btnRechercheCommande->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Trier par :", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Ordre :", nullptr));
        comboTriCommande->setItemText(0, QCoreApplication::translate("MainWindow", "Date", nullptr));
        comboTriCommande->setItemText(1, QCoreApplication::translate("MainWindow", "Montant", nullptr));
        comboTriCommande->setItemText(2, QCoreApplication::translate("MainWindow", "Client", nullptr));
        comboTriCommande->setItemText(3, QCoreApplication::translate("MainWindow", "Paiement", nullptr));

        comboOrdreCommande->setItemText(0, QCoreApplication::translate("MainWindow", "Croissant", nullptr));
        comboOrdreCommande->setItemText(1, QCoreApplication::translate("MainWindow", "D\303\251croissant", nullptr));

        btnExporterCommandesPdf->setText(QCoreApplication::translate("MainWindow", "Exporter en PDF", nullptr));
        btnCommandesPourClient->setText(QCoreApplication::translate("MainWindow", "Commandes du client saisi", nullptr));
        btnStatsCommandes->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        btnChiffreAffairesTotal->setText(QCoreApplication::translate("MainWindow", "Chiffre d'affaires total", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabCommandes), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        menuRattrappage->setTitle(QCoreApplication::translate("MainWindow", "Rattrappage", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
