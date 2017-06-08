#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

CascadeClassifier face_cascade;


char num_str[10];
void detectAndDisplay( Mat frame );

int main()
{
    //加载级联分类器
    if( !face_cascade.load( "haarcascade_frontalface_alt.xml" ) )
    {
        printf("--(!)Error loading face cascade\n");
        return -1;
    }
    //读取图片
    Mat img;
    img=imread("2.jpg");
    //人脸检测
    detectAndDisplay(img);

    //保存图片
    imwrite("2_detect.bmp",img);
    waitKey(0);
    return 0;
}


void detectAndDisplay( Mat image )
{
    Mat frame;
    std::vector<Rect> faces;
    Mat frame_gray;
    //因为图片上访没有人脸，取感兴趣区域为图片下5/6,加快处理速度
    frame=image(Rect(0,image.rows/6-1,image.cols,image.rows/6*5));
    //图片由rgb转化为灰度图
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    //直方图均衡化
    equalizeHist( frame_gray, frame_gray );
    //人脸检测
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 5, 0, Size(45, 45) ,Size(300,300));
    //在图片中画出人脸并标号
    for( size_t i = 0; i < faces.size(); i++ )
    {
			//确定人脸的中心点坐标
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
			//使用矩形框出人脸
            rectangle(frame,cvPoint(faces[i].x ,faces[i].y ),cvPoint(faces[i].x +faces[i].width,faces[i].y +faces[i].height),Scalar(0,255,0),2,8,0);
			//将当前人脸的序号转化为字符串
            sprintf(num_str,"%d",int(i)+1);
			//在图片上标出人脸序号
            putText(frame,num_str,cvPoint(faces[i].x,faces[i].y),FONT_HERSHEY_SIMPLEX,3,Scalar(255,0,255),8,4,false);
    }
}
