#ifndef ARMVIEW_H
#define ARMVIEW_H

#include <QWidget>
#include <CanObject.h>

namespace Ui {
class ArmView;
}

class ArmView : public QWidget , CanObject
{
    Q_OBJECT
    
public:
    explicit ArmView(QWidget *parent = 0);
    ~ArmView();
    
private slots:
    void on_ArmVResetButton_clicked();

    void on_ArmVSetButton_clicked();

    void on_ArmHResetButton_clicked();

    void on_ArmHSetButton_clicked();

    void on_ClampMoveResetButton_clicked();

    void on_ClampMoveSetButton_clicked();

    void on_ClampRotateResetButton_clicked();

    void on_ClampRotateSetButton_clicked();

    void on_ClampQuoinResetButton_clicked();

    void on_ClampQuoinSetButton_clicked();

    void on_ArmHTestButton_clicked();

    void on_ArmVTestButton_clicked();

    void on_ClampMoveTestButton_clicked();

    void on_ClampRotateTestButton_clicked();

    void on_ClampQuoinTestButton_clicked();

    void on_RebootPSOCButton_clicked();

    void on_CommTestButton_clicked();

    void on_LedTestButton_clicked();

    void on_PSOCTempButton_clicked();

    void on_PSOCVerButton_clicked();

    void on_ParamReadButton_clicked();

    void on_ParamSaveButton_clicked();

    void on_ParamTestButton_clicked();

    void on_ArmHorizSpin_valueChanged(int arg1);

    void on_ArmVertSpin_valueChanged(int arg1);

    void on_ClampMoveSpin_valueChanged(int arg1);

private:
    Ui::ArmView *ui;
};

#endif // ARMVIEW_H
