#include"function_declare.h"

void edge(Mat &src, Mat &dst)
{
	Mat filter_img;
	Mat canny_img;
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat out;
	Mat element2 = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat out2, out3;//out3:ãÐÖµ·Ö¸îºóµÄÍ¼Ïñ£»out2

	uchar *dst_data;
	uchar *out_data;

	bilateralFilter(src, filter_img, 9, 50, 70);//Ë«±ßÂË²¨
	cv::namedWindow("ÂË²¨", CV_WINDOW_NORMAL);
	imshow("ÂË²¨", filter_img);
	Canny(filter_img, dst, 30, 90);
	cv::namedWindow("aftercanny", CV_WINDOW_NORMAL);
	imshow("aftercanny", src);
	waitKey();
	//imshow("beforethreshold", src);
	//Mat mv[3];
	//split(src, mv);
	//imshow("G", mv[0]);
	//Mat gmat;
	//bitwise_not(mv[0], gmat);
	//waitKey();
	//threshold(gmat, out3, THRESHOLD, 255, THRESH_BINARY);
	imshow("threshold", out3);
	Mat out4;
	Mat ele = getStructuringElement(MORPH_RECT, Size(5, 5));
	dilate(out3, out4, ele);
	imshow("afterdilate", out4);//ÅòÕÍ²Ù×÷

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
	cv::namedWindow("canny_just", CV_WINDOW_NORMAL);
	imshow("canny_just", dst);
	//dilate(dst, out, element);
	//erode(out, out2, element2);
	//Canny(out, dst, 50, 150);
}