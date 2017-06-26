#include <ErrorInfo.h>
#include <mainwindow.h>

void ErrorInfo::ShowErrinfo(int iErrID,bool bIgnore)
{

    int iID=iErrID;
    if(bIgnore)
        iID=(iErrID & 0xFFFF);
    QString sErrInfo;
    QSqlQuery query(g_pMainWnd->m_pDb->m_db);
    query.exec(QObject::tr("select * from ErrorInfo where ErrID='%1'").arg(iID));
    if(query.next())
    {
       // qDebug() << query.value(0).toString() << query.value(1).toString()<<query.value(2).toInt()<<query.value(3).toInt();

        sErrInfo=query.value(1).toString();
        //g_pMainWnd->m_pPatient->iAge=query.value(2).toInt();
        //g_pMainWnd->m_pPatient->iSex=query.value(3).toInt();
    }

    QString sInfo("<h1>错误  ID :<font color='red'>0x%1</font></h1> \n <h1>错误内容: <font color='green'> %2 </font></h1>");
    QMessageBox message(QMessageBox::NoIcon, "错误", sInfo.arg(iErrID,0,16).arg(sErrInfo));
    message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();

}

