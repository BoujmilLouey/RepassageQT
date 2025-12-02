#include "dbconnection.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DBConnection::DBConnection()
{
}

DBConnection::~DBConnection()
{
    close();
}

DBConnection& DBConnection::instance()
{
    static DBConnection inst;
    return inst;
}

bool DBConnection::open()
{
    if (m_db.isOpen())
        return true;

    // ================== VERSION ORACLE (POUR L'ECOLE) ==================
    // Quand vous êtes sur le poste de l'école avec Oracle :
    //
    // m_db = QSqlDatabase::addDatabase("QOCI");
    // m_db.setHostName("ORACLE_HOST");
    // m_db.setPort(1521);
    // m_db.setDatabaseName("ORCL");      // SID ou service
    // m_db.setUserName("USER_ORACLE");
    // m_db.setPassword("PWD_ORACLE");
    //
    // if (!m_db.open()) {
    //     qDebug() << "Erreur ouverture BD Oracle:" << m_db.lastError().text();
    //     return false;
    // }

    // ================== VERSION SQLITE (POUR CHEZ VOUS) =================
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("repassage.db");

    if (!m_db.open()) {
        qDebug() << "Erreur ouverture BD SQLite:" << m_db.lastError().text();
        return false;
    }

    // Création des tables si elles n'existent pas (SQLite uniquement)
    QSqlQuery q(m_db);

    q.exec("CREATE TABLE IF NOT EXISTS CLIENT ("
           "ID_CLIENT INTEGER PRIMARY KEY,"
           "NOM TEXT,"
           "PRENOM TEXT,"
           "EMAIL TEXT,"
           "TELEPHONE TEXT,"
           "ADRESSE TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS COMMANDE ("
           "ID_COMMANDE INTEGER PRIMARY KEY,"
           "DATE_COMMANDE TEXT,"  // stockee en texte (ISO) en SQLite
           "MONTANT_TOTAL REAL,"
           "STATUT TEXT,"
           "MODE_PAIEMENT TEXT,"
           "ID_CLIENT INTEGER,"
           "FOREIGN KEY(ID_CLIENT) REFERENCES CLIENT(ID_CLIENT))");


    return true;
}

void DBConnection::close()
{
    if (m_db.isOpen())
        m_db.close();
}

QSqlDatabase DBConnection::db() const
{
    return m_db;
}
