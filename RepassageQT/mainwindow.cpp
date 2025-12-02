#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "client.h"
#include <QSqlQuery>
#include "dbconnection.h"


// Charts
#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_modelClients(nullptr)
    , m_modelCommandes(nullptr)
{
    ui->setupUi(this);

    // Clients
    m_modelClients = Client::afficher();
    ui->tableViewClients->setModel(m_modelClients);
    ui->tableViewClients->resizeColumnsToContents();

    // Commandes
    m_modelCommandes = Commande::afficher();
    ui->tableViewCommandes->setModel(m_modelCommandes);
    ui->tableViewCommandes->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete m_modelClients;
    delete m_modelCommandes;
    delete ui;
}
void MainWindow::on_btnAjouterClient_clicked()
{
    QString nom      = ui->lineNomClient->text();
    QString prenom   = ui->linePrenomClient->text();
    QString email    = ui->lineEmailClient->text();
    QString tel      = ui->lineTelClient->text();
    QString adresse  = ui->lineAdresseClient->text();

    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Validation",
                             "Nom et prénom sont obligatoires pour ajouter un client.");
        return;
    }

    Client c(0, nom, prenom, email, tel, adresse);
    if (c.ajouter()) {
        QMessageBox::information(this, "Client ajouté",
                                 "Ajout effectué avec succès !");
        ui->tableViewClients->setModel(Client::afficher());
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Erreur lors de l'ajout du client. Vérifiez la BD.");
    }
}
void MainWindow::on_btnModifierClient_clicked()
{
    int id = ui->lineIdClient->text().toInt();
    if (id <= 0) {
        QMessageBox::warning(this, "Validation",
                             "Veuillez saisir un ID client valide pour modifier.");
        return;
    }

    Client c(id,
             ui->lineNomClient->text(),
             ui->linePrenomClient->text(),
             ui->lineEmailClient->text(),
             ui->lineTelClient->text(),
             ui->lineAdresseClient->text());

    if (c.modifier()) {
        QMessageBox::information(this, "Modification",
                                 "Client modifié avec succès.");
        ui->tableViewClients->setModel(Client::afficher());
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Échec de la modification.");
    }
}
void MainWindow::on_btnSupprimerClient_clicked()
{
    int id = ui->lineIdClient->text().toInt();

    if (id <= 0) {
        QMessageBox::warning(this, "Validation",
                             "ID client invalide.");
        return;
    }

    Client c;
    c.setId(id);

    if (c.supprimer()) {
        QMessageBox::information(this, "Suppression",
                                 "Client supprimé avec succès.");
        ui->tableViewClients->setModel(Client::afficher());
    } else {
        QMessageBox::critical(this, "Erreur",
                              "Impossible de supprimer ce client.");
    }
}
void MainWindow::on_btnRechercheClient_clicked()
{
    // 1. Lire les critères de recherche depuis l'IHM
    QString nom    = ui->lineRechercheNomClient->text();
    QString email  = ui->lineRechercheEmailClient->text();
    QString tel    = ui->lineRechercheTelClient->text();

    // 2. Récupérer les options de tri
    QString triCol = ui->comboTriClient->currentText();   // "Nom", "Prenom", "Email"
    bool asc = (ui->comboOrdreClient->currentText() == "Croissant");

    // 3. Appeler la fonction métier de la classe Client
    QSqlQueryModel *model = Client::rechercheMulti(nom, email, tel, triCol, asc);

    // 4. Mettre à jour le tableau
    delete m_modelClients;
    m_modelClients = model;
    ui->tableViewClients->setModel(m_modelClients);
    ui->tableViewClients->resizeColumnsToContents();
}
void MainWindow::on_btnStatsClients_clicked()
{
    // Requête : nombre de clients par première lettre du nom
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT SUBSTR(NOM, 1, 1) AS LETTRE, COUNT(*) AS NBR "
                  "FROM CLIENT "
                  "GROUP BY SUBSTR(NOM, 1, 1) "
                  "ORDER BY LETTRE");

    if (!query.exec()) {
        QMessageBox::critical(this, "Statistiques",
                              "Erreur lors du calcul des statistiques clients.");
        return;
    }

    QBarSet *set = new QBarSet("Clients");
    QStringList categories;

    while (query.next()) {
        QString lettre = query.value("LETTRE").toString();
        int count = query.value("NBR").toInt();

        categories << lettre;
        *set << count;
    }

    if (categories.isEmpty()) {
        QMessageBox::information(this, "Statistiques",
                                 "Aucun client en base, le graphique serait vide.");
        return;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Nombre de clients par première lettre du nom");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axe X : lettres
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Axe Y : nombre
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de clients");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setAttribute(Qt::WA_DeleteOnClose);
    chartView->resize(700, 400);
    chartView->show();
}
void MainWindow::on_btnExporterClientsPdf_clicked()
{
    // 1. Choisir où enregistrer le fichier
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Enregistrer la liste des clients en PDF",
        "clients.pdf",
        "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty())
        return;

    // 2. Préparer le writer PDF
    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "PDF",
                              "Impossible de créer le PDF.");
        return;
    }

    int y = 50;

    // Titre
    painter.setFont(QFont("Helvetica", 14, QFont::Bold));
    painter.drawText(0, y, "Liste des clients");
    y += 40;

    painter.setFont(QFont("Helvetica", 9));

    // 3. Lire les clients depuis la base
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE "
                  "FROM CLIENT "
                  "ORDER BY NOM");

    if (!query.exec()) {
        QMessageBox::critical(this, "PDF",
                              "Erreur lors de la lecture des clients.");
        painter.end();
        return;
    }

    // 4. Écrire ligne par ligne
    while (query.next()) {
        int id          = query.value("ID_CLIENT").toInt();
        QString nom     = query.value("NOM").toString();
        QString prenom  = query.value("PRENOM").toString();
        QString email   = query.value("EMAIL").toString();
        QString tel     = query.value("TELEPHONE").toString();
        QString adresse = query.value("ADRESSE").toString();

        QString line = QString("%1 - %2 %3 | %4 | %5 | %6")
                           .arg(id)
                           .arg(nom)
                           .arg(prenom)
                           .arg(email)
                           .arg(tel)
                           .arg(adresse);

        painter.drawText(0, y, line);
        y += 20;

        // Nouvelle page si on dépasse
        if (y > writer.height() - 50) {
            writer.newPage();
            y = 50;
        }
    }

    painter.end();

    QMessageBox::information(this, "PDF",
                             "PDF généré avec succès.");
}
void MainWindow::on_btnTotalDepenseClient_clicked()
{
    int id = ui->lineIdClient->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Total dépensé",
                             "Veuillez saisir un ID Client.");
        return;
    }

    double total = Client::totalDepense(id);

    QMessageBox::information(this, "Total dépensé",
                             "Le client a dépensé un total de : "
                                 + QString::number(total, 'f', 2) + " DT");
}
void MainWindow::on_btnFideliteClient_clicked()
{
    int id = ui->lineIdClient->text().toInt();

    if (id == 0) {
        QMessageBox::warning(this, "Niveau de fidélité",
                             "Veuillez saisir un ID Client.");
        return;
    }

    QString niveau = Client::niveauFidelite(id);

    QMessageBox::information(this, "Niveau fidélité",
                             "Le niveau de fidélité du client est : " + niveau);
}
void MainWindow::on_btnAjouterCommande_clicked()
{
    bool okIdCmd = false;
    int idCmd = ui->lineIdCommande->text().toInt(&okIdCmd);
    if (!okIdCmd || idCmd <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un ID commande valide.");
        return;
    }

    QDate dateCmd = ui->dateCommande->date();

    bool okMontant = false;
    double montant = ui->lineMontantCommande->text().toDouble(&okMontant);
    if (!okMontant) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un montant valide.");
        return;
    }

    QString statut = ui->comboStatutCommande->currentText();
    QString mode = ui->comboModePaiement->currentText();

    bool okIdClient = false;
    int idClient = ui->lineIdClientCommande->text().toInt(&okIdClient);
    if (!okIdClient || idClient <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un ID client valide.");
        return;
    }

    Commande c(idCmd, dateCmd, montant, statut, idClient, mode);
    if (c.ajouter()) {
        QMessageBox::information(this, "Commande",
                                 "Commande ajoutée avec succès.");
        delete m_modelCommandes;
        m_modelCommandes = Commande::afficher();
        ui->tableViewCommandes->setModel(m_modelCommandes);
        ui->tableViewCommandes->resizeColumnsToContents();
    } else {
        QMessageBox::critical(this, "Commande",
                              "Erreur lors de l'ajout de la commande.");
    }
}
void MainWindow::on_btnModifierCommande_clicked()
{
    bool okIdCmd = false;
    int idCmd = ui->lineIdCommande->text().toInt(&okIdCmd);
    if (!okIdCmd || idCmd <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un ID commande valide pour modifier.");
        return;
    }

    QDate dateCmd = ui->dateCommande->date();

    bool okMontant = false;
    double montant = ui->lineMontantCommande->text().toDouble(&okMontant);
    if (!okMontant) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un montant valide.");
        return;
    }

    QString statut = ui->comboStatutCommande->currentText();
    QString mode = ui->comboModePaiement->currentText();

    bool okIdClient = false;
    int idClient = ui->lineIdClientCommande->text().toInt(&okIdClient);
    if (!okIdClient || idClient <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un ID client valide.");
        return;
    }

    Commande c(idCmd, dateCmd, montant, statut, idClient, mode);
    if (c.modifier()) {
        QMessageBox::information(this, "Commande",
                                 "Commande modifiée avec succès.");
        delete m_modelCommandes;
        m_modelCommandes = Commande::afficher();
        ui->tableViewCommandes->setModel(m_modelCommandes);
        ui->tableViewCommandes->resizeColumnsToContents();
    } else {
        QMessageBox::critical(this, "Commande",
                              "Erreur lors de la modification de la commande.");
    }
}
void MainWindow::on_btnSupprimerCommande_clicked()
{
    bool okIdCmd = false;
    int idCmd = ui->lineIdCommande->text().toInt(&okIdCmd);
    if (!okIdCmd || idCmd <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un ID commande valide pour supprimer.");
        return;
    }

    Commande c;
    c.setId(idCmd);

    if (c.supprimer()) {
        QMessageBox::information(this, "Commande",
                                 "Commande supprimée avec succès.");
        delete m_modelCommandes;
        m_modelCommandes = Commande::afficher();
        ui->tableViewCommandes->setModel(m_modelCommandes);
        ui->tableViewCommandes->resizeColumnsToContents();
    } else {
        QMessageBox::critical(this, "Commande",
                              "Erreur lors de la suppression de la commande.");
    }
}
void MainWindow::on_btnRechercheCommande_clicked()
{
    // Critères
    QDate dateMin = ui->dateMinCommande->date();
    QDate dateMax = ui->dateMaxCommande->date();

    QString mode = ui->comboModePaiementFiltre->currentText();
    if (mode == "Tous")
        mode.clear(); // pas de filtre sur le mode de paiement

    bool okIdClient = false;
    int idClient = ui->lineIdClientFiltreCommande->text().toInt(&okIdClient);
    if (!okIdClient)
        idClient = 0; // pas de filtre client

    QString triCol = ui->comboTriCommande->currentText();   // "Date", "Montant", "Client", "Paiement"
    bool asc = (ui->comboOrdreCommande->currentText() == "Croissant");

    // Appel métier
    QSqlQueryModel *model = Commande::rechercheMulti(dateMin, dateMax, mode, idClient, triCol, asc);

    // Rafraîchir le tableau
    delete m_modelCommandes;
    m_modelCommandes = model;
    ui->tableViewCommandes->setModel(m_modelCommandes);
    ui->tableViewCommandes->resizeColumnsToContents();
}
void MainWindow::on_btnStatsCommandes_clicked()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT MODE_PAIEMENT, SUM(MONTANT_TOTAL) AS TOTAL "
                  "FROM COMMANDE "
                  "GROUP BY MODE_PAIEMENT "
                  "ORDER BY MODE_PAIEMENT");

    if (!query.exec()) {
        QMessageBox::critical(this, "Statistiques commandes",
                              "Erreur lors du calcul des statistiques commandes.");
        return;
    }

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Chiffre d'affaires", series);
    QStringList categories;

    while (query.next()) {
        QString mode = query.value("MODE_PAIEMENT").toString();
        double total = query.value("TOTAL").toDouble();

        categories << mode;
        *set << total;
    }

    if (categories.isEmpty()) {
        QMessageBox::information(this, "Statistiques commandes",
                                 "Aucune commande en base.");
        delete series;
        return;
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Chiffre d'affaires par mode de paiement");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Montant total");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setAttribute(Qt::WA_DeleteOnClose);
    chartView->resize(700, 400);
    chartView->show();
}
void MainWindow::on_btnExporterCommandesPdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter les commandes en PDF",
        "commandes.pdf",
        "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty())
        return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(20, 20, 20, 20));

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::critical(this, "PDF",
                              "Impossible de créer le PDF.");
        return;
    }

    int y = 50;

    painter.setFont(QFont("Helvetica", 14, QFont::Bold));
    painter.drawText(0, y, "Liste des commandes");
    y += 40;

    painter.setFont(QFont("Helvetica", 9));

    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT, MODE_PAIEMENT "
                  "FROM COMMANDE "
                  "ORDER BY DATE_COMMANDE DESC");

    if (!query.exec()) {
        QMessageBox::critical(this, "PDF",
                              "Erreur lors de la lecture des commandes.");
        painter.end();
        return;
    }

    while (query.next()) {
        int idCmd       = query.value("ID_COMMANDE").toInt();
        QDate dateCmd   = query.value("DATE_COMMANDE").toDate();
        double montant  = query.value("MONTANT_TOTAL").toDouble();
        QString statut  = query.value("STATUT").toString();
        int idClient    = query.value("ID_CLIENT").toInt();
        QString mode    = query.value("MODE_PAIEMENT").toString();

        QString line = QString("%1 - %2 | %3 DT | %4 | Client %5 | %6")
                           .arg(idCmd)
                           .arg(dateCmd.toString("dd/MM/yyyy"))
                           .arg(montant, 0, 'f', 2)
                           .arg(statut)
                           .arg(idClient)
                           .arg(mode);

        painter.drawText(0, y, line);
        y += 20;

        if (y > writer.height() - 50) {
            writer.newPage();
            y = 50;
        }
    }

    painter.end();

    QMessageBox::information(this, "PDF",
                             "PDF des commandes généré avec succès.");
}
void MainWindow::on_btnCommandesPourClient_clicked()
{
    bool okIdClient = false;
    int idClient = ui->lineIdClientCommande->text().toInt(&okIdClient);
    if (!okIdClient || idClient <= 0) {
        QMessageBox::warning(this, "Commandes client",
                             "Veuillez saisir un ID client valide dans le champ ID Client.");
        return;
    }

    delete m_modelCommandes;
    m_modelCommandes = Commande::afficherPourClient(idClient);
    ui->tableViewCommandes->setModel(m_modelCommandes);
    ui->tableViewCommandes->resizeColumnsToContents();

    QMessageBox::information(this, "Commandes du client",
                             "Affichage des commandes du client : "
                                 + QString::number(idClient));
}
void MainWindow::on_btnChiffreAffairesTotal_clicked()
{
    double ca = Commande::chiffreAffairesTotal();

    QMessageBox::information(this, "Chiffre d'affaires total",
                             "Le chiffre d'affaires total (toutes commandes) est de : "
                                 + QString::number(ca, 'f', 2) + " DT");
}








