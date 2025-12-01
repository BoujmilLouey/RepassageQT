#include "dbconnection.h"
#include <QSqlError>
#include <QDebug>

DBConnection::DBConnection()
{
    // IMPORTANT POUR L’EXAMEN :
    // On déclare une connexion ORACLE (QOCI = driver Oracle de Qt)
    m_db = QSqlDatabase::addDatabase("QOCI");   // Oracle

    // À ADAPTER avec les valeurs de votre Oracle (école / cloud)
    m_db.setHostName("MON_HOST_ORACLE");
    m_db.setDatabaseName("MON_SERVICE_ORACLE"); // SID/service (ex: XE ou mydb_high)
    m_db.setUserName("MON_UTILISATEUR");
    m_db.setPassword("MON_MOTDEPASSE");
}

DBConnection& DBConnection::instance()
{
    static DBConnection instance;
    return instance;
}

bool DBConnection::open()
{
    if (!m_db.isOpen()) {
        if (!m_db.open()) {
            qDebug() << "Erreur ouverture BD Oracle :" << m_db.lastError().text();
            return false;
        }
    }
    return true;
}

void DBConnection::close()
{
    if (m_db.isOpen())
        m_db.close();
}
