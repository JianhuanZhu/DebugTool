#include "dbmanager.h"

DbManager::DbManager()
{

}


bool DbManager::openDataBase(const QString& strFileName)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(strFileName);
    m_db.setUserName("root");
    m_db.setPassword("123456");
    if(m_db.open())
    {
        return true;
    }
    qDebug()<<m_db.lastError();
    qFatal("failed to connect.") ;
    return false;
}

//关闭数据库
void DbManager::closeDataBase()
{
    m_db.close();
}


//判断数据库中是否存在该表
bool DbManager::isExistTable(const QString& strTableName)
{
    QSqlQuery query;
    QString strSql = QString("SELECT 1 FROM sqlite_master where type = 'table' and  name = '%1'").arg(strTableName);
    query.exec(strSql);
    if(query.next())
    {
        int nResult = query.value(0).toInt();//有表时返回1，无表时返回null
        if(nResult)
        {
            return true;
        }
    }
    return false;
}

//判断表中是否含有某字段(列)
bool DbManager::isExistField(const QString& strTableName, const QString& strFieldName)
{
    QSqlQuery query(m_db);
    QString strSql = QString("SELECT 1 FROM sqlite_master where type = 'table'"
                             " and name= '%1' and sql like '%%2%'").arg(strTableName).arg(strFieldName);
    query.exec(strSql);
    if(query.next())
    {
        int nResult = query.value(0).toInt();//有此字段时返回1，无字段时返回null
        if(nResult)
        {
            return true;
        }
    }
    return false;
}
