#ifndef VIALVIEW_H
#define VIALVIEW_H

#include <QWidget>
#include <CanObject.h>



namespace Ui {
class VialView;
}

class VialView : public QWidget , CanObject
{
    Q_OBJECT
    
public:
    explicit VialView(QWidget *parent = 0);
    ~VialView();
    
private:
    Ui::VialView *ui;
    //CanObject* m_pCanObj;

private slots:
    void VialHorizReset();
    void VialHorizSet();
    void VialRouteReset();
    void VialRouteSet();
    void VialHorizTest();
    void VialRouteTest();

    void AnpuleHorizReset();
    void AnpuleHorizSet();
    void AnpuleBrokenReset();
    void AnpuleBrokenSet();
    void AnpuleHorizTest();
    void AnpuleBrokenTest();

    void CameraReset();
    void CameraSet();
    void CameraTest();

    void on_RebootPSOCButton_clicked();
    void on_CommTestButton_clicked();
    void on_LedTestButton_clicked();
    void on_PSOCTempButton_clicked();
    void on_PSOCVerButton_clicked();
    void on_ParamReadButton_clicked();
    void on_ParamSaveButton_clicked();
    void on_ParamTestButton_clicked();
};

#endif // VIALVIEW_H
