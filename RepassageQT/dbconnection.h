#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>

class DBConnection
{
public:
    static DBConnection& instance();

    bool open();
    void close();

    QSqlDatabase db() const;

private:
    DBConnection();
    ~DBConnection();
    DBConnection(const DBConnection&) = delete;
    DBConnection& operator=(const DBConnection&) = delete;

    QSqlDatabase m_db;
};

#endif // DBCONNECTION_H
