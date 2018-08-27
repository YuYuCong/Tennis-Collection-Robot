#include"function_declare.h"

/// Function Definitions  

/**
 * @function get_Random_points
 * @author William Yu
 * @brief 由于没有足够的网球图片测试路径规划，可以使用此函数生成一批随机点，模拟网球目标
 */
void get_Random_points(vector<cv::Point>& Random_points, int NUMBER)
{
	//-- create a random object (RNG)
	RNG rng;
	rng = RNG(getTickCount());
	Point point = Point(0, 0);
	
	//2017-10-30，修改随机点区域限制
	//int x_min = - window_width;
	//int x_max = window_width;
	//int y_min = - window_height;
	//int y_max = window_height;
	//2017-10-30，添加偏置
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
