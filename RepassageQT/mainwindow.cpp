#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "client.h"


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
