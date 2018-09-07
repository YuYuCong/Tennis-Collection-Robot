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

Mat img;
Mat targetData, backData;
bool flag = true;





///  Function Declaration

void on_mouse(int event, int x, int y, int flags, void* ustc); //鼠标取样本点
void getTrainData(Mat &train_data, Mat &train_label);  //生成训练数据 
void svm_train(); //svm






/// Function Definitions



static void help()
{
    cout<< "\n--------------------------------------------------------------------------" << endl
        << "This program shows Support Vector Machines for RGB Data. "                    << endl
        << "Usage:"                                                                       << endl
        << "  ./2.tra... <path_to_img>"                                                << endl
        << "--------------------------------------------------------------------------"   << endl;
    cout<< "\n--------------------------------------------------------------------------" << endl
        << "这是个演示SVM训练RGB数据的程序 "                                                  << endl
        << "使用方法:"                                                                     << endl
        << "  ./2.tra... <path_to_img>"                                                << endl
		<< "  默认参数为  ../data/ball.jpg"                                                << endl
        << "  点击选择任意多个点作为正样本，然后按c键"                                          << endl
        << "  点击选择任意多个点作为负样本，然后按q键"                                          << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}




/**
 * @function main
 * @author William Yu
 * @brief 
 */
int main(int argc, char** argv)
{
    help();

    String imageName("../data/ball.jpg"); // by default
    if (argc > 1)
    {
        imageName = argv[1];
    }

    img = imread(imageName);


	if (img.empty())
	{
		cout << "Image load error";
		return 0;
	}
	namedWindow("src",WINDOW_NORMAL);
    setMouseCallback("src", on_mouse, 0);
 
	for (;;)
	{
        namedWindow("src",WINDOW_NORMAL);
		imshow("src", img);
 
		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "Exiting ...\n";
			break;
		}
		if ((char)c == 'c')
		{
			flag = false;
		}
		if ((char)c == 'q')
		{
			destroyAllWindows();
			break;
		}
	}
	svm_train();
	return 0;
}






/**
 * @function on_mouse
 * @brief 
 */
void on_mouse(int event, int x, int y, int flags, void* ustc)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		Point pt = Point(x, y);
		Vec3b point = img.at<Vec3b>(y, x);  //取出该坐标处的像素值，注意x,y的顺序
		Mat tmp = (Mat_<float>(1, 3) << point[0], point[1], point[2]);
		if (flag)
		{
			targetData.push_back(tmp); //加入正样本矩阵
			circle(img, pt, 2, Scalar(0, 255, 255), -1, 8); //画出点击的点 
 
		}
 
		else
		{
			backData.push_back(tmp); //加入负样本矩阵
			circle(img, pt, 2, Scalar(255, 0, 0), -1, 8);
 
		}     
		imshow("src", img);
	}
}








/**
 * @function getTrainData
 * @brief 
 */

void getTrainData(Mat &train_data, Mat &train_label)
{
	int m = targetData.rows;
	int n = backData.rows;
	cout << "正样本数：:" << m << endl;
	cout << "负样本数：" << n << endl;
	vconcat(targetData, backData, train_data); //合并所有的样本点，作为训练数据
	train_label = Mat(m + n, 1, CV_32S, Scalar::all(1)); //初始化标注
	for (int i = m; i < m + n; i++)
		train_label.at<int>(i, 0) = -1;
}






/**
 * @function svm_train
 * @brief 
 */

void svm_train()
{
    //--训练
	Mat train_data, train_label;
	getTrainData(train_data, train_label); //获取鼠标选择的样本训练数据
    
    cout << "Starting training process" << endl;
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setC(0.1);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(CV_TERMCRIT_ITER, 100, 1e-6));
	svm->train(train_data, ROW_SAMPLE, train_label);
    cout << "Finished training process" << endl;

	//--保存模型
    svm->save("TennisModel.xml"); 
    
}