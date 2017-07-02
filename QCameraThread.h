#ifndef QCAMERATHREAD_H
#define QCAMERATHREAD_H

#include <QThread>

#include <iostream>
using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;


class QCameraThread : public QThread
{
    Q_OBJECT
public:
    explicit QCameraThread(int iCameraID,QObject *parent = 0);
    ~QCameraThread();

    void setDeg(int iDeg);
    void close();
private:
    VideoCapture m_capture;
    int m_iDeg;  //旋转角度，0--0°,1--90°,2--180°,3--270°
    bool m_bOpen;
    int m_iCameraID;
    String m_sWinName;
protected:
    void run();
    
signals:
    
public slots:
    
};

#endif // QCAMERATHREAD_H
