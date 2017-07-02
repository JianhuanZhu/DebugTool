#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>


#include <QCameraThread.h>

namespace Ui {
class ImageView;
}

class ImageView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();
    
private:
    Ui::ImageView *ui;
    QCameraThread *m_pCameraThread1,*m_pCameraThread2;

private slots:


    void on_openCamera1Button_clicked();
    void on_closeCamera1Button_clicked();
    void on_openCamera2Button_clicked();
    void on_closeCamera2Button_clicked();
};

#endif // IMAGEVIEW_H
