#include "armview.h"
#include "ui_armview.h"
#include <ErrorInfo.h>

#define MACH_ARM 3

ArmView::ArmView(QWidget *parent) :
    QWidget(parent),CanObject(MACH_ARM),
    ui(new Ui::ArmView)
{
    ui->setupUi(this);
    ui->ClampRotateEdit->setValidator(new QIntValidator(0, 65535, this));
    ui->ClampQuoinEdit->setValidator(new QIntValidator(0, 65535, this)); //0, 65535为输入的数字值范围

    QString sParam[12]={"机械手垂直位置1","机械手垂直位置2","机械手垂直位置3","机械手垂直位置4","机械手水平位置1","机械手水平位置2",
                    "机械手水平位置3","机械手水平位置4","夹手移动位置1","夹手移动位置2","夹手移动位置3","夹手移动位置4"};
    ui->ParamComboBox->clear();
    for(int i=0;i<12;i++)
        ui->ParamComboBox->addItem(sParam[i]);
    ui->ParamEdit->setValidator(new QIntValidator(0, 65535, this));
}

ArmView::~ArmView()
{
    delete ui;
}

void ArmView::on_ArmVResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ArmVSetButton_clicked()
{
    command.command=0xA1;
    command.value1=0;
    command.value2=ui->ArmVertSpin->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ArmHResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }


}

void ArmView::on_ArmHSetButton_clicked()
{
    command.command=0xA3;
    command.value1=0;
    command.value2=ui->ArmHorizSpin->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampMoveResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampMoveSetButton_clicked()
{
    command.command=0xA5;
    command.value1=0;
    command.value2=ui->ClampMoveSpin->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampRotateResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }


}

void ArmView::on_ClampRotateSetButton_clicked()
{
    command.command=0xA7;
    command.value1=ui->ClampRotateEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampQuoinResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampQuoinSetButton_clicked()
{
    command.command=0xA9;
    command.value1=ui->ClampQuoinEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ArmHTestButton_clicked()
{
    command.command=0xB2;
    command.value1=0;
    command.value2=ui->ArmHorizSlider->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
}

void ArmView::on_ArmVTestButton_clicked()
{
    command.command=0xB1;
    command.value1=0;
    command.value2=ui->ArmVertSlider->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampMoveTestButton_clicked()
{
    command.command=0xB3;
    command.value1=0;
    command.value2=ui->ClampMoveSlider->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampRotateTestButton_clicked()
{
    command.command=0xB4;
    command.value1=0;
    command.value2=ui->ClampRotateSlider->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_ClampQuoinTestButton_clicked()
{
    command.command=0xB5;
    command.value1=0;
    command.value2=ui->ClampQuoinSlider->value();
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }

}

void ArmView::on_RebootPSOCButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
}

void ArmView::on_CommTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1><font color='blue'>通讯测试正常</font></h1>");
    QMessageBox message(QMessageBox::NoIcon, "机械手调试", sInfo);
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void ArmView::on_LedTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
}

void ArmView::on_PSOCTempButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 温度 :<font color='blue'>%1 度</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "机械手调试", sInfo.arg(feeback.value));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void ArmView::on_PSOCVerButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 软件版本 :<font color='blue'>0x%1</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "机械手调试", sInfo.arg(feeback.value/100.0));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void ArmView::on_ParamReadButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
    ui->ParamEdit->setText(QString::number(feeback.value>>16));
}

void ArmView::on_ParamSaveButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
}

void ArmView::on_ParamTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
        return;
    }
}

void ArmView::on_ArmHorizSpin_valueChanged(int arg1)
{
    QString sLabel[]={"扳安瓿瓶","安瓿定位","安瓿取瓶","安瓿吸液"};
    ui->label_HPos->setText(sLabel[arg1-1]);
}

void ArmView::on_ArmVertSpin_valueChanged(int arg1)
{
    QString sLabel[]={"扳安瓿瓶","安瓿取瓶","安瓿定位","安瓿吸液"};
    ui->label_VPos->setText(sLabel[arg1-1]);
}

void ArmView::on_ClampMoveSpin_valueChanged(int arg1)
{
    QString sLabel[]={"安瓿吸液","扳安瓿瓶","安瓿定位","安瓿取瓶"};
    ui->label_MPos->setText(sLabel[arg1-1]);
}

void ArmView::on_ArmAllResetButton_clicked()
{
   //整体复位

    //水平复位-->移动复位-->垂直复位-->旋转复位-->夹紧复位
    uchar cmd[]={0xA2,0xA4,0xA0,0xA6,0xA8};

    for(int i=0;i<5;i++)
    {
        command.command=cmd[i];
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
            ErrorInfo::ShowErrinfo((MACH_ARM<<16)|feeback.error);
            return;
        }
    }
}

