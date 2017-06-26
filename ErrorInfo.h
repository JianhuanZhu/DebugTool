#ifndef GLOBE_H
#define GLOBE_H


#include <QMessageBox>
#include <QDebug>
#include <QString>
class ErrorInfo
{
public:
    static void ShowErrinfo(int iErrID,bool bIgnore=false);  //显示错误，bIgnore忽略设备
};

#endif // GLOBE_H
