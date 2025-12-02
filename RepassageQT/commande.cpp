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
                   double montantTotal, const QString &statut,
                   int idClient, const QString &modePaiement)
{
    m_id = id;
    m_dateCommande = dateCommande;
    m_montantTotal = montantTotal;
    m_statut = statut;
    m_idClient = idClient;
    m_modePaiement = modePaiement;
}

bool Commande::ajouter()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("INSERT INTO COMMANDE (ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT, MODE_PAIEMENT) "
                  "VALUES (:id, :date, :montant, :statut, :idClient, :mode)");
    query.bindValue(":mode", m_modePaiement);
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
                  "WHERE ID_COMMANDE = :id" "SET MODE_PAIEMENT = :mode");

    query.bindValue(":datec", m_dateCommande);
    query.bindValue(":montant", m_montantTotal);
    query.bindValue(":statut", m_statut);
    query.bindValue(":mode", m_modePaiement);
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
    model->setQuery("SELECT ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT, MODE_PAIEMENT"
                    "FROM COMMANDE",
                    DBConnection::instance().db());
    return model;
}
QSqlQueryModel* Commande::rechercheMulti(const QDate &dateMin,
                                         const QDate &dateMax,
                                         const QString &modePaiement,
                                         int idClient,
                                         const QString &triColonne,
                                         bool ordreAscendant)
{
    QString sql = "SELECT ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT, MODE_PAIEMENT "
                  "FROM COMMANDE WHERE 1 = 1";

    if (dateMin.isValid())
        sql += " AND DATE_COMMANDE >= :dateMin";
    if (dateMax.isValid())
        sql += " AND DATE_COMMANDE <= :dateMax";
    if (!modePaiement.isEmpty())
        sql += " AND MODE_PAIEMENT = :mode";
    if (idClient > 0)
        sql += " AND ID_CLIENT = :idClient";

    QString col = "DATE_COMMANDE";
    if (triColonne == "Montant")
        col = "MONTANT_TOTAL";
    else if (triColonne == "Client")
        col = "ID_CLIENT";
    else if (triColonne == "Paiement")
        col = "MODE_PAIEMENT";

    sql += " ORDER BY " + col + (ordreAscendant ? " ASC" : " DESC");

    QSqlQuery query(DBConnection::instance().db());
    query.prepare(sql);

    if (dateMin.isValid())
        query.bindValue(":dateMin", dateMin);
    if (dateMax.isValid())
        query.bindValue(":dateMax", dateMax);
    if (!modePaiement.isEmpty())
        query.bindValue(":mode", modePaiement);
    if (idClient > 0)
        query.bindValue(":idClient", idClient);

    if (!query.exec()) {
        qDebug() << "Erreur rechercheMulti COMMANDE:" << query.lastError().text();
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* Commande::afficherPourClient(int idClient)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query(DBConnection::instance().db());

    query.prepare("SELECT ID_COMMANDE, DATE_COMMANDE, MONTANT_TOTAL, STATUT, ID_CLIENT, MODE_PAIEMENT "
                  "FROM COMMANDE "
                  "WHERE ID_CLIENT = :id "
                  "ORDER BY DATE_COMMANDE DESC");
    query.bindValue(":id", idClient);

    if (!query.exec()) {
        qDebug() << "Erreur afficherPourClient COMMANDE:" << query.lastError().text();
    }

    model->setQuery(query);
    return model;
}

double Commande::chiffreAffairesTotal()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT SUM(MONTANT_TOTAL) FROM COMMANDE");

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

