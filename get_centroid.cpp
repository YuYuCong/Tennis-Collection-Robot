#include"function_declare.h"

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

	PCA pca_analysis(data_pts, Mat(), CV_PCA_DATA_AS_ROW);

	Point cntr = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
	return cntr;
}


Mat get_centroid(vector<Point> & Points, vector<Point> & Points_checked)
{
	//2017-10-31更新
	for (int i = 0; i < Points.size(); i++) {
		Points[i].x = Points[i].x + window_width / 2;
		Points[i].y = Points[i].y + 0 ;//Y方向未添加偏置
	};
	Mat image(window_height, window_width, CV_8UC3, Scalar(255,255,255) ); 
	int lineType = 8;
	for (int i = 0; i < Points.size(); i++) {
		circle(image, Points[i], radius, Scalar(0,205,0), -1, lineType);
	};
	imshow("[1]balls", image);

	Mat image2 = image.clone();
	for (int i = 0; i < Points.size(); i++) {
		circle(image2, Points[i], bigball_ball * radius, Scalar(127,255,0), -1, lineType);
	};
	//imshow("[2]bigballs", image2);
	Mat gray;
	cvtColor(image2, gray, COLOR_BGR2GRAY);
	Mat bw;
	threshold(gray, bw, 50, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	vector<Vec4i> hierarchy;
	vector<vector<Point> > contours;
	Mat bw_back = 255 - bw;
	findContours(bw_back, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours.size(); ++i)
	{
		//drawContours(image, contours, static_cast<int>(i), Scalar(0, 0, 0), 1, 8, hierarchy, 0);
		Point center = each_getCentroid(contours[i]);
		//circle(image, center, car_ball * radius, Scalar(13, 24, 216), 1, 8);
		circle(image, center, 1, Scalar(13, 24, 216), -1, 8);
		//2017-10-31更新
		center.x = center.x - window_width / 2;
		center.y = center.y - 0;
		Points_checked.push_back(center);
	}
	//检查
	//for (int i = 0; i < Points_checked.size(); i++)
	//{
	//	cout << Points_checked[i] << " ";
	//}
	//cout << endl;
	//imshow("[3]Points_checked", image);
	return image;
}
