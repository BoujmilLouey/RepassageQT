#include "commande.h"
#include "dbconnection.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Commande::Commande()
    : m_id(0),
    m_montantTotal(0.0),
    m_idClient(0)
{}

Commande::Commande(int id, const QDate &dateCommande,
                   double montantTotal, const QString &statut, int idClient)
    : m_id(id),
    m_dateCommande(dateCommande),
    m_montantTotal(montantTotal),
    m_statut(statut),
    m_idClient(idClient)
{}

bool Commande::ajouter()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("INSERT INTO COMMANDE (DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT) "
                  "VALUES (:datec, :montant, :statut, :idclient)");

    query.bindValue(":datec", m_dateCommande);
    query.bindValue(":montant", m_montantTotal);
    query.bindValue(":statut", m_statut);
    query.bindValue(":idclient", m_idClient);

    if (!query.exec()) {
        qDebug() << "Erreur insertion COMMANDE:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Commande::modifier()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("UPDATE COMMANDE "
                  "SET DATE_COMMANDE = :datec, MONTANT_TOTAL = :montant, "
                  "STATUT = :statut, ID_CLIENT = :idclient "
                  "WHERE ID_COMMANDE = :id");

    query.bindValue(":datec", m_dateCommande);
    query.bindValue(":montant", m_montantTotal);
    query.bindValue(":statut", m_statut);
    query.bindValue(":idclient", m_idClient);
    query.bindValue(":id", m_id);

    if (!query.exec()) {
        qDebug() << "Erreur modification COMMANDE:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Commande::supprimer()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("DELETE FROM COMMANDE WHERE ID_COMMANDE = :id");
    query.bindValue(":id", m_id);

    if (!query.exec()) {
        qDebug() << "Erreur suppression COMMANDE:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Commande::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT "
                    "FROM COMMANDE",
                    DBConnection::instance().db());
    return model;
}
