#include"function_declare.h"

/**
 * @function edge2list
 * @author Yang Qi
 * @brief 输出轮廓点集合
 */
void edge2list(vector<vector<Point>>& contours_dst, Mat & img, vector<Vec4i>& hierarchy)
{
	//ofstream out("out.txt");

	vector<vector<Point> > contours_src;
	findContours(img, contours_src, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i < contours_src.size(); i++)
	{
		//遍历边缘信息，只保存长度大于最小值的边缘；
		if ((hierarchy[i][3] == -1) && (contours_src[i].size() > MIN_SIZE)) {
			vector<Point>points;
			for (int k = 0; k < contours_src[i].size(); k++) 
			{
				//取出边缘上的点
				points.push_back(contours_src[i][k]);

				//if (out.is_open())   
				//{
				//	//out.seekg(0, ios::end);
				//	out.seekp(0, ios::end);
				//	out << contours_src[i][k] << "\n";
				//}

				//cout << contours_src[i][k] << endl;
			}

			//if (out.is_open())
			//{
			//	//out.seekg(0, ios::end);
			//	out.seekp(0, ios::end);
			//	out << "\n\n\n\n\n\n\n\n\n";
			//}

			//保存边缘上的点到目标向量；
			contours_dst.push_back(points);
			points.clear();
		}
	}
	//out.close();
}




/**
 * @function drawContour
 * @author Yang Qi
 * @brief 绘制所有边缘图像
 */
void drawContour(Mat & img, vector<vector<Point>>&contours, int type, Scalar color)
{
	for (size_t i = 0; i< contours.size(); i++)
	{
		drawContours(img, contours, (int)i, color, type, 8);
	}
}