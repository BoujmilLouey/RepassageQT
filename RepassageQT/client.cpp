#include "client.h"
#include "dbconnection.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Client::Client()
    : m_id(0)
{}

Client::Client(int id, const QString &nom, const QString &prenom,
               const QString &email, const QString &telephone,
               const QString &adresse)
    : m_id(id),
    m_nom(nom),
    m_prenom(prenom),
    m_email(email),
    m_telephone(telephone),
    m_adresse(adresse)
{}

bool Client::ajouter()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("INSERT INTO CLIENT (NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE) "
                  "VALUES (:nom, :prenom, :email, :telephone, :adresse)");

    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":email", m_email);
    query.bindValue(":telephone", m_telephone);
    query.bindValue(":adresse", m_adresse);

    if (!query.exec()) {
        qDebug() << "Erreur insertion CLIENT:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Client::modifier()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("UPDATE CLIENT "
                  "SET NOM = :nom, PRENOM = :prenom, EMAIL = :email, "
                  "TELEPHONE = :telephone, ADRESSE = :adresse "
                  "WHERE ID_CLIENT = :id");

    query.bindValue(":nom", m_nom);
    query.bindValue(":prenom", m_prenom);
    query.bindValue(":email", m_email);
    query.bindValue(":telephone", m_telephone);
    query.bindValue(":adresse", m_adresse);
    query.bindValue(":id", m_id);

    if (!query.exec()) {
        qDebug() << "Erreur modification CLIENT:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Client::supprimer()
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("DELETE FROM CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", m_id);

    if (!query.exec()) {
        qDebug() << "Erreur suppression CLIENT:" << query.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE "
                    "FROM CLIENT",
                    DBConnection::instance().db());
    return model;
}
QSqlQueryModel* Client::rechercheMulti(const QString &nom,
                                       const QString &email,
                                       const QString &telephone,
                                       const QString &triColonne,
                                       bool ordreAscendant)
{
    QString sql = "SELECT ID_CLIENT, NOM, PRENOM, EMAIL, TELEPHONE, ADRESSE "
                  "FROM CLIENT WHERE 1 = 1";

    // ---- Filtres de recherche (3 critères) ----
    if (!nom.isEmpty())
        sql += " AND LOWER(NOM) LIKE :nom";
    if (!email.isEmpty())
        sql += " AND LOWER(EMAIL) LIKE :email";
    if (!telephone.isEmpty())
        sql += " AND TELEPHONE LIKE :tel";

    // ---- Tri multicritères ----
    QString colonneTri = "NOM";
    if (triColonne == "Prenom")
        colonneTri = "PRENOM";
    else if (triColonne == "Email")
        colonneTri = "EMAIL";

    sql += " ORDER BY " + colonneTri + (ordreAscendant ? " ASC" : " DESC");

    QSqlQuery query(DBConnection::instance().db());
    query.prepare(sql);

    // Bind des paramètres
    if (!nom.isEmpty())
        query.bindValue(":nom", "%" + nom.toLower() + "%");
    if (!email.isEmpty())
        query.bindValue(":email", "%" + email.toLower() + "%");
    if (!telephone.isEmpty())
        query.bindValue(":tel", "%" + telephone + "%");

    if (!query.exec()) {
        qDebug() << "Erreur rechercheMulti CLIENT:" << query.lastError().text();
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));
    return model;
}
double Client::totalDepense(int idClient)
{
    QSqlQuery query(DBConnection::instance().db());
    query.prepare("SELECT SUM(MONTANT_TOTAL) FROM COMMANDE WHERE ID_CLIENT = :id");
    query.bindValue(":id", idClient);

    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }

    return 0.0;
}


QString Client::niveauFidelite(int idClient)
{
    double total = totalDepense(idClient);

    if (total < 100)
        return "Bronze";
    else if (total < 500)
        return "Silver";
    else
        return "Gold";
}


