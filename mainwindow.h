#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imageview.h>
#include <vialview.h>
#include <dbmanager.h>
#include <armview.h>
#include <injectorview.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DbManager *m_pDb;
    
private:
    Ui::MainWindow *ui;

    ImageView *m_pImageView;
    VialView  *m_pVialView;
    ArmView   *m_pArmView;
    InjectorView *m_pInjectView;
};

extern MainWindow *g_pMainWnd;
#endif // MAINWINDOW_H
