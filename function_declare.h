#ifndef FUNCTION_DECLARE_H
#define FUNCTION_DECLARE_H


#include "include_all.h"

#define pi (double)3.1415926

#define MIN_SIZE 20

#define R_D (double)(1)

#define maxB   (uchar)100
#define minB   (uchar)0
#define maxG   (uchar)255
#define minG   (uchar)80
#define maxR   (uchar)255
#define minR   (uchar)50

#define maxG_B   (uchar)255
#define minG_B   (uchar)0
#define maxR_B   (uchar)255
#define minR_B   (uchar)0

#define THRESHOLD 150

#define uchar unsigned char

/*提取边缘，src为单通道，dst为二值图像*/
void edge(Mat &src, Mat &dst);
/*将边缘信息存入向量*/
void edge2list(vector<vector<Point>> & contours_des, Mat & img, vector<Vec4i> &hierarchy);
/*由向量中提取信息，并将边缘以图像的方式表现出来*/
void drawContour(Mat& img, vector<vector<Point>> &contours, int type = 1, Scalar color = Scalar(255));
/*检查一定半径的圆形的范围的颜色信息是否符合要求*/
bool checkColor(Mat * img, Point2i &center, double r_d, double proportion = 0.5);

bool calcCenter(vector<Point> &contour, Point &center);

vector<Point> checkCircle(vector<vector<Point>> &contours);

const int NUMBER = 3;//随机点数
const int radius = 7; //网球半径3.5cm
const int bigball_ball = 2;  //处理，球的膨胀系数, big_ball:ball=bigball_ball
const int car_ball = 3;  //网球车的比例， 车：网球=car_ball
const int window_width = 1000;//图宽X
const int window_height = 1000;//图高Y
#define MIN_SIZE 20

/// Function headers 

#define Pi 3.1415926

/// Function headers 

//#define Method1
#ifdef Method1
vector<Point> Method_of_exhaustion(vector<Point>&center_points);
#endif

#define Method2
#ifdef Method2
vector<Point> Greedy_Algorithm(vector<Point>&center_points);
#endif

/* 获取新的几何形心 */
Mat get_centroid(vector<Point> & Points, vector<Point> & Points_checked);
/* 转换为机器人极坐标动作组 */
void movement(vector<cv::Point>& path, vector<double> & rho, vector<double> & theta, vector<double> & angle);

/*  */
Point each_getCentroid(vector<Point> list);
#endif // !FUNCTION_DECLARE_H

