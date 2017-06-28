#include "labelprint.h"
#include "ui_labelprint.h"
#include <ErrorInfo.h>

#define LABPRINT 5


LabelPrint::LabelPrint(QWidget *parent) :
    QWidget(parent), CanObject(LABPRINT),
    ui(new Ui::LabelPrint)
{
    ui->setupUi(this);
    ui->PrinterVertEdit->setValidator(new QIntValidator(0, 65535, this)); //0, 65535为输入的数字值范围
    ui->PrinterRotateEdit->setValidator(new QIntValidator(0, 65535, this));
    ui->PrinterHorzEdit->setValidator(new QIntValidator(0, 65535, this));
    ui->PrinterMoveEdit->setValidator(new QIntValidator(0, 65535, this));

    QString sParam[6]={"输液袋位置1","输液袋位置2","输液袋位置3"};
    ui->ParamComboBox->clear();
    for(int i=0;i<3;i++)
        ui->ParamComboBox->addItem(sParam[i]);
    ui->ParamEdit->setValidator(new QIntValidator(0, 65535, this));
}

LabelPrint::~LabelPrint()
{
    delete ui;
}

void LabelPrint::on_PrinterHResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterHSetButton_clicked()
{
    command.command=0xA1;
    command.value1=ui->PrinterHorzEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}


void LabelPrint::on_PrinterVResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterVSetButton_clicked()
{
    command.command=0xA5;
    command.value1=ui->PrinterVertEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterMResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterMSetButton_clicked()
{
    command.command=0xA7;
    command.value1=ui->PrinterMoveEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterRResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterRSetButton_clicked()
{
    command.command=0xA9;
    command.value1=ui->PrinterRotateEdit->text().toInt();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_InfusionResetButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_InfusionSetButton_clicked()
{
    command.command=0xA3;
    command.value1=0;
    command.value2=ui->InfusionSpin->value();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterHTestButton_clicked()
{
    command.command=0xB1;
    command.value1=0;
    command.value2=ui->PrinterHorzSlider->value();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterVTestButton_clicked()
{
    command.command=0xB3;
    command.value1=0;
    command.value2=ui->PrinterVertSlider->value();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterMTestButton_clicked()
{
    command.command=0xB4;
    command.value1=0;
    command.value2=ui->PrinterMoveSlider->value();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PrinterRTestButton_clicked()
{
    command.command=0xB5;
    command.value1=0;
    command.value2=ui->PrinterRotateSlider->value();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_InfusionTestButton_clicked()
{
    command.command=0xB2;
    command.value1=0;
    command.value2=ui->InfusionSlider->value();
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_RebootPSOCButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_CommTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1><font color='blue'>通讯测试正常</font></h1>");
    QMessageBox message(QMessageBox::NoIcon, "标签打印调试", sInfo);
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void LabelPrint::on_LedTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_PSOCTempButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 温度 :<font color='blue'>%1 度</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "标签打印调试", sInfo.arg(feeback.value));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void LabelPrint::on_PSOCVerButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
    QString sInfo("<h1>PSOC 软件版本 :<font color='blue'>0x%1</font></h1> ");
    QMessageBox message(QMessageBox::NoIcon, "标签打印调试", sInfo.arg(feeback.value/100.0));
    //message.setIconPixmap(QPixmap(":image/images/sorry.png"));
    message.exec();
}

void LabelPrint::on_ParamReadButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
    ui->ParamEdit->setText(QString::number(feeback.value>>16));
}

void LabelPrint::on_ParamSaveButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}

void LabelPrint::on_ParamTestButton_clicked()
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
        ErrorInfo::ShowErrinfo((LABPRINT<<16)|feeback.error);
        return;
    }
}



void LabelPrint::on_InfusionSpin_valueChanged(int arg1)
{
    QString sLabel[]={"位置1","位置2","位置3"};
    ui->label_HPos->setText(sLabel[arg1-1]);
}
