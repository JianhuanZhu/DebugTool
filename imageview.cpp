#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);

}

ImageView::~ImageView()
{
    delete ui;
}

#if 0
void ImageView::OpenCamera()
{

    ui->openButton->setEnabled(false);
    ui->closeButton->setEnabled(true);
    m_bOpen=true;
    if (m_capture.isOpened())
        m_capture.release();     //decide if capture is already opened; if so,close it
    m_capture.open(0);           //open the default camera
    if (m_capture.isOpened())
    {
        m_capture.set(CV_CAP_PROP_FRAME_WIDTH,640);
        m_capture.set(CV_CAP_PROP_FRAME_HEIGHT,480);
        //capture.set(CV_CAP_PROP_FPS,10);
        //rate=10;
        //rate1= capture1.get(CV_CAP_PROP_FPS);
        namedWindow("Camera",WINDOW_AUTOSIZE);

        Mat matShow,matGray;
        Mat matThreshold;
        do
        {
            m_capture >> m_frame;
            if (!m_frame.empty())
            {
                if(m_bGray)
                {
                   cvtColor(m_frame,matShow,CV_RGB2GRAY);
                   if(m_bThreshold)
                   {
                       threshold(matShow,matThreshold,0,255,THRESH_BINARY|THRESH_OTSU);
                       imshow("threshold",matThreshold);
                       //drawObjContours(matThreshold);
                   }
                }
                else
                    matShow=m_frame.clone();



                 if (!m_matBack.empty())
                 {
                     cvtColor(m_frame,matGray,CV_RGB2GRAY);
                     RotatedRect rRect;

                     /*Mat matBcak32f,matGray32f;
                     matGray.convertTo(matGray32f,CV_32F);
                     m_matBack.convertTo(matBcak32f,CV_32F);
                     Mat matDiv=255*(1-(matBcak32f/matGray32f));
                     matDiv.convertTo(matDiv,CV_8U);
                     Mat matDivTh;
                     threshold(matDiv,matDivTh,0,255,THRESH_BINARY|THRESH_OTSU); //
                     erode(matDivTh,matDivTh,Mat());
                     rRect=getRotatedRect(matDivTh);
                     Mat matDivThRGB;
                     cvtColor(matDivTh,matDivThRGB,CV_GRAY2RGB);
                     drawRotatedRect(matDivThRGB,rRect,Scalar(0,255,0));
                     imshow("DIV",matDivThRGB);*/


                     Mat matSub;
                     absdiff(matGray,m_matBack,matSub);
                     Mat matSubTh;
                     threshold(matSub,matSubTh,0,255,THRESH_BINARY|THRESH_OTSU); //
                     erode(matSubTh,matSubTh,Mat());
                     rRect=getRotatedRect(matSubTh);
                     Mat matSubThRGB;
                     cvtColor(matSubTh,matSubThRGB,CV_GRAY2RGB);
                     drawRotatedRect(matSubThRGB,rRect,Scalar(0,0,255));
                     imshow("SUB",matSubThRGB);

                     drawRotatedRect(matShow,rRect,Scalar(0,255,0));

                     /*Mat matAnd=(matDivTh & matSubTh);
                     rRect=getRotatedRect(matAnd);
                     drawRotatedRect(matShow,rRect,Scalar(255,0,0));*/
                     //imshow("matAnd",matAnd);
                 }

                 Mat matFilp=rotateImage(matShow,90);
                 imshow("Camera",matFilp);

                 waitKey(20);
            }
        }while(m_bOpen);
        matShow.release();
        //if(matThreshold)
        //    matThreshold.release();
    }
    m_frame.release();
    m_capture.release();
    ui->openButton->setEnabled(true);
    ui->closeButton->setEnabled(false);

}


Mat ImageView::rotateImage(Mat img, int degree)
{
    degree = -degree;//warpAffine默认的旋转方向是逆时针，所以加负号表示转化为顺时针
    double angle = degree  * CV_PI / 180.; // 弧度
    double a = sin(angle), b = cos(angle);
    int width = img.cols;
    int height = img.rows;
    int width_rotate = int(height * fabs(a) + width * fabs(b));
    int height_rotate = int(width * fabs(a) + height * fabs(b));
    //旋转数组map
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
    float map[6];
    Mat map_matrix = Mat(2, 3, CV_32F, map);
    // 旋转中心
    CvPoint2D32f center = cvPoint2D32f(width / 2, height / 2);
    CvMat map_matrix2 = map_matrix;
    cv2DRotationMatrix(center, degree, 1.0, &map_matrix2);//计算二维旋转的仿射变换矩阵
    map[2] += (width_rotate - width) / 2;
    map[5] += (height_rotate - height) / 2;
    Mat img_rotate;
    //对图像做仿射变换
    //CV_WARP_FILL_OUTLIERS - 填充所有输出图像的象素。
    //如果部分象素落在输入图像的边界外，那么它们的值设定为 fillval.
    //CV_WARP_INVERSE_MAP - 指定 map_matrix 是输出图像到输入图像的反变换，
    warpAffine(img, img_rotate, map_matrix, Size(width_rotate, height_rotate), 1, 0, 0);
    return img_rotate;
}


void ImageView::CloseCamera()
{

    m_bOpen=false;
    destroyAllWindows();
}

#endif



void ImageView::on_openCamera1Button_clicked()
{
     ui->openCamera1Button->setEnabled(false);
     ui->closeCamera1Button->setEnabled(true);
     m_pCameraThread1=new QCameraThread(0,this);
     m_pCameraThread1->setDeg(ui->comboCamera1Rotate->currentIndex());
     m_pCameraThread1->start();
}

void ImageView::on_closeCamera1Button_clicked()
{
    m_pCameraThread1->close();
    ui->openCamera1Button->setEnabled(true);
    ui->closeCamera1Button->setEnabled(false);
}

void ImageView::on_openCamera2Button_clicked()
{
    ui->openCamera2Button->setEnabled(false);
    ui->closeCamera2Button->setEnabled(true);
    m_pCameraThread2=new QCameraThread(1,this);
    m_pCameraThread2->setDeg(ui->comboCamera2Rotate->currentIndex());
    m_pCameraThread2->start();
}

void ImageView::on_closeCamera2Button_clicked()
{
    m_pCameraThread2->close();
    ui->openCamera2Button->setEnabled(true);
    ui->closeCamera2Button->setEnabled(false);
}
