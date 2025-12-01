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
