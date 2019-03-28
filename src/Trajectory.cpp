#include"function_declare.h"

/**
 * @function FrameDiff
 * @author William YU
 * @brief 3帧差法求取运动网球
 */
bool FrameDiff(int frameNum, Mat&previousFrame, Mat&previousFrameBackup, Mat&tmpFrame, Mat&tmpFrameBackup, Mat&currentFrame, Mat&currentFrameBackup )
{
    if(frameNum == 1) //初始化
    {
        previousFrame.create(tmpFrame.size(), CV_8UC1);
        currentFrame.create(tmpFrame.size(), CV_8UC1);
        currentFrameBackup.create(tmpFrame.size(), CV_32FC1);
        previousFrameBackup.create(tmpFrame.size(), CV_32FC1);
        tmpFrameBackup.create(tmpFrame.size(), CV_32FC1);
    }

    if(frameNum >= 2)
    {
        cvtColor(tmpFrame, currentFrame, CV_BGR2GRAY);
        currentFrame.convertTo(tmpFrameBackup, CV_32FC1);
        previousFrame.convertTo(previousFrameBackup, CV_32FC1);
        absdiff(tmpFrameBackup, previousFrameBackup, currentFrameBackup);
        currentFrameBackup.convertTo(currentFrame, CV_8UC1);
        threshold(currentFrame, currentFrame, 30, 255, CV_THRESH_BINARY);
        int g_nStructElementSize = 3;
        Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point( g_nStructElementSize, g_nStructElementSize ));
        dilate(currentFrame, currentFrame, element);
        erode(currentFrame, currentFrame, element);
    }
    cvtColor(tmpFrame, previousFrame, CV_BGR2GRAY);

	//waitKey(0);
	return 1;
}

/**
 * @function polyfit
 * @author William YU
 * @brief 求解最小二乘问题
 */
//Reference:https://www.jianshu.com/p/edaf949bcaeb
//          https://blog.csdn.net/i_chaoren/article/details/79822574

Mat polyfit(vector<Point>& in_point, int n)
{
	int size = in_point.size(); 
	int x_num = n + 1;//未知数个数
	Mat U(size, x_num, CV_64F);
	Mat Y(size, 1, CV_64F);
 
	for (int i = 0; i < U.rows; i++)
		for (int j = 0; j < U.cols; j++)
		{
			U.at<double>(i, j) = pow(in_point[i].x, j);
		}
 
	for (int i = 0; i < Y.rows; ++i)
	{
		Y.at<double>(i, 0) = in_point[i].y;
	}

	Mat mat_k(x_num, 1, CV_64F);
	mat_k = ( U.t() * U ).inv() * U.t() * Y;   //核心公式！！！ K = ( U^T * U )^(-1) * U^T * Y //amazing...=_=
	cout << "Here cames mat_k..." << mat_k << endl;
	return mat_k;
}

/**
 * @function polyfit_test
 * @author William YU
 * @brief 可视化验证2次曲线拟合结果	//n:多项式拟合阶次
 */
bool polyfit_show(vector<Point>& in_point, Mat& src, int n) 
{	
	if(in_point.size()<13) //点数不够
	{
		cout<<"Points not enough!"<<endl;
		return 0;
	}

    //--计算系数矩阵--核心函数
	Mat mat_k = polyfit(in_point, n); 

    //--结果可视化验证
    //绘制锚点
	// for (int i = 0; i < in_point.size(); i++)
	// {
	// 	Point ipt = in_point[i];
	// 	circle(src, ipt, 3, Scalar(0, 0, 255), CV_FILLED, CV_AA);
	// }
    //绘制拟合曲线
	if(in_point[0].x < in_point[in_point.size()-1].x) //从左到右
	{
		for (int i = in_point[0].x; i < in_point[in_point.size()-1].x+10; i++)//只拟合起点到终点之间的曲线段,多加10像素作为预测区域
		{
			Point2d ipt;
			ipt.x = i;
			ipt.y = 0;
			for (int j = 0; j < n + 1; j++)
			{
				ipt.y += mat_k.at<double>(j, 0)*pow(i,j);//计算曲线方程 //y = a_0*x^0 + a_1*x^1 + a_2*x^2 + a_3*x^3 + ...
			}
			circle(src, ipt, 1, Scalar(255, 255, 255), CV_FILLED, CV_AA);
		}
	}
	else if(in_point[0].x > in_point[in_point.size()-1].x) //从右到左
	{
		for (int i = in_point[in_point.size()-1].x-10; i = in_point[0].x; i++)//只拟合起点到终点之间的曲线段,多加10像素作为预测区域
		{
			Point2d ipt;
			ipt.x = i;
			ipt.y = 0;
			for (int j = 0; j < n + 1; j++)
			{
				ipt.y += mat_k.at<double>(j, 0)*pow(i,j);//计算曲线方程 //y = a_0*x^0 + a_1*x^1 + a_2*x^2 + a_3*x^3 + ...
			}
			circle(src, ipt, 1, Scalar(255, 255, 255), CV_FILLED, CV_AA);
		}
	}
	
 
	imshow("polyfit_show", src);
	waitKey(0);
}

/**
 * @function main
 * @author William Yu
 */
int main ( int argc, char** argv )
{
	VideoCapture capture;
    capture = VideoCapture(0);
    //capture = VideoCapture("./data/tennis.avi");
	if(!capture.isOpened())
    {
        cout<<"ERROR:video wrong!"<<endl;
		return 0;
    }

    Mat tmpFrame, tmpFrameBackup;
    Mat currentFrame, currentFrameBackup;
    Mat previousFrame, previousFrameBackup;


	vector<Point> points;

    int frameNum = 0;
	capture >> tmpFrame;
    while(!tmpFrame.empty())
    {
		capture >> tmpFrame;

		//--运动物体检测
	    frameNum++;
    	FrameDiff( frameNum, previousFrame, previousFrameBackup, tmpFrame, tmpFrameBackup, currentFrame, currentFrameBackup );
		imshow("Frame", tmpFrame);
		imshow("Moving Object", currentFrame);
		waitKey(23);

		//--对currentFrame进行圆形检测
		//Reference:https://blog.csdn.net/chengchaopeng520/article/details/74522714
		vector<Vec3f> circles;
		Mat gray;
		cvtColor(tmpFrame, gray, cv::COLOR_BGR2GRAY);
		HoughCircles(gray, circles, HOUGH_GRADIENT, //输入，输出，方法（类型）
				1, //dp(dp=1时表示霍夫空间与输入图像空间的大小一致，dp=2时霍夫空间是输入图像空间的一半，以此类推)
				250, //最短距离-可以分辨是两个圆，否则认为是同心圆 ,
				100, //边缘检测时使用Canny算子的高阈值
				40, //中心点累加器阈值—候选圆心（霍夫空间内累加和大于该阈值的点就对应于圆心），越小越敏感，注意太敏感会导致死循环
				0, 0);//最小半径和最大半径是多少。
		if(!circles.size()) //若无结果，跳过
		{
			cout<<"No circle checked!"<<endl;
			//waitKey(0);
		}
		else //只选取一个最圆的圆//TODO：如何筛选
		{
			//输出检测到的圆的圆心像素坐标
			Point center(cvRound(circles[0][0]), cvRound(circles[0][1]));
			points.push_back(center);
			cout << center << endl;  
			int radius = cvRound(circles[0][2]);
			circle(tmpFrame, center, 4, cv::Scalar(0, 255, 0), -1, 8, 0);
			circle(tmpFrame, center, radius, cv::Scalar(155, 50, 255), 3, 4, 0);
		}
		namedWindow("circle", WINDOW_AUTOSIZE);
		imshow("circle", tmpFrame);
		//--输出坐标点集points，构建为最小二乘拟合问题

		//--求解上述最小二乘问题
		// //--debug测试点集
		// Point in[19] = { Point(50,120),Point(74,110),Point(98,100),Point(122,100),Point(144,80)
		// 	,Point(168,80),Point(192,70),Point(214,50),Point(236,40),Point(262,20)
		// 	,Point(282,20),Point(306,30),Point(328,40),Point(356,50),Point(376,50)
		// 	,Point(400,50),Point(424,50),Point(446,40),Point(468,30) };
		// vector<Point> in_point(begin(in),end(in));
		// polyfit_test(in_point);
		polyfit_show(points,tmpFrame,2);
	}
	return 0;
}