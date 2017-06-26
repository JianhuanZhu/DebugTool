#include "imageview.h"
#include "ui_imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageView)
{
    ui->setupUi(this);

    //QObject::connect(ui->openButton,SIGNAL(clicked()),this,SLOT(OpenCamera()));
    //QObject::connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(CloseCamera()));
    QObject::connect(ui->checkGray,SIGNAL(clicked()),this,SLOT(CheckGrayBox()));
    QObject::connect(ui->checkThreshold,SIGNAL(clicked()),this,SLOT(CheckThresholdBox()));
    m_bOpen=false;
    m_bGray=false;
    m_bThreshold=false;

    ui->openButton->setEnabled(true);
    ui->closeButton->setEnabled(false);
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

void ImageView::CheckGrayBox()
{
    m_bGray=ui->checkGray->isChecked();
}

void ImageView::CheckThresholdBox()
{
   /* m_bThreshold=ui->checkThreshold->isChecked();
    if(m_bThreshold)
    {
        if (!m_frame.empty())
            namedWindow("threshold",WINDOW_AUTOSIZE);
        m_bGray=true;
        ui->checkGray->setChecked(m_bGray);
    }
    else
    {
        if (!m_frame.empty())
           destroyWindow("threshold");
    }*/
}

void ImageView::drawObjContours(Mat &matTh)
{
    matTh=255-matTh;
    std::vector< std::vector<cv::Point> > contours ;
    findContours(matTh,contours,CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE);


    Mat matContour;
    cvtColor(matTh,matContour,CV_GRAY2RGB);

    for(int i=0;i<(int)contours.size();i++)
    {
        Rect rc=boundingRect(contours[i]);
        if(rc.contains(Point(320,400)))
            drawContours(matContour,contours,i,Scalar(0,255,0),2);
    }

    imshow("contour",matContour);
}


RotatedRect ImageView::getRotatedRect(Mat& mat)
{
    RotatedRect rRect;
    Mat matClone=mat.clone();
    vector<Point> ptvec;
    std::vector< std::vector<cv::Point> > contours;
    findContours(matClone,contours,CV_RETR_EXTERNAL , CV_CHAIN_APPROX_NONE);
    for(int i=0;i<(int)contours.size();i++)
    {
        ptvec.insert(ptvec.end(),contours[i].begin(),contours[i].end());
    }
    matClone.release();
    if(!ptvec.empty())   rRect=minAreaRect(ptvec);
    return rRect;
}


void ImageView::drawRotatedRect(Mat &mat,RotatedRect &rRect,Scalar clrLine)
{
    Point2f pt[4];
    rRect.points(pt);
    for(int i=0;i<4;i++)
        cv::line(mat,pt[i],pt[(i+1)%4],clrLine,2);
}


void ImageView::on_UpdateBacklightButton_clicked()
{
    /*if (!m_frame.empty())
    {
        cvtColor(m_frame,m_matBack,CV_RGB2GRAY);
        if(ui->checkShowBacklight->isChecked())
        {
            imshow("backlight",m_matBack);
        }
        else
        {

        }
    }*/

}








void ImageView::on_openButton_pressed()
{
    ui->openButton->setEnabled(false);
    ui->closeButton->setEnabled(true);
    m_bOpen=true;

    bool bOpenCamera[2];
    bOpenCamera[0]=ui->checkCamera1->isChecked();
    bOpenCamera[1]=ui->checkCamera2->isChecked();

    String sWinName[2]={"Camera1","Camera2"};

    int iDeg[2];
    iDeg[0]=ui->comboCamera1Rotate->currentIndex();
    iDeg[1]=ui->comboCamera2Rotate->currentIndex();

    for(int i=0;i<2;i++)
    {
        if(bOpenCamera[i]==false)  continue;
        if(m_capture[i].isOpened())
             m_capture[i].release();     //decide if capture is already opened; if so,close it
         m_capture[i].open(i);           //open the default camera
         if (m_capture[i].isOpened())
         {
             m_capture[i].set(CV_CAP_PROP_FRAME_WIDTH,640);
             m_capture[i].set(CV_CAP_PROP_FRAME_HEIGHT,480);
             //capture.set(CV_CAP_PROP_FPS,10);
             //rate=10;
             //rate1= capture1.get(CV_CAP_PROP_FPS);
             namedWindow(sWinName[i],WINDOW_AUTOSIZE);
         }
    }


   do
   {

        for(int i=0;i<2;i++)
        {
           if(bOpenCamera[i]==false) continue;

           m_capture[i] >> m_frame[i];
           Mat matShow, matTrans;;
           if (!m_frame[i].empty())
           {
               switch(iDeg[i])
               {
               case 0:
                   matShow=m_frame[i];
                   break;
               case 1:

                   transpose(m_frame[i],matTrans);
                   flip(matTrans,matShow,1);
                   break;
               case 2:
                   flip(m_frame[i],matShow,1);
                   break;
               case 3:
                   transpose(m_frame[i],matShow);
                   break;
               }
               imshow(sWinName[i],matShow);

           }
        }
        waitKey(20);
   }
   while(m_bOpen);

    ui->openButton->setEnabled(true);
    ui->closeButton->setEnabled(false);
}


void ImageView::on_closeButton_pressed()
{
    m_bOpen=false;
    destroyAllWindows();
}
