#include"function_declare.h"
#include<math.h>



using namespace cv;
void colour(Mat &src, Mat &colour_img1)
{
	Mat colour_i;
	//Mat colour_img1;
	uchar *src_data;
	uchar *out_data;
	Mat colour_img(src.rows, src.cols, CV_8UC1, Scalar(0));
	/*
	for (int i = 0; i < src.rows; i++)
	{

		for (int j = 0; j < src.cols; j++)
		{
			long r;// r值的空间距离
			r = 60.82 + 0.3645*src.at<cv::Vec3b>(i, j)[0] + 0.4813*src.at<cv::Vec3b>(i, j)[1];
			r = r - src.at<cv::Vec3b>(i, j)[2];
			r = r*r;
			if (r < 20.00)        //阈值调整
			{
				colour_img = 255;
			}
		}
		  
	
	}*/
	for (int i = 0; i < src.rows; i++)
	{
		src_data = src.ptr(i);
		out_data = colour_img.ptr(i);
		for (int j = 0; j < src.cols; j++)
		{
			//if (src_data[j] > 100)
			//{
				long r1,r2;
				r1 = -2.499 - 0.3342*src.at<cv::Vec3b>(i, j)[0] + 1.051*src.at<cv::Vec3b>(i, j)[1];
				r2 = 0.8618*src.at<cv::Vec3b>(i, j)[1] + 25.81;
				r1 = r1 - src.at<cv::Vec3b>(i, j)[2];
				r2 = r2 - src.at<cv::Vec3b>(i, j)[2];
				r1 = r1*r1;
				r2 = r2*r2;
				if ((r1 < 81.00) && (r2<360))
				{
					out_data[j] = 255;
				}
			//}
		}
	}
	Mat ele = getStructuringElement(MORPH_RECT, Size(25, 25));
	Mat ele2 = getStructuringElement(MORPH_RECT, Size(20, 20));
	dilate(colour_img, colour_i, ele);
	erode(colour_i, colour_img1, ele);
	//connectedComponents(colour_img, colour_img1,8,4);
	cv::namedWindow("colour", CV_WINDOW_NORMAL);
	imshow("colour", colour_img1);
}

void main()
{
	//VideoCapture capture(1);
	while (1)
	{
	
	vector<vector<cv::Point> >  contours_dst;
	vector<Vec4i> hierarchy;

	vector<vector<cv::Point> >  contours_dst2;
	vector<Vec4i> hierarchy2;
	Mat src;
	//capture >> src;
	Mat fram = imread("ball6.jpg");
	//imshow("src_main", src);
	resize(fram, src, Size(1920, 1440), 0, 0, CV_INTER_LINEAR);
	Mat edge_img(src.rows,src.cols,CV_8UC1,Scalar(0));
	Mat edge_img2(src.rows, src.cols, CV_8UC1, Scalar(0));
	Mat list_filled_img(src.rows, src.cols, CV_8UC1,Scalar(0));
	Mat list_img(src.rows, src.cols, CV_8UC1, Scalar(0));
	Mat list_img2(src.rows, src.cols, CV_8UC1, Scalar(0));//和原图一样大小的黑图
	//Mat colour_img(src.rows, src.cols, CV_8UC1, Scalar(0));
	Mat colour_img2;
	Mat Colour;
	// bilateralFilter(src, Colour, 9, 50, 90);//双边滤波
	blur(src, Colour, Size(20, 20), Point(-1, -1));
	colour(Colour, colour_img2);
	//src = colour_img2;
	cv::namedWindow("colour", CV_WINDOW_NORMAL);
	cv::namedWindow("canny", CV_WINDOW_NORMAL);
	imshow("colour", colour_img2);
	waitKey(5000);
	Canny(colour_img2, edge_img, 150, 120);
	imshow("canny", edge_img);


	//waitKey();
	//edge(src,  edge_img);
	
	edge2list(contours_dst, edge_img, hierarchy);
	drawContour(list_filled_img, contours_dst);
	//vector<Point> point = checkCircle(contours_dst);
	Point point = Point(0, 0);

	//Mat src = imread("ball.jpg", 0);
	vector<Point> points;
	for (int i = 0; i < contours_dst.size(); i++)
	{
		if (calcCenter(contours_dst[i], point)) 
		{
			points.push_back(point);
			circle(src, point, 4, Scalar(0), 3);
		}
	}
	//参数
	double center_x, center_y;//中心坐标值
	float kx, ky, bx, by;   //kx,ky为系数，bx,by为偏置；
	kx = 1;
	ky = 1;
	bx = 0;
	by = 0;

	double fx = 2671.557;
	double fy = 2680.628;
	double cx = 1660.216;
	double cy = 1213.749;       //相机内参

	int theta_1=77;//水平视场角
	int theta_2=53;//垂直视场角
	int pitch=60;//俯仰角
	int height=30;//车高
	int theta_x1;//绝对值
	
	
	
	for (int i = 0; i < points.size(); i++)
	{
		int x = points[i].x;
		int y = points[i].y;
		
		//x = x*fx + cx;
		//y = y*fy + cy;
		x = x / 0.588;
		y = y / 0.588;
		x = kx *x + bx;
		y = ky*y + by;

		//printf("the x y is %d,%d", x, y);

		int theta_x = (x - 1660)*theta_1 / 3264;//极坐标角度值可输出
		//theta_x = theta_x - 0;
		
		int distance_y = 0.665*height * tan((((1213 - y)*theta_2 / 2448) + pitch)*pi / 180)-36;  //直角坐标y输出
		//if(theta_x < 0)
			//theta_x1 = -theta_x;
		//distance_y = 720+ distance_y;
		x = distance_y*tan(theta_x*pi / 180);
		points[i].x = x;
		points[i].y = distance_y;
		printf("the x is%d,y is%d", x, y);

	}

	
	cv::namedWindow("1", CV_WINDOW_NORMAL);
	imshow("1", src);

	vector<Point>  Points_checked;
	//Mat src;
	src = get_centroid(points, Points_checked);  ///处理,获取形心
	int64 st2, et2;
	st2 = cvGetTickCount();
	////////////////////////第二种////////////////////////////////////////
	vector<Point> path2 = Greedy_Algorithm(Points_checked);
	////////////////////////第二种////////////////////////////////////////
	et2 = cvGetTickCount();
	cout << "times cost:" << (et2 - st2) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";

	//2017-10-31更新,加入偏置，更改下列语句块
	//Mat Greedy_Algorithm_src = src.clone();
	//line(Greedy_Algorithm_src, Point(0, 0), path1[0], Scalar(255, 0, 0), 1, 8);
	//for (int i = 0; i < path1.size() - 1; i++)
	//{
	//	line(Greedy_Algorithm_src, path1[i], path1[i + 1], Scalar(255, 0, 0), 1, 8);
	//}
	Mat Greedy_Algorithm_src = src.clone();
	line(Greedy_Algorithm_src, Point(0 + window_width / 2, 0 + 0), Point(path2[0].x + window_width / 2, path2[0].y + 0), Scalar(0, 0, 255), 1, 8);
	for (int i = 0; i < path2.size() - 1; i++)
	{
		line(Greedy_Algorithm_src, Point(path2[i].x + window_width / 2, path2[i].y + 0), Point(path2[i + 1].x + window_width / 2, path2[i + 1].y + 0), Scalar(0, 0, 255), 1, 8);
	}
	//2017-10-30改动：不回原点
	//line(Greedy_Algorithm_src, path2[path2.size() - 1], Point(0, 0), Scalar(0,0,255), 1, 8);
	//2017-11-1改动：图像镜像
	cv::flip(Greedy_Algorithm_src, Greedy_Algorithm_src, 0);
	cv::namedWindow("[4]path2:Greedy_Algorithm", CV_WINDOW_NORMAL);
	imshow("[4]path2:Greedy_Algorithm", Greedy_Algorithm_src);
	resize(Greedy_Algorithm_src, src, Size(1080, 810), 0, 0, CV_INTER_LINEAR);
	imshow("planning", src);


	vector<double> rho;  //极径
	vector<double> theta; //极角弧度制
	vector<double> angle; //极角角度制
	movement(path2, rho, theta, angle);

	}
	//waitKey();
}