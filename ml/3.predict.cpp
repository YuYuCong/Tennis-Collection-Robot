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
 * Modification History    : ver1.0, 2018.08.29, William Yu
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

/// Function Definitions



/**
 * @function svm_predict
 * @author William Yu
 * @brief 
 */
void svm_predict()
{
    Ptr<SVM> svm = ml::SVM::load("TennisModel.xml");
    svm->load("TennisModel.xml"); //载入前期训练的模型

    //--预测
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

    
    namedWindow("svm_predict",WINDOW_NORMAL);
	imshow("svm_predict", image);
	waitKey(0);
}









/**
 * @function main
 * @author William Yu
 * @brief 
 */

int main(int argc, char** argv)
{
    String imageName("../data/ball.jpg"); // by default
    if (argc > 1)
    {
        imageName = argv[1];
    }
    image = imread(imageName);
	if (image.empty())
	{
		cout << "Image load error";
		return 0;
	}
	namedWindow("src",WINDOW_NORMAL);
    imshow("src", image);
	waitKey(0);

	//--svm预测
	svm_predict();
	
	
	//保存结果
    imwrite("result.png", image);   
	return 0;
}
