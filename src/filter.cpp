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
	uchar *out_data;             //为什么要定义这两个指针啊？程序中并未用到。 by Sunnie 20181020

	Mat element1 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat element2 = getStructuringElement(MORPH_RECT, Size(10, 10));
	Mat element3 = getStructuringElement(MORPH_RECT, Size(5, 5));

	//膨胀
	dilate(src, src, element3);
	namedWindow("dilate_filter", CV_WINDOW_NORMAL);
	imshow("dilate_filter", src);
	waitKey(0);

	//双边滤波
	Mat bilateral_filter;
	bilateralFilter(src, bilateral_filter, 9, 50, 70);
	namedWindow("bilateral_filter", CV_WINDOW_NORMAL);
	imshow("bilateral_filter", bilateral_filter);
	waitKey(0);

	//Canny算子提取边缘
	Mat canny;
	Canny(bilateral_filter, canny, 150, 120);
	namedWindow("canny", CV_WINDOW_NORMAL);
	imshow("canny", canny);
	waitKey(0);
	
	
	//Mat out, out2;
	//blur(src, Colour, Size(20, 20), Point(-1, -1));
	//dilate(dst, out, element);
	//erode(out, out2, element2);
	//connectedComponents(colour_filter_img, colour_filter_img,8,4);
	
	//按位反转
	// Mat out3;
	// bitwise_not(bit_not, out3); 
	// namedWindow("bit_not", CV_WINDOW_NORMAL);
	// imshow("bit_not", out3);
	// waitKey(0);

	dst = canny;
}