#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>

class DBConnection
{
public:
    static DBConnection& instance();

    QSqlDatabase db() const { return m_db; }
    bool open();
    void close();

private:
    DBConnection();                              // ctor privé
    DBConnection(const DBConnection&) = delete;
    DBConnection& operator=(const DBConnection&) = delete;

    QSqlDatabase m_db;
};

#endif // DBCONNECTION_H
