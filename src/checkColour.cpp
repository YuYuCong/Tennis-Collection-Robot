#include"function_declare.h"


/// Function Definitions  

/**
 * @function checkColor
 * @author Yang Qi
 * @brief 色彩检测
 */
//此函数当前并没有使用
bool checkColor(Mat * img, Point2i &center, double r_d,double proportion)
{
	double dx;
	double dy;
	double d;

	int channel = img->channels();
	if (channel != 3)
		return false;

	int x = center.x;
	int y = center.y;
	int r = (int)(r_d + 0.5);

	unsigned long time = 0;

	for (int i = (y - r) > 0 ? (y - r) : 0; ((i < y + r) && (i < img->rows)); i++)
	{
		for (int j = (x - r)>0 ? (x - r) : 0; ((j < x + r) && (j<img->cols)); j++)
		{
			dx = abs(x - j);
			dy = abs(y - i);
			d = sqrt(dx*dx + dy*dy);

			if (d < r_d) {
				unsigned char* srcData = img->ptr(i);

				
				if ((srcData[3 * j + 2] - srcData[3 * j] <= maxR_B)&(srcData[3 * j + 2] - srcData[3 * j] >= minR_B))
					if ((srcData[3 * j + 1] - srcData[3 * j] <= maxG_B)&(srcData[3 * j + 1] - srcData[3 * j] >= minG_B))
						if ((srcData[3 * j] >= minB)&(srcData[3 * j] <= maxB))
							if ((srcData[3 * j + 1] >= minG)&(srcData[3 * j + 2] <= maxG))
								if ((srcData[3 * j + 2] >= minR)&(srcData[3 * j + 2] <= maxR))
								{
									time++;
								}
			}

		}
	}

	if (time >= proportion*pi*r*r)
	{
		return true;
	}

	return false;
}




/**
 * @function colour
 * @author Yang Qi
 * @brief 颜色空间域滤波
 */
//此函数的参数需要调整，回归数值为经验数值
void colour(Mat &src, Mat &dst)
{
	uchar *src_data;
	uchar *out_data;

	for (int i = 0; i < src.rows; i++)
	{
		src_data = src.ptr(i);
		out_data = dst.ptr(i);
		for (int j = 0; j < src.cols; j++)
		{
			//if (src_data[j] > 100)
			//{
				long r1,r2;
				r1 = -2.499 - 0.3342 * src.at<cv::Vec3b>(i, j)[0] + 1.051 * src.at<cv::Vec3b>(i, j)[1]; //线性回归
				r2 = 0.8618 * src.at<cv::Vec3b>(i, j)[1] + 25.81;
				r1 = r1 - src.at<cv::Vec3b>(i, j)[2];
				r2 = r2 - src.at<cv::Vec3b>(i, j)[2];
				r1 = r1*r1;
				r2 = r2*r2;
				if ((r1 < 81.00) && (r2<360)) //此处参数需要调整
				{
					out_data[j] = 255;
				}
			//}
		}
	}
	
}
