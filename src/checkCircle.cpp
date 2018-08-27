#include"function_declare.h"

#define THRESHOL_CLASS (double)30



/// Function Definitions  

/**
 * @function calcCenter
 * @author Yang Qi
 * @brief 计算中心点
 */
bool calcCenter(vector<Point> &contour, Point &center) 
{
	vector<float> distance;
	int x, y;
	int x1, y1;
	int x_fin, y_fin;
	double dis_all = 0;
	float dis = 0, dis_2;

	//--计算轮廓的中心点
	x = contour[0].x;
	y = contour[0].y;//起点坐标
	for (int i = 1; i<contour.size(); i++) //遍历整个轮廓，找到距离起点最远的点
	{
		x1 = contour[i].x;
		y1 = contour[i].y;
		dis_2 = (x1 - x)*(x1 - x) + (y1 - y)*(y1 - y);
		if (dis_2>dis) {
			dis = dis_2;
			x_fin = x1;
			y_fin = y1;
		}
	}
	x_fin = (x + x_fin) / 2;
	y_fin = (y + y_fin) / 2;
	center.x = x_fin;
	center.y = y_fin;


	//--计算轮廓上每个点到中心点的距离集合
	for (int i = 0; i<contour.size(); i++) 
	{
		x1 = contour[i].x;
		y1 = contour[i].y;
		dis = (x1 - x_fin)*(x1 - x_fin) + (y1 - y_fin)*(y1 - y_fin);
		distance.push_back(dis);
		dis_all += dis;
	}


	//--圆形误差判断
	//[问题描述]如何评价一组数据的离散程度？
	//平均差或者方差
	float r = dis_all / distance.size(); //周径均值
	dis_all = 0;
	for (int i = 0; i<distance.size(); i++) 
	{

		//平均差 描述一组数据的离散程度 //从0到n对|x_i-x_ba|求和，再除以n
		dis_all += abs(distance[i] - r);
		//方差 描述一组数据的离散程度  //从0到n对|x_i-x_ba|^2求和，再除以n
		//dis_all += ((distance[i] - r) * (distance[i] - r)); 

	}
	double dis_class = dis_all / distance.size();
	
	if (dis_class < THRESHOL_CLASS) {
		return true;
	}
	else {
		return false;
	}
}
//--关于上述函数：这个圆形判断方法异常简陋，可改进的地方很多





/**
 * @function checkCircle
 * @author Yang Qi
 * @brief 圆形检测
 */
vector<Point> checkCircle(vector<vector<Point>> &contours) 
{
	Point point = Point(0, 0);

	vector<Point> points;
	for (int i = 0; i < contours.size(); i++)
	{
		if (calcCenter(contours[i], point)) //计算中心点坐标
		{
			points.push_back(point);
		}
	}
	return points;
}












/**
 * @function calcDistance
 * @author Yang Qi
 * @brief 距离计算
 */
vector<Point2f> calcDistance(vector<Point> points) {
	vector<Point2f> distances;
	//[TODO]
	return distances;
}
//没有使用