#include "QCameraThread.h"
#include <QDebug>

QCameraThread::QCameraThread(int iCameraID,QObject *parent) :
    QThread(parent)
{
    m_iCameraID=iCameraID;
    char sName[20];

    sprintf(sName,"Camera%d",m_iCameraID);
    m_sWinName=sName;
}


QCameraThread::~QCameraThread()
{

}
void QCameraThread::run()
{

    if(m_capture.isOpened())
         m_capture.release();     //decide if capture is already opened; if so,close it
     m_capture.open(m_iCameraID);           //open the default camera
     if (m_capture.isOpened())
     {
         m_capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
         m_capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
         m_capture.set(CV_CAP_PROP_FPS,5);
     }
     else
     {
         return;
     }
     m_bOpen=true;

     Mat matFrame,matShow;
     do
     {
             m_capture >> matFrame;
             Mat matTrans;
             if (!matFrame.empty())
             {
                 switch(m_iDeg)
                 {
                 case 0:
                     matShow=matFrame.clone();
                     break;
                 case 1:
                     transpose(matFrame,matTrans);
                     flip(matTrans,matShow,0);
                     break;
                 case 2:
                     flip(matFrame,matShow,0);
                     break;
                 case 3:
                     transpose(matFrame,matShow);
                     break;
                 default:
                     matShow=matFrame.clone();
                     break;
                 }
                 matFrame.release();
                 matTrans.release();
                 //qDebug()<<"读取一桢图像";
                 imshow(m_sWinName,matShow);
                 matShow.release();
             }
             usleep(20000);
     }
     while(m_bOpen);

     m_capture.release();
     destroyWindow(m_sWinName);
}

void QCameraThread::close()
{
    m_bOpen=false;
}

void QCameraThread::setDeg(int iDeg)
{
    m_iDeg=iDeg;
}
