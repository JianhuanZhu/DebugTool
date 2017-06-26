#ifndef INJECTORVIEW_H
#define INJECTORVIEW_H

#include <QWidget>
#include <CanObject.h>

namespace Ui {
class InjectorView;
}

class InjectorView : public QWidget , CanObject
{
    Q_OBJECT
    
public:
    explicit InjectorView(QWidget *parent = 0);
    ~InjectorView();
    
private slots:
    void on_InjectorHResetButton_clicked();

    void on_InjectorHSetButton_clicked();

    void on_InjectorVResetButton_clicked();

    void on_InjectorVSetButton_clicked();

    void on_InjectorRResetButton_clicked();

    void on_InjectorRSetButton_clicked();

    void on_InjectorPResetButton_clicked();

    void on_InjectorPSetButton_clicked();

    void on_InjectorMResetButton_clicked();

    void on_InjectorMSetButton_clicked();

    void on_InjectorHTestButton_clicked();

    void on_InjectorVTestButton_clicked();

    void on_InjectorRTestButton_clicked();

    void on_InjectorPTestButton_clicked();

    void on_InjectorMTestButton_clicked();

    void on_RebootPSOCButton_clicked();

    void on_CommTestButton_clicked();

    void on_LedTestButton_clicked();

    void on_PSOCTempButton_clicked();

    void on_PSOCVerButton_clicked();

    void on_ParamReadButton_clicked();

    void on_ParamSaveButton_clicked();

    void on_ParamTestButton_clicked();

    void on_InjectorHorizSpin_valueChanged(int arg1);

private:
    Ui::InjectorView *ui;
};

#endif // INJECTORVIEW_H
