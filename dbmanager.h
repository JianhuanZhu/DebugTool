#ifndef SQLITEDB_H
#define SQLITEDB_H


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>

class DbManager
{
public:
    DbManager();

    QSqlDatabase m_db;
    bool openDataBase(const QString& strFileName);
    void closeDataBase();
    bool isExistTable(const QString& strTableName);
    bool isExistField(const QString& strTableName, const QString& strFieldName);
};

#endif // SQLITEDB_H
