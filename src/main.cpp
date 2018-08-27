/*=================================================================================
 *	                    Copyleft! 2018 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2018 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : main.cpp
 * Description             : 圆形物体检测与收集路径规划
 * Reference               : 
 * Programmer(s)           : William Yu, windmillyucong@163.com
 * 							 Yang Qi, 1214201832@qq.com
 * Company                 : HUST, DMET国家重点实验室FOCUS团队
 * Modification History	   : ver1.0, 2017.09.26, William Yu
 *                           ver1.1, 2018.07.21, William Yu, add notes.
 * 							 ver1.2, 2018.08.27, William Yu, move to linux project
=================================================================================*/

/// Include Files 
#include "function_declare.h"
#include <math.h>
using namespace cv;





/// Function Definitions




/**
 * @function main
 * @author Yang Qi
 * 		   William Yu
 */
int main ( int argc, char** argv )
{
	//不使用相机
	//VideoCapture capture(1);
	//while (1)
	//{

		//************************************************************************************************
		// STEP1：数字图像处理，获取网球位置坐标
		//****************************************************************************************
		vector<vector<cv::Point> >  contours_dst;
		vector<Vec4i> hierarchy;
		
		Mat src;
		//不使用相机
		//capture >> src;
		Mat frame = imread("../data/ball4.jpg");
		resize(frame, src, Size(1920, 1440), 0, 0, CV_INTER_LINEAR);
		namedWindow("src", CV_WINDOW_NORMAL );
		imshow("src", src );
		waitKey(0);

		Mat edge_img(src.rows, src.cols, CV_8UC1,Scalar(0));
		Mat edge(src.rows, src.cols, CV_8UC1,Scalar(0));
		Mat checkcolour(src.rows, src.cols, CV_8UC1, Scalar(0));

		blur(src, src, Size(20, 20), Point(-1, -1));

		//-----------------------------------------------------
		// [1]：基于颜色检测
		//-------------------------------------------------
		colour(src, checkcolour);
		namedWindow("checkcolour", CV_WINDOW_NORMAL);
		imshow("checkcolour", checkcolour);
		waitKey(0);

		Canny(checkcolour, edge_img, 150, 120);
		namedWindow("edge_img", CV_WINDOW_NORMAL);
		imshow("edge_img", edge_img);
		waitKey(0);

		// //--三通道分离
		// Mat mv[3];
		// split(src, mv);
		// namedWindow("G", CV_WINDOW_NORMAL);
		// imshow("G", mv[0]);
		// namedWindow("B", CV_WINDOW_NORMAL);
		// imshow("B", mv[1]);
		// namedWindow("R", CV_WINDOW_NORMAL);
		// imshow("R", mv[2]);
		// waitKey(0);

		//-----------------------------------------------------
		// 滤波系列
		//-------------------------------------------------
		// filter(checkcolour, edge_img);
		// namedWindow("filter", CV_WINDOW_NORMAL);
		// imshow("filter", edge_img);
		// waitKey(0);

		//--边缘输出
		edge2list(contours_dst, edge_img, hierarchy);
		drawContour(edge, contours_dst);
		namedWindow("edge", CV_WINDOW_NORMAL);
		imshow("edge", edge);
		waitKey(0);

		//-----------------------------------------------------
		// [2]：基于形状圆形检测
		//-------------------------------------------------
		vector<Point> points;
		points = checkCircle(contours_dst);
		cout<<points.size()<<endl;
		//查看效果
		for (int i = 0; i < points.size(); i++)
			circle(src, points[i], 1, Scalar(0), 3);
		namedWindow("points", CV_WINDOW_NORMAL);
		imshow("points", src);
		waitKey(0);
		cout<<points.size()<<endl;
		

		//************************************************************************************************
		// STEP2：坐标修正
		//****************************************************************************************
		// //--坐标修正
		// //参数
		// double center_x, center_y;//中心值坐标
		// float kx, ky, bx, by;   //kx,ky为系数，bx,by为偏置
		// kx = 1;
		// ky = 1;
		// bx = 0;
		// by = 0;

		// //--相机内参
		// double fx = 2671.557;
		// double fy = 2680.628;
		// double cx = 1660.216;
		// double cy = 1213.749;       
		
		// //--相机位姿参数
		// int theta_1=77;//水平视场角
		// int theta_2=53;//垂直视场角
		// int pitch=60;//俯仰角
		// int height=30;//车高
		// int theta_x1;//绝对值
		
		
		// //坐标转换
		// for (int i = 0; i < points.size(); i++)
		// {
		// 	int x = points[i].x;
		// 	int y = points[i].y;
			
		// 	//x = x*fx + cx;
		// 	//y = y*fy + cy;
		// 	x = x / 0.588;
		// 	y = y / 0.588;
		// 	x = kx *x + bx;
		// 	y = ky *y + by;

		// 	//printf("the x y is %d,%d", x, y);

		// 	int theta_x = (x - 1660)*theta_1 / 3264;//极坐标角度值可输出
		// 	//theta_x = theta_x - 0;
			
		// 	int distance_y = 0.665*height * tan((((1213 - y)*theta_2 / 2448) + pitch)*pi / 180)-36;  //直角坐标y输出
		// 	//if(theta_x < 0)
		// 		//theta_x1 = -theta_x;
		// 	//distance_y = 720+ distance_y;
		// 	x = distance_y*tan(theta_x*pi / 180);
		// 	points[i].x = x;
		// 	points[i].y = distance_y;
		// 	printf("the x is%d,y is%d", x, y);
		// }

		






		

		//************************************************************************************************
		// STEP3：判断距离较近网球的中间位置坐标
		//****************************************************************************************
		//[Debug]	注释掉主函数此行之前的代码，使用get_Random_points获取随机点，模拟STEP1得出的网球中心点坐标，
		//		用以测试STEP2和STEP3程序
		//          非调试状态下注释掉下面三句代码，取消主函数此行之前的代码的注释。
		// Mat src;
		// vector<Point> points;
		// get_Random_points(points, 8);
		

		vector<Point>  Points_checked;
		src = get_centroid(points, Points_checked); ///处理,获取大轮廓形心






		//************************************************************************************************
		// STEP4：路径规划
		//****************************************************************************************

		vector<double> rho;  //极径
		vector<double> theta; //极角弧度制
		vector<double> angle; //极角角度制

#ifdef Method1
		//--计时评价算法时间复杂度
		int64 st1, et1;
		st1 = cvGetTickCount();
		////////////////////////第一种////////////////////////////////////////
		vector<Point> path1 = Method_of_exhaustion(Points_checked);
		////////////////////////第一种////////////////////////////////////////
		et1 = cvGetTickCount();
		cout << "times cost:" << (et1 - st1) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";
		
		
		//2017-10-31更新,加入偏置，更改下列语句块
		//Mat Method_of_exhaustion_src = src.clone();
		//line(Method_of_exhaustion_src, Point(0, 0), path2[0], Scalar(255, 0, 0), 1, 8);
		//for (int i = 0; i < path2.size() - 1; i++)
		//{
		//	line(Method_of_exhaustion_src, path2[i], path2[i + 1], Scalar(255, 0, 0), 1, 8);
		//}
		Mat Method_of_exhaustion_src = src.clone();
		line(Method_of_exhaustion_src, Point(0 + window_width / 2, 0 + 0), Point(path2[0].x + window_width / 2, path2[0].y + 0), Scalar(0, 0, 255), 1, 8);
		for (int i = 0; i < path2.size() - 1; i++)
		{
			line(Method_of_exhaustion_src, Point(path2[i].x + window_width / 2, path2[i].y + 0), Point(path2[i + 1].x + window_width / 2, path2[i + 1].y + 0), Scalar(0, 0, 255), 1, 8);
		}

		//2017-10-30改动：不回原点，注释掉下行语句
		//line(Method_of_exhaustion_src, path2[path2.size() - 1], Point(0, 0), Scalar(0,0,255), 1, 8);
		
		//2017-11-1改动：图像镜像
		flip(Method_of_exhaustion_src, Method_of_exhaustion_src, 0);
		namedWindow("[4]path1:Method_of_exhaustion_src", CV_WINDOW_NORMAL);
		imshow("[4]path1:Method_of_exhaustion", Method_of_exhaustion_src);
		waitKey(0);
		// resize(Method_of_exhaustion_src, src, Size(1080, 810), 0, 0, CV_INTER_LINEAR);
		// imshow("planning", src);

		
		movement(path1, rho, theta, angle);
#endif



#ifdef Method2
		int64 st2, et2;
		st2 = cvGetTickCount();
		////////////////////////第二种////////////////////////////////////////
		vector<Point> path2 = Greedy_Algorithm(Points_checked);
		////////////////////////第二种////////////////////////////////////////
		et2 = cvGetTickCount();
		cout << "times cost:" << (et2 - st2) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";


		//2017-10-31更新,加入偏置，更改下列语句块
		//Mat Greedy_Algorithm_src = src.clone();
		//line(Greedy_Algorithm_src, Point(0, 0), path2[0], Scalar(255, 0, 0), 1, 8);
		//for (int i = 0; i < path2.size() - 1; i++)
		//{
		//	line(Greedy_Algorithm_src, path2[i], path2[i + 1], Scalar(255, 0, 0), 1, 8);
		//}
		Mat Greedy_Algorithm_src = src.clone();
		line(Greedy_Algorithm_src, Point(0 + window_width / 2, 0 + 0), Point(path2[0].x + window_width / 2, path2[0].y + 0), Scalar(0, 0, 255), 1, 8);
		for (int i = 0; i < path2.size() - 1; i++)
		{
			line(Greedy_Algorithm_src, Point(path2[i].x + window_width / 2, path2[i].y + 0), Point(path2[i + 1].x + window_width / 2, path2[i + 1].y + 0), Scalar(0, 0, 255), 1, 8);
		}

		//2017-10-30改动：不回原点，注释掉下行语句
		//line(Greedy_Algorithm_src, path2[path2.size() - 1], Point(0, 0), Scalar(0,0,255), 1, 8);
		
		//2017-11-1改动：图像镜像
		flip(Greedy_Algorithm_src, Greedy_Algorithm_src, 0);
		namedWindow("[4]path2:Greedy_Algorithm", CV_WINDOW_NORMAL);
		imshow("[4]path2:Greedy_Algorithm", Greedy_Algorithm_src);
		waitKey(0);
		// resize(Greedy_Algorithm_src, src, Size(1080, 810), 0, 0, CV_INTER_LINEAR);
		// imshow("planning", src);

		movement(path2, rho, theta, angle);
#endif


		
		

	//}
	waitKey(0);
	return 0;
}