#include"function_declare.h"

/**
 * @function filter
 * @author William Yu
 * @brief 
 */
void filter(Mat &src, Mat &dst)
{
	namedWindow("before_filter", CV_WINDOW_NORMAL);
	imshow("before_filter", src);
	waitKey(0);

	uchar *dst_data;
	uchar *out_data;

	Mat element1 = getStructuringElement(MORPH_RECT, Size(25, 25));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat element3 = getStructuringElement(MORPH_RECT, Size(5, 5));


	Mat bilateral_filter;
	bilateralFilter(src, bilateral_filter, 9, 50, 70);//双边滤波
	namedWindow("双边滤波", CV_WINDOW_NORMAL);
	imshow("双边滤波", bilateral_filter);
	waitKey(0);

	Mat canny;
	Canny(bilateral_filter, canny, 30, 90);//Canny算子提取边缘
	namedWindow("canny", CV_WINDOW_NORMAL);
	imshow("canny", canny);
	waitKey(0);
	
	Mat out, out2;
	//blur(src, Colour, Size(20, 20), Point(-1, -1));
	//dilate(dst, out, element);
	//erode(out, out2, element2);
	//connectedComponents(colour_filter_img, colour_filter_img,8,4);


	Mat out3;
	bitwise_not(canny, out3); //按位反转
	threshold(out3, out3, THRESHOLD, 255, THRESH_BINARY);  //THRESHOLD参数在include_all.h里面可调
	namedWindow("threshold", CV_WINDOW_NORMAL);
	imshow("threshold", out3);
	waitKey(0);
	
	Mat out4;
	dilate(out3, out4, element1);//膨胀操作
	namedWindow("dilate", CV_WINDOW_NORMAL);
	imshow("dilate", out4);
	waitKey(0);





	for (int i = 0; i < dst.rows; i++)
	{
		dst_data = dst.ptr(i);
		out_data = out4.ptr(i);
		for (int j = 0; j < dst.cols; j++)
		{
			if (dst_data[j] > 100)
			{
				if (out_data[j] == 0)
				{
					dst_data[j] = 0;
				}
			}
		}
	}

}