/*=================================================================================
 *                      Copyleft! 2018 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2018 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : 
 * Description             : Machine Learning SVM （编译环境：opencv3.3.1+Linux）
 *                           由前景背景颜色构建的样本空间，使用SVM目标检测
 * Reference               : https://docs.opencv.org/3.3.1/d0/dcc/tutorial_non_linear_svms.html
 *                           http://www.cnblogs.com/LeftNotEasy/archive/2011/05/02/basic-of-svm.html
 * Programmer(s)           : William Yu, windmillyucong@163.com
 * Company                 : HUST, DMET国家重点实验室FOCUS团队
 * Modification History    : ver1.0, 2018.12.30, William Yu
 *                           
=================================================================================*/

/// Include Files
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
using namespace cv;
using namespace cv::ml;
using namespace std;


/// Global Variables
Mat image;
string path_to_data = "../data/";
string videoname = "video.mp4";

int64 st1, et1;//计时优化
int64 st2, et2;//计时优化
int64 st3, et3;//计时优化
int64 st4, et4;//计时优化

#define k 0.9  //数据压缩比例
#define gFREC 1 //频率



/// Function Definitions


/**
 * @function svm_predict
 * @author William Yu
 * @brief 
 */
void svm_predict()
{
    Ptr<SVM> svm = ml::SVM::load("TennisModel.xml");

	st3 = cvGetTickCount();
    svm->load("TennisModel.xml"); //载入前期训练的模型
	et3 = cvGetTickCount();
	cout << "times cost of SVM_Load_Model:" << (et3 - st3) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";
	
    
    //--预测
	st4 = cvGetTickCount();
	Vec3b color(0, 0, 0);
	for (int i = 0; i < image.rows; ++i)
		for (int j = 0; j < image.cols; ++j)
		{
			Vec3b point = image.at<Vec3b>(i, j);  //取出该坐标处的像素值
			Mat sampleMat = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
			float response = svm->predict(sampleMat);  //进行预测，返回1或-1,返回类型为float
			if ((int)response != 1)
				image.at<Vec3b>(i, j) = color;  //将背景设置为黑色
		}
	et4 = cvGetTickCount();
	cout << "times cost of SVM_Predict:" << (et4 - st4) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";
}






/**
 * @function main
 * @author William Yu
 * @brief 
 */

int main(int argc, char** argv)
{
	//VideoCapture capture(path_to_data + videoname);  //使用数据集
	VideoCapture capture(0);  //使用相机
    cout<<"width:"<<capture.get(CV_CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"height:"<<capture.get(CV_CAP_PROP_FRAME_HEIGHT)<<endl;
	
    //Mat frame;

	while (capture.isOpened())
	{
        capture >> image;
		st1 = cvGetTickCount();
		//imshow("frame", image);
        resize(image, image, Size(k*capture.get(CV_CAP_PROP_FRAME_WIDTH), k*capture.get(CV_CAP_PROP_FRAME_HEIGHT)), 0, 0, CV_INTER_LINEAR);
		et1 = cvGetTickCount();
		cout << "times cost of Resize:" << (et1 - st1) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";
		
    
		//--svm预测
		st2 = cvGetTickCount();
		svm_predict();
		et2 = cvGetTickCount();
		cout << "times cost of SVM:" << (et2 - st2) / (double)cvGetTickFrequency() / 1000.0 << "milliseconds\n\n";

		//显示结果
		namedWindow("svm_predict",WINDOW_NORMAL);
		imshow("svm_predict", image);

		//--然后用之前的程序求取中心

        char key = (char)waitKey(gFREC);
        if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
           break;

	}
	return 0;
}