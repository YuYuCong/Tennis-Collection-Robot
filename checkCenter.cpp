#include"function_declare.h"

#define THRESHOL_CLASS (double)350


bool calcCenter(vector<Point> &contour, Point &center) 
{
	vector<float> distance;
	int x, y;
	int x1, y1;
	int x_fin, y_fin;
	double dis_all = 0;
	float dis = 0, dis_2;

	x = contour[0].x;
	y = contour[0].y;
	for (int i = 1; i<contour.size(); i++)
	{
		x1 = contour[i].x;
		y1 = contour[i].y;
		dis_2 = (x1 - x)*(x1 - x) + (y1 - y)*(y1 - y);
		if (dis_2>dis) 
		{
			dis = dis_2;
			x_fin = x1;
			y_fin = y1;
		}
	}
	x_fin = (x + x_fin) / 2;
	y_fin = (y + y_fin) / 2;
	center.x = x_fin;
	center.y = y_fin;
	for (int i = 0; i<contour.size(); i++) 
	{
		x1 = contour[i].x;
		y1 = contour[i].y;
		dis = (x1 - x_fin)*(x1 - x_fin) + (y1 - y_fin)*(y1 - y_fin);
		distance.push_back(dis);
		dis_all += dis;
	}
	float r = dis_all / distance.size();
	dis_all = 0;
	//float rr = r - (0.0668*y_fin + 22.21);
	//rr = rr*rr;
	//if (rr < 1)
	//{
	
		for (int i = 0; i<distance.size(); i++)
		{
		dis_all += abs(distance[i] - r);// *(distance[i] - r);
		}
		double dis_class = dis_all / distance.size();
		if ((dis_class<THRESHOL_CLASS))
		{
			return true;
		}
		else
		{
			return false;
		}
  // }
}


vector<Point> checkCircle(vector<vector<Point>> &contours) 
{
	Point point = Point(0, 0);
	
	//Mat src = imread("ball.jpg", 0);
	vector<Point> points;
	for (int i = 0; i < contours.size(); i++)
	{
		if (calcCenter(contours[i], point))
		{
			points.push_back(point);
			//circle(src, point, 1, Scalar(0), 3);
		}
	}
	
	//waitKey();
	return points;
}


vector<Point2f> calcDistance(vector<Point> points) {
	vector<Point2f> distances;
	
	return distances;
}