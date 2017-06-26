#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>


#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;

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


    RotatedRect getRotatedRect(Mat& mat);
    void drawRotatedRect(Mat &mat,RotatedRect &rRect,Scalar clrLine);

    VideoCapture m_capture[2];
    Mat m_frame[2];
    //Mat m_matBack;
    bool m_bOpen;
    bool m_bGray,m_bThreshold;
    void drawObjContours(Mat &matTh);
//    Mat rotateImage(Mat img, int degree);
private slots:
//    void OpenCamera();
//    void CloseCamera();
    void CheckGrayBox();
    void CheckThresholdBox();
    void on_UpdateBacklightButton_clicked();
    void on_openButton_pressed();
    void on_closeButton_pressed();
};

#endif // IMAGEVIEW_H
