#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *g_pMainWnd;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_pMainWnd=this;


    m_pDb=new DbManager();
    //m_pDb->openDataBase("/home/kaishui/QTWorkspace/DebugTool/DebugTool.db");
    m_pDb->openDataBase("DebugTool.db");

    /*QPalette palette1;
    palette1.setColor(QPalette::Background,QColor::fromRgb(0,255,0));
    ui->tabWidget->setAutoFillBackground(true);
    ui->tabWidget->widget(0)->setAutoFillBackground(true);
    ui->tabWidget->widget(0)->setPalette(palette1);*/

}

MainWindow::~MainWindow()
{
    m_pDb->closeDataBase();
    delete m_pDb;
    delete ui;
}
