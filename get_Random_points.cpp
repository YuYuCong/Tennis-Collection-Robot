#include"function_declare.h"

/// Function definitions  
/**
* @function get_Random_points
*/
void get_Random_points(vector<cv::Point>& Random_points)
{
	/// create a random object (RNG)
	RNG rng;
	rng = RNG(getTickCount());
	Point point = Point(0, 0);
	//2017-10-30更新
	//int x_min = - window_width;
	//int x_max = window_width;
	//int y_min = - window_height;
	//int y_max = window_height;
	//2017-10-30更新，加偏置
	int x_min = - window_width / 2;
	int x_max = window_width / 2;
	int y_min =  0;
	int y_max = window_height;
	for (int i = 0; i < NUMBER; i++)
	{
		Point center;
		center.x = rng.uniform(x_min, x_max);
		center.y = rng.uniform(y_min, y_max);
		Random_points.push_back(center);
	}
}