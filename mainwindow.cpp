#include "mainwindow.h"
#include "ui_mainwindow.h"

cv::Mat img;
cv::Mat cutImg;
cv::Mat maskImg;
int status=1;
int area=0;
int goal=0;
int coin=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_cam_clicked()
{
    ui->grabcut->setEnabled(1);
    //讀取攝像機影像
    cv::VideoCapture cap;
    cap.open(0);

    cv::Mat src;

    cap.read(src);
    cap.release();
    cv::imshow("src",src);
    cv::setMouseCallback("src",mouseMove,0);

    img = src.clone();

}

void quadrantChange(int &xStart,int &xEnd,int &yStart,int &yEnd)
{
    //II quadrant
    if(xEnd-xStart < 0 && yEnd-yStart > 0)
    {
        std::swap(xStart,xEnd);
    }
    //III quadrant
    if(xEnd-xStart < 0 && yEnd-yStart < 0)
    {
        std::swap(xStart,xEnd);
        std::swap(yStart,yEnd);
    }
    //IV quadrant
    if(xEnd-xStart > 0 && yEnd-yStart < 0)
    {
        std::swap(yStart,yEnd);
    }

}

void mouseMove(int event, int x, int y, int flag, void *param)
{
    qDebug() << event <<x<<y<<flag;
    //要畫的圖
    cv::Mat dst;
    dst = img.clone();

    //紀錄起始和結束的點
    static int xStartAbs,yStartAbs,xStart,xEnd,yStart,yEnd;

    //按下左鍵，紀錄起始點
    if(event ==1)
    {
        xStartAbs = x;
        yStartAbs = y;

        xStart = x;
        yStart = y;
    }
    //滑鼠左鍵按著
    else if(event == 0)
    {
        if(flag == 1)
        {
            xStart = xStartAbs;
            yStart = yStartAbs;
            xEnd = x;
            yEnd = y;
            //處理不同象限的起始結束點
            quadrantChange(xStart,xEnd,yStart,yEnd);

            //畫長方形
            cv::rectangle(dst, cv::Rect(xStart,yStart,xEnd-xStart,yEnd-yStart),cv::Scalar(255,255,255),3);
            cv::line(dst,cv::Point(xStart,yStart),cv::Point(xEnd,yEnd),3);
            cv::imshow("src",dst);
        }
    }
    //滑鼠左鍵放開
    else if(event ==4)
    {
        xStart = xStartAbs;
        yStart = yStartAbs;
        xEnd = x;
        yEnd = y;
        if(xStart==xEnd||yStart==yEnd)
        {
            return;
        }
        if(xEnd > dst.cols || yEnd > dst.rows)
        {
            xEnd = dst.cols;
            yEnd = dst.rows;
        }

        quadrantChange(xStart,xEnd,yStart,yEnd);

        cv::rectangle(dst, cv::Rect(xStart,yStart,xEnd-xStart,yEnd-yStart),cv::Scalar(255,255,255),3);
        cv::line(dst,cv::Point(xStart,yStart),cv::Point(xEnd,yEnd),cv::Scalar(255,255,255),3);
        cv::imshow("src",dst);

        //存檔
        cutImg = img(cv::Rect(xStart,yStart,xEnd-xStart,yEnd-yStart));
        cv::imwrite("cut.bmp",cutImg);
        cv::imshow("cut",cutImg);
        maskImg.create(cutImg.rows,cutImg.cols,CV_8UC1);
        for(int i = 0;i<maskImg.rows;i++)
        {
            for(int j = 0;j<maskImg.cols;j++)
            {
                maskImg.at<uchar>(i,j) = 0;
            }
        }
        cv::setMouseCallback("cut",imageLabeling,0);
    }

}

//  cv::circle(dst,cv::Point(x,y),5,cv::Scalar(255,0,0),4);

void imageLabeling(int event, int x, int y, int flag, void *param)
{

    //標記前景
    if(event == cv::EVENT_LBUTTONDOWN || flag == cv::EVENT_FLAG_LBUTTON)
    {
        if(x>0&&y>0&&x<maskImg.cols&&y<maskImg.rows)
            maskImg.at<uchar>(y,x) = 255;
        cv::imshow("mask",maskImg);
    }
    //標記背景
    if(event == cv::EVENT_RBUTTONDOWN || flag == cv::EVENT_FLAG_RBUTTON)
    {
        if(x>0&&y>0&&x<maskImg.cols&&y<maskImg.rows)
            maskImg.at<uchar>(y,x) = 128;
        cv::imshow("mask",maskImg);
    }
    //重新標記
    if(event == cv::EVENT_MBUTTONUP)
    {
        for(int i = 0;i<maskImg.rows;i++)
        {
            for(int j = 0;j<maskImg.cols;j++)
            {
                maskImg.at<uchar>(i,j) = 0;
            }
        }
        cv::imshow("mask",maskImg);
    }
    //標記十元硬幣
//    if(flag == 9)
//    {
//        if(x>0&&y>0&&x<maskImg.cols&&y<maskImg.rows)
//            maskImg.at<uchar>(y,x) = ;
//    }
}

void MainWindow::on_grabcut_clicked()
{
    area=0;
    coin=0;
    //存放背景模型用
    cv::Mat bgdModel;
    bgdModel.zeros(1,65,CV_64FC1);
    //存放前景模型用
    cv::Mat fgdModel;
    fgdModel.zeros(1,65,CV_64FC1);


    this->maskReal = maskImg.clone();

    for(int i = 0;i<maskReal.rows;i++)
    {
        for(int j = 0;j<maskReal.cols;j++)
        {
            //將前景標記轉換
            if(maskReal.at<uchar>(i,j) == 255)
            {
                maskReal.at<uchar>(i,j) = cv::GC_FGD;
            }
            //將背景標記轉換
            else if(maskReal.at<uchar>(i,j) == 128)
            {
                maskReal.at<uchar>(i,j) = cv::GC_BGD;
            }
            //其他全部視為可能的背景
            else
            {
                maskReal.at<uchar>(i,j) = cv::GC_PR_BGD;
            }
        }
    }

    //背景分離主函式
    cv::grabCut(cutImg,maskReal,cv::Rect(0,0,cutImg.cols-1,cutImg.rows-1)
                ,bgdModel,fgdModel,5,cv::GC_INIT_WITH_MASK|cv::GC_INIT_WITH_RECT);

    for(int i = 0;i<maskReal.rows;i++)
    {
        for(int j = 0;j<maskReal.cols;j++)
        {
            //將結果的前景轉換成白色
            if(maskReal.at<uchar>(i,j) == cv::GC_PR_FGD)
            {
                maskReal.at<uchar>(i,j) = 255;
                if(status==1)
                {
                    area++;
                }
                if(status==2)
                {
                    coin++;
                }
            }
            //將結果的可能前景轉換成白色
            else if(maskReal.at<uchar>(i,j) == cv::GC_FGD)
            {
                maskReal.at<uchar>(i,j) = 255;
                if(status==1)
                {
                    area++;
                }
                if(status==2)
                {
                    coin++;
                }
            }
            //將結果的可能背景轉換成黑色
            else if(maskReal.at<uchar>(i,j) == cv::GC_PR_BGD)
            {
                maskReal.at<uchar>(i,j) = 0;
            }
            //其他轉換成黑色
            else
            {
                maskReal.at<uchar>(i,j) = 0;
            }
        }
    }
    ui->goalnumber->display(goal);
    ui->coinnumber->display(coin);
    //建立一張全黑影像作為提取前景用
    cv::Mat foreground(cutImg.size(),CV_8UC3,cv::Scalar(0,0,0));
    //從原始影像搭配遮罩提取前景
    cutImg.copyTo(foreground,maskReal);

    cv::imshow("result",foreground);
    cv::imshow("maskOUT",maskReal);
}


void MainWindow::on_loadpicture_clicked()
{
    ui->grabcut->setEnabled(1);
    QString fileName = QFileDialog::getOpenFileName();
    //    qDebug() << fileName;
    cv::Mat src = cv::imread(fileName.toStdString());

    int width = src.cols;
    int height = src.rows;

    cv::resize(src,src,cv::Size(width,height));
    //    cv::imshow("WTF",src);

    cv::imshow("src",src);
    cv::setMouseCallback("src",mouseMove,0);
    img = src.clone();
}

void MainWindow::on_goal_clicked()
{
    status=1;
}

void MainWindow::on_coin_clicked()
{
    ui->count->setEnabled(1);
    goal=area;
    status=2;
}

void MainWindow::on_count_clicked()
{
    double answer=goal*(5.30929/coin);
    ui->answernumber->display(answer);

}
