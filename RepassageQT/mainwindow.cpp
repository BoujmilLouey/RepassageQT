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
#include <QTextDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_modelClients(nullptr)
    , m_modelCommandes(nullptr)
{
    ui->setupUi(this);
    ui->lineIdClient->setReadOnly(true);
    ui->lineIdCommande->setReadOnly(true);

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

    // Générer automatiquement le prochain ID client
    int idClient = 1;
    {
        QSqlQuery q(DBConnection::instance().db());
        if (q.exec("SELECT COALESCE(MAX(ID_CLIENT),0) + 1 FROM CLIENT") && q.next()) {
            idClient = q.value(0).toInt();
        }
    }
    ui->lineIdClient->setText(QString::number(idClient));

    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Validation",
                             "Nom et prénom sont obligatoires pour ajouter un client.");
        return;
    }
    if (!email.contains('@')) {
        QMessageBox::warning(this, "Client",
                             "Adresse email invalide.");
        return;
    }
    bool telOk = true;
    for (QChar c : tel) {
        if (!c.isDigit()) {
            telOk = false;
            break;
        }
    }
    if (!telOk || tel.length() < 8) {
        QMessageBox::warning(this, "Client",
                             "Téléphone invalide (uniquement des chiffres, au moins 8).");
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
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter les clients en PDF",
        "clients.pdf",
        "Fichiers PDF (*.pdf)");

    if (fileName.isEmpty())
        return;

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageMargins(QMarginsF(25, 25, 25, 25));

    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE "
                  "FROM CLIENT ORDER BY NOM");
    query.exec();

    QString html;

    html += "<html><head><meta charset='utf-8'>"
            "<style>"
            "body { font-family: 'Helvetica'; font-size: 34pt; line-height: 260%; }"
            "h2 { text-align: center; font-size: 48pt; margin-bottom: 50px; }"
            "table { border-collapse: collapse; width: 100%; font-size: 34pt; }"
            "th, td { border: 3px solid #000; padding: 24px; }"
            "th { background-color: #f0f0f0; font-size: 40pt; }"
            "</style></head><body>";

    html += "<h2>Liste des clients</h2>";
    html += "<table>";

    html += "<tr>"
            "<th>ID</th>"
            "<th>Nom</th>"
            "<th>Prénom</th>"
            "<th>Email</th>"
            "<th>Téléphone</th>"
            "<th>Adresse</th>"
            "</tr>";

    while (query.next()) {
        html += "<tr>";
        html += "<td>" + query.value("ID_CLIENT").toString() + "</td>";
        html += "<td>" + query.value("NOM").toString() + "</td>";
        html += "<td>" + query.value("PRENOM").toString() + "</td>";
        html += "<td>" + query.value("EMAIL").toString() + "</td>";
        html += "<td>" + query.value("TELEPHONE").toString() + "</td>";
        html += "<td>" + query.value("ADRESSE").toString() + "</td>";
        html += "</tr>";
    }

    html += "</table></body></html>";

    QTextDocument doc;
    doc.setHtml(html);

    QPainter painter(&writer);
    doc.drawContents(&painter);
    painter.end();

    QMessageBox::information(this, "PDF", "PDF géant généré !");
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
    // Générer automatiquement le prochain ID commande
    int idCmd = 1;
    {
        QSqlQuery q(DBConnection::instance().db());
        if (q.exec("SELECT COALESCE(MAX(ID_COMMANDE),0) + 1 FROM COMMANDE") && q.next()) {
            idCmd = q.value(0).toInt();
        }
    }
    ui->lineIdCommande->setText(QString::number(idCmd));


    QDate dateCmd = ui->dateCommande->date();

    bool okMontant = false;
    double montant = ui->lineMontantCommande->text().toDouble(&okMontant);
    if (!okMontant) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un montant valide.");
        return;
    }
    // Montant > 0
    if (!okMontant || montant <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Le montant doit être un nombre positif.");
        return;
    }

    QString statut = ui->comboStatutCommande->currentText();
    QString mode = ui->comboModePaiement->currentText();
    if (statut.trimmed().isEmpty() || mode.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Commande",
                             "Statut et mode de paiement sont obligatoires.");
        return;
    }
    bool okIdClient = false;
    int idClient = ui->lineIdClientCommande->text().toInt(&okIdClient);
    if (!okIdClient || idClient <= 0) {
        QMessageBox::warning(this, "Commande",
                             "Veuillez saisir un ID client valide.");
        return;
    }
    // Vérifier que le client existe réellement dans la table CLIENT
    QSqlQuery q(DBConnection::instance().db());
    q.prepare("SELECT COUNT(*) FROM CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", idClient);

    if (!q.exec() || !q.next() || q.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Commande",
                             "Le client avec cet ID n'existe pas.\n"
                             "Veuillez choisir un ID client existant.");
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
    // Vérifier que le client existe réellement dans la table CLIENT
    QSqlQuery q(DBConnection::instance().db());
    q.prepare("SELECT COUNT(*) FROM CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", idClient);

    if (!q.exec() || !q.next() || q.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Commande",
                             "Le client avec cet ID n'existe pas.\n"
                             "Veuillez choisir un ID client existant.");
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
    QDate dateMin = ui->dateMinCommande->date();
    QDate dateMax = ui->dateMaxCommande->date();
    QString modePaiement;

    // comboModePaiementFiltre : index 0 = "Tous"
    int idxMode = ui->comboModePaiementFiltre->currentIndex();
    if (idxMode > 0)
        modePaiement = ui->comboModePaiementFiltre->currentText();

    bool okIdClient = false;
    int idClient = ui->lineIdClientFiltreCommande->text().toInt(&okIdClient);
    if (!okIdClient)
        idClient = 0; // pas de filtre

    // ---------- TRI ----------
    QString triCol;
    switch (ui->comboTriCommande->currentIndex()) {
    case 0: // Date
        triCol = "DATE_COMMANDE";
        break;
    case 1: // Montant
        triCol = "MONTANT_TOTAL";
        break;
    case 2: // Client
        triCol = "ID_CLIENT";
        break;
    case 3: // Paiement
        triCol = "MODE_PAIEMENT";
        break;
    default:
        triCol = "DATE_COMMANDE";
        break;
    }

    bool asc = (ui->comboOrdreCommande->currentIndex() == 0); // 0 = Croissant

    // Appel métier
    QSqlQueryModel *model = Commande::rechercheMulti(dateMin,
                                                     dateMax,
                                                     modePaiement,
                                                     idClient,
                                                     triCol,
                                                     asc);

    delete m_modelCommandes;
    m_modelCommandes = model;
    ui->tableViewCommandes->setModel(m_modelCommandes);
    ui->tableViewCommandes->resizeColumnsToContents();
    ui->tableViewCommandes->setColumnHidden(5, true); // cache ID_CLIENT

    // Bonus: autoriser tri en cliquant l'en-tête du tableau
    ui->tableViewCommandes->setSortingEnabled(true);
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
    writer.setPageMargins(QMarginsF(25, 25, 25, 25));

    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT, MODE_PAIEMENT "
                  "FROM COMMANDE ORDER BY DATE_COMMANDE DESC");
    query.exec();

    QString html;

    html += "<html><head><meta charset='utf-8'>"
            "<style>"
            "body { font-family: 'Helvetica'; font-size: 34pt; line-height: 260%; }"
            "h2 { text-align: center; font-size: 48pt; margin-bottom: 50px; }"
            "table { border-collapse: collapse; width: 100%; font-size: 34pt; }"
            "th, td { border: 3px solid #000; padding: 24px; }"
            "th { background-color: #f0f0f0; font-size: 40pt; }"
            "</style></head><body>";

    html += "<h2>Liste des commandes</h2>";
    html += "<table>";

    html += "<tr>"
            "<th>ID</th>"
            "<th>Date</th>"
            "<th>Montant</th>"
            "<th>Statut</th>"
            "<th>Client</th>"
            "<th>Mode</th>"
            "</tr>";

    while (query.next()) {
        QString date = QDate::fromString(
                           query.value("DATE_COMMANDE").toString(),
                           "yyyy-MM-dd")
                           .toString("dd/MM/yyyy");

        html += "<tr>";
        html += "<td>" + query.value("ID_COMMANDE").toString() + "</td>";
        html += "<td>" + date + "</td>";
        html += "<td>" + QString::number(query.value("MONTANT_TOTAL").toDouble(), 'f', 2) + "</td>";
        html += "<td>" + query.value("STATUT").toString() + "</td>";
        html += "<td>" + query.value("ID_CLIENT").toString() + "</td>";
        html += "<td>" + query.value("MODE_PAIEMENT").toString() + "</td>";
        html += "</tr>";
    }

    html += "</table></body></html>";

    QTextDocument doc;
    doc.setHtml(html);

    QPainter painter(&writer);
    doc.drawContents(&painter);
    painter.end();

    QMessageBox::information(this, "PDF", "PDF géant généré !");
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

void MainWindow::on_tableViewClients_clicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    int row = index.row();
    QAbstractItemModel *model = ui->tableViewClients->model();
    if (!model)
        return;

    int idClient = model->data(model->index(row, 0)).toInt();          // ID_CLIENT
    QString nom   = model->data(model->index(row, 1)).toString();      // NOM
    QString prenom= model->data(model->index(row, 2)).toString();      // PRENOM
    QString email = model->data(model->index(row, 3)).toString();      // EMAIL
    QString tel   = model->data(model->index(row, 4)).toString();      // TELEPHONE
    QString adr   = model->data(model->index(row, 5)).toString();      // ADRESSE

    ui->lineIdClient->setText(QString::number(idClient));
    ui->lineNomClient->setText(nom);
    ui->linePrenomClient->setText(prenom);
    ui->lineEmailClient->setText(email);
    ui->lineTelClient->setText(tel);
    ui->lineAdresseClient->setText(adr);
}
void MainWindow::on_tableViewCommandes_clicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    int row = index.row();
    QAbstractItemModel *model = ui->tableViewCommandes->model();
    if (!model)
        return;

    int idCmd        = model->data(model->index(row, 0)).toInt();        // ID_COMMANDE
    QString dateStr  = model->data(model->index(row, 1)).toString();     // DATE_COMMANDE
    double montant   = model->data(model->index(row, 2)).toDouble();     // MONTANT_TOTAL
    QString statut   = model->data(model->index(row, 3)).toString();     // STATUT
    QString mode     = model->data(model->index(row, 4)).toString();     // MODE_PAIEMENT
    int idClient     = model->data(model->index(row, 5)).toInt();        // ID_CLIENT

    ui->lineIdCommande->setText(QString::number(idCmd));

    // Si tu stockes la date en texte "yyyy-MM-dd"
    QDate d = QDate::fromString(dateStr, "yyyy-MM-dd");
    if (!d.isValid()) {
        // fallback si autre format
        d = QDate::fromString(dateStr, "dd/MM/yyyy");
    }
    if (d.isValid())
        ui->dateCommande->setDate(d);

    ui->lineMontantCommande->setText(QString::number(montant, 'f', 2));

    // Remettre le bon texte dans les combos (si l'item existe)
    int idxStatut = ui->comboStatutCommande->findText(statut);
    if (idxStatut >= 0)
        ui->comboStatutCommande->setCurrentIndex(idxStatut);

    int idxMode = ui->comboModePaiement->findText(mode);
    if (idxMode >= 0)
        ui->comboModePaiement->setCurrentIndex(idxMode);

    ui->lineIdClientCommande->setText(QString::number(idClient));
}
void MainWindow::on_btnAfficherToutesCommandes_clicked()
{
    delete m_modelCommandes;
    m_modelCommandes = Commande::afficher();
    ui->tableViewCommandes->setModel(m_modelCommandes);
    ui->tableViewCommandes->resizeColumnsToContents();
    ui->tableViewCommandes->setColumnHidden(5, true); // cache ID_CLIENT si besoin

    // Optionnel : reset des champs de recherche
    ui->dateMinCommande->setDate(QDate::currentDate());
    ui->dateMaxCommande->setDate(QDate::currentDate());
    ui->comboModePaiementFiltre->setCurrentIndex(0);   // "Tous"
    ui->lineIdClientFiltreCommande->clear();
    ui->comboTriCommande->setCurrentIndex(0);          // Date
    ui->comboOrdreCommande->setCurrentIndex(0);        // Croissant
}








