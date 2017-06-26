#include "injectorview.h"
#include "ui_injectorview.h"
#include <ErrorInfo.h>

#define INJECTOR 4

InjectorView::InjectorView(QWidget *parent) :
    QWidget(parent),CanObject(INJECTOR),
    ui(new Ui::InjectorView)
{
    ui->setupUi(this);
    ui->InjectorVertEdit->setValidator(new QIntValidator(0, 65535, this)); //0, 65535为输入的数字值范围
    ui->InjectorRotateEdit->setValidator(new QIntValidator(0, 65535, this));
    ui->InjectorPushEdit->setValidator(new QIntValidator(0, 65535, this));
    ui->InjectorMoveEdit->setValidator(new QIntValidator(0, 65535, this));

    QString sParam[6]={"注射器水平位置1","注射器水平位置2","注射器水平位置3","注射器水平位置4","注射器旋转复位位置","注射器推拉复位位置"};
    ui->ParamComboBox->clear();
    for(int i=0;i<6;i++)
        ui->ParamComboBox->addItem(sParam[i]);
    ui->ParamEdit->setValidator(new QIntValidator(0, 65535, this));


}

InjectorView::~InjectorView()
{
    delete ui;
}

void InjectorView::on_InjectorHResetButton_clicked()
{
    command.command=0xA2;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorHSetButton_clicked()
{
    command.command=0xA3;
    command.value1=0;
    command.value2=ui->InjectorHorizSpin->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorVResetButton_clicked()
{
    command.command=0xA0;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorVSetButton_clicked()
{
    command.command=0xA1;
    command.value1=ui->InjectorVertEdit->text().toInt();
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorRResetButton_clicked()
{
    command.command=0xA4;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }

}

void InjectorView::on_InjectorRSetButton_clicked()
{
    command.command=0xA5;
    command.value1=ui->InjectorRotateEdit->text().toInt();
    command.value2=ui->InjectorRotateWaySlider->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorPResetButton_clicked()
{
    command.command=0xA6;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }

}

void InjectorView::on_InjectorPSetButton_clicked()
{
    command.command=0xA7;
    command.value1=ui->InjectorPushEdit->text().toInt();
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorMResetButton_clicked()
{
    command.command=0xA8;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorMSetButton_clicked()
{
    command.command=0xA9;
    command.value1=ui->InjectorMoveEdit->text().toInt();
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorHTestButton_clicked()
{
    command.command=0xB2;
    command.value1=0;
    command.value2=ui->InjectorHorizSlider->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorVTestButton_clicked()
{
    command.command=0xB1;
    command.value1=0;
    command.value2=ui->InjectorVertSlider->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorRTestButton_clicked()
{
    command.command=0xB3;
    command.value1=0;
    command.value2=ui->InjectorRotateSlider->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorPTestButton_clicked()
{
    command.command=0xB4;
    command.value1=0;
    command.value2=ui->InjectorPushSlider->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorMTestButton_clicked()
{
    command.command=0xB5;
    command.value1=0;
    command.value2=ui->InjectorMoveSlider->value();
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_RebootPSOCButton_clicked()
{
    command.command=0xAB;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_CommTestButton_clicked()
{
    command.command=0xAC;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1><font color='blue'>通讯测试正常</font></h1>");
    QMessageBox message(QMessageBox::NoIcon, "注射器调试", sInfo);
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void InjectorView::on_LedTestButton_clicked()
{
    command.command=0xAE;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_PSOCTempButton_clicked()
{
    command.command=0xAD;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 温度 :<font color='blue'>%1 度</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "注射器调试", sInfo.arg(feeback.value));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void InjectorView::on_PSOCVerButton_clicked()
{
    command.command=0xAF;
    command.value1=0;
    command.value2=0;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 软件版本 :<font color='blue'>0x%1</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "注射器调试", sInfo.arg(feeback.value/100.0));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void InjectorView::on_ParamReadButton_clicked()
{
    command.command=0xE1;
    command.value1=0;
    command.value2=ui->ParamComboBox->currentIndex()+1;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
    ui->ParamEdit->setText(QString::number(feeback.value>>16));
}

void InjectorView::on_ParamSaveButton_clicked()
{
    command.command=0xD1;
    command.value1=ui->ParamEdit->text().toInt();
    command.value2=ui->ParamComboBox->currentIndex()+1;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_ParamTestButton_clicked()
{
    command.command=0xC1;
    command.value1=ui->ParamEdit->text().toInt();
    command.value2=ui->ParamComboBox->currentIndex()+1;
    if(m_pCmdCan->Send(&command)<=0)
    {
        return;
    }
    posc_cmd feeback;
    int len=sizeof(posc_cmd);
    if(m_pCmdCan->Recv(&feeback,len,TIMEOUT)<(int)sizeof(posc_cmd))
    {
         return;
    }
    if(feeback.error!=0xFF)
    {
        ErrorInfo::ShowErrinfo((INJECTOR<<16)|feeback.error);
        return;
    }
}

void InjectorView::on_InjectorHorizSpin_valueChanged(int arg1)
{
    QString sLabel[]={"吸安瓿瓶","吸输液袋","吸西林瓶","装注射器"};
    ui->label_HPos->setText(sLabel[arg1-1]);
}
