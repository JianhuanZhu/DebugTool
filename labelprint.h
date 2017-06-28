#ifndef LABELPRINT_H
#define LABELPRINT_H

#include <QWidget>
#include <CanObject.h>

namespace Ui {
class LabelPrint;
}

class LabelPrint : public QWidget , CanObject
{
    Q_OBJECT
    
public:
    explicit LabelPrint(QWidget *parent = 0);
    ~LabelPrint();
    
private slots:
    void on_PrinterHResetButton_clicked();

    void on_PrinterHSetButton_clicked();

    void on_PrinterHTestButton_clicked();

    void on_PrinterVResetButton_clicked();

    void on_PrinterVSetButton_clicked();

    void on_PrinterMResetButton_clicked();

    void on_PrinterMSetButton_clicked();

    void on_PrinterRResetButton_clicked();

    void on_PrinterRSetButton_clicked();

    void on_InfusionResetButton_clicked();

    void on_InfusionSetButton_clicked();

    void on_PrinterVTestButton_clicked();

    void on_PrinterMTestButton_clicked();

    void on_PrinterRTestButton_clicked();

    void on_InfusionTestButton_clicked();

    void on_RebootPSOCButton_clicked();

    void on_CommTestButton_clicked();

    void on_LedTestButton_clicked();

    void on_PSOCTempButton_clicked();

    void on_PSOCVerButton_clicked();

    void on_ParamReadButton_clicked();

    void on_ParamSaveButton_clicked();

    void on_ParamTestButton_clicked();



    void on_InfusionSpin_valueChanged(int arg1);

private:
    Ui::LabelPrint *ui;
};

#endif // LABELPRINT_H
