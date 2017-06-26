#include "vialview.h"
#include "ui_vialview.h"
#include <ErrorInfo.h>

#define VIAL 2

VialView::VialView(QWidget *parent) :
    QWidget(parent),CanObject(VIAL),
    ui(new Ui::VialView)
{

    ui->setupUi(this);
    QObject::connect(ui->VialHResetButton,SIGNAL(clicked()),this,SLOT(VialHorizReset()));
    QObject::connect(ui->VialHSetButton,SIGNAL(clicked()),this,SLOT(VialHorizSet()));
    QObject::connect(ui->VialHTestButton,SIGNAL(clicked()),this,SLOT(VialHorizTest()));
    QObject::connect(ui->VialRouteResetButton,SIGNAL(clicked()),this,SLOT(VialRouteReset()));
    QObject::connect(ui->VialRouteSetButton,SIGNAL(clicked()),this,SLOT(VialRouteSet()));
    QObject::connect(ui->VialRouteTestButton,SIGNAL(clicked()),this,SLOT(VialRouteTest()));
    ui->VialHorizEdit->setValidator(new QIntValidator(0, 65535, this)); //0, 65535为输入的数字值范围
    ui->VialRouteEdit->setValidator(new QIntValidator(0, 65535, this));

    QObject::connect(ui->AnpuleHResetButton,SIGNAL(clicked()),this,SLOT(AnpuleHorizReset()));
    QObject::connect(ui->AnpuleHSetButton,SIGNAL(clicked()),this,SLOT(AnpuleHorizSet()));
    QObject::connect(ui->AnpuleHTestButton,SIGNAL(clicked()),this,SLOT(AnpuleHorizTest()));
    QObject::connect(ui->AnpuleBrokenResetButton,SIGNAL(clicked()),this,SLOT(AnpuleBrokenReset()));
    QObject::connect(ui->AnpuleBrokenSetButton,SIGNAL(clicked()),this,SLOT(AnpuleBrokenSet()));
    QObject::connect(ui->AnpuleBrokenTestButton,SIGNAL(clicked()),this,SLOT(AnpuleBrokenTest()));
    ui->AnpuleHorizEdit->setValidator(new QIntValidator(0, 65535, this));
    ui->AnpuleBrokenEdit->setValidator(new QIntValidator(0, 65535, this));

    QObject::connect(ui->CameraResetButton,SIGNAL(clicked()),this,SLOT(CameraReset()));
    QObject::connect(ui->CameraSetButton,SIGNAL(clicked()),this,SLOT(CameraSet()));
    QObject::connect(ui->CameraTestButton,SIGNAL(clicked()),this,SLOT(CameraTest()));

    QString sParam[17]={"西林瓶位置1","西林瓶位置2","西林瓶位置3","西林瓶位置4","西林瓶位置5","西林瓶位置6",
                        "安瓿瓶位置1","安瓿瓶位置2","安瓿瓶位置3","安瓿瓶位置4","安瓿瓶位置5","摄像头复位",
                        "摄像头位置2","摄像头位置3","摄像头位置4","掰瓶复位","掰瓶位置"};
    ui->ParamComboBox->clear();
    for(int i=0;i<17;i++)
        ui->ParamComboBox->addItem(sParam[i]);
    ui->ParamEdit->setValidator(new QIntValidator(0, 65535, this));



}

VialView::~VialView()
{
    delete ui;
}


void VialView::VialHorizReset()
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
       ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
       return;
   }

}

void VialView::VialHorizSet()
{
    command.command=0xA1;
    command.value1=ui->VialHorizEdit->text().toInt();
    command.value2=ui->VialHorizSpin->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }

}

void VialView::VialHorizTest()
{
    command.command=0xB2;
    command.value1=0;
    command.value2=ui->VialHorizSlider->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}


void VialView::VialRouteReset()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }

}

void VialView::VialRouteSet()
{
    command.command=0xA3;
    command.value1=ui->VialRouteEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}

void VialView::VialRouteTest()
{
    command.command=0xB1;
    command.value1=0;
    command.value2=ui->VialRouteSlider->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }

}

void VialView::AnpuleHorizReset()
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
       ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
       return;
   }

}

void VialView::AnpuleHorizSet()
{
    command.command=0xA5;
    command.value1=ui->AnpuleHorizEdit->text().toInt();
    command.value2=ui->AnpuleHorizSpin->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}


void VialView::AnpuleHorizTest()
{
    command.command=0xB3;
    command.value1=0;
    command.value2=ui->AnpuleHorizSlider->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}



void VialView::AnpuleBrokenReset()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }

}

void VialView::AnpuleBrokenSet()
{
    command.command=0xA9;
    command.value1=ui->AnpuleBrokenEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }

}

void VialView::AnpuleBrokenTest()
{
    command.command=0xB5;
    command.value1=0;
    command.value2=ui->AnpuleBrokenSlider->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}


void VialView::CameraReset()
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
       ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
       return;
   }

}

void VialView::CameraSet()
{
    command.command=0xA7;
    command.value1=0;
    command.value2=ui->CameraSpin->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }

}

void VialView::CameraTest()
{
    command.command=0xB4;
    command.value1=0;
    command.value2=ui->CameraSlider->value();
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}


void VialView::on_RebootPSOCButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}

void VialView::on_CommTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1><font color='blue'>通讯测试正常</font></h1>");
    QMessageBox message(QMessageBox::NoIcon, "瓶子调试", sInfo);
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void VialView::on_LedTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}

void VialView::on_PSOCTempButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 温度 :<font color='blue'>%1 度</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "瓶子调试", sInfo.arg(feeback.value));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void VialView::on_PSOCVerButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 软件版本 :<font color='blue'>0x%1</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "瓶子调试", sInfo.arg(feeback.value/100.0));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void VialView::on_ParamReadButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
    ui->ParamEdit->setText(QString::number(feeback.value>>16));
}

void VialView::on_ParamSaveButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}

void VialView::on_ParamTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((VIAL<<16)|feeback.error);
        return;
    }
}
