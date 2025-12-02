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
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
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







