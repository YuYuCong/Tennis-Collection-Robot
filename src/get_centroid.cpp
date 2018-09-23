#include"function_declare.h"

/// Function Definitions  



/**
 * @function each_getCentroid
 * @author William Yu
 * @brief 获取一组轮廓点的形心
 */
Point each_getCentroid(vector<Point> list)
{
	Point result_point(0, 0);
	int sz = static_cast<int>(list.size());
	Mat data_pts = Mat(sz, 2, CV_64FC1);
	for (int i = 0; i < data_pts.rows; ++i)
	{
		data_pts.at<double>(i, 0) = list[i].x;
		data_pts.at<double>(i, 1) = list[i].y;
	}

	//PCA主成分分析
	PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);

	Point cntr = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
	return cntr;
}




/**
 * @function get_centroid
 * @author William Yu
 * @brief 由已检测出的网球坐标点，聚合距离较近的网球坐标，完成对距离较近的网球一次性直接收集
 */
Mat get_centroid(vector<Point> & Points, vector<Point> & Points_checked)
{
	//2017-10-31更新：添加偏置
	//之前使用左下角作为原点，添加偏置使用图像下边界中点作为原点
	for (int i = 0; i < Points.size(); i++) {
		Points[i].x = Points[i].x + window_width / 2;
		Points[i].y = Points[i].y + 0 ;//Y方向未添加偏置，因为不需要
	};


	//--绘制网球
	Mat image(window_height, window_width, CV_8UC3, Scalar(255,255,255) ); 
	int lineType = 8;
	for (int i = 0; i < Points.size(); i++) {
		circle(image, Points[i], radius, Scalar(0,205,0), -1, lineType);
	};
	namedWindow("[1]balls", CV_WINDOW_NORMAL);
	imshow("[1]balls", image);
	waitKey(0);


	//--膨胀出大网球，将距离较近的园合为一个连通域
	Mat image2 = image.clone();
	for (int i = 0; i < Points.size(); i++) {
		circle(image2, Points[i], bigball_ball * radius, Scalar(127,255,0), -1, lineType);
	};
	namedWindow("[2]bigballs", CV_WINDOW_NORMAL);
	imshow("[2]bigballs", image2);
	waitKey(0);



	Mat gray;
	cvtColor(image2, gray, COLOR_BGR2GRAY);
	Mat bw;
	threshold(gray, bw, 50, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;
	Mat bw_back = 255 - bw;
	
	//--查找新的大轮廓
	findContours(bw_back, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	
	for (int i = 0; i < contours.size(); ++i)
	{
		drawContours(image, contours, static_cast<int>(i), Scalar(0, 255, 0), 1, 8, hierarchy, 0);
		
		//--获取所有新大轮廓的中心位置，最核心的函数就这一句
		Point center = each_getCentroid(contours[i]);
		
		
		circle(image, center, car_ball * radius, Scalar(13, 24, 216), 1, 8);
		circle(image, center, 1, Scalar(13, 24, 216), -1, 8);
		
		//2017-10-31更新，添加偏置
		center.x = center.x - window_width / 2;
		center.y = center.y - 0;

		Points_checked.push_back(center);
	}

	//--输出检查
	//for (int i = 0; i < Points_checked.size(); i++)
	//{
	//	cout << Points_checked[i] << " ";
	//}
	//cout << endl;
	namedWindow("[3]Points_distance_checked", CV_WINDOW_NORMAL);
	imshow("[3]Points_distance_checked", image);
	waitKey(0);

	return image;
}