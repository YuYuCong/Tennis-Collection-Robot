/*=================================================================================
 *                      Copyleft! 2018 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2018 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : 
 * Description             : Machine Learning_SVM 线性不可分
 * Reference               : https://docs.opencv.org/3.3.1/d0/dcc/tutorial_non_linear_svms.html
 *                           http://www.cnblogs.com/LeftNotEasy/archive/2011/05/02/basic-of-svm.html
 * Programmer(s)           : William Yu, windmillyucong@163.com
 * Company                 : HUST, DMET国家重点实验室FOCUS团队
 * Modification History    : ver1.0, 2018.08.28, William Yu
 *
=================================================================================*/

//------------------------线性不可分----------
//------------------------尝试载入数据集文件../data/data.txt进行训练---------
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>

#define	NTRAINING_SAMPLES	10			// Number of training samples per class //每种类型的训练样本数量

using namespace cv;
using namespace cv::ml;
using namespace std;

static void help()
{
    cout<< "\n--------------------------------------------------------------------------" << endl
        << "This program shows Support Vector Machines for Non-Linearly Separable Data. " << endl
        << "Usage:"                                                               << endl
        << "./non_linear_svms" << endl
        << "--------------------------------------------------------------------------"   << endl
        << endl;
}

int main()
{
    help();

    //--Data for visual representation
    //--数据可视化
    const int WIDTH = 255, HEIGHT = 255;
    Mat I = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);

    Mat trainData(10, 2, CV_32FC1);
    Mat labels   (10, 1, CV_32SC1);







    //--从txt文件读取训练数据
    string dataset_dir = "../data/"; //数据集地址
    cout<<"dataset: "<<dataset_dir<<endl;
    ifstream fin ( dataset_dir+"data.txt" );//数据文件名称
    if ( !fin )
    {
        cout<<"please generate the data file called data.txt!"<<endl;
        return 1;
    }
    
    int i=0;
    while ( !fin.eof() )
    {
        string label, b, g, r;
        fin>>label>>r>>g>>b;
        labels.at<int>(i,0) = atof ( label.c_str() );
        trainData.at<float>(i,0) = atof ( b.c_str() );
        trainData.at<float>(i,1) = atof ( g.c_str() );
        //trainData.at<float>(i,2) = atof ( r.c_str() ); //暂且测试二维数据，不读入第三个数据
        cout<<"label:"<<labels.at<int>(i,0)<<" b"<<trainData.at<float>(i,0)<<" g"<<trainData.at<float>(i,1)<<endl;
        //cout<<"label:"<<labels.at<int>(i,0)<<" b"<<trainData.at<float>(i,0)<<" g"<<trainData.at<float>(i,1)<<" r"<<trainData.at<float>(i,2)<<endl;
        
        i++;
        if ( fin.good() == false )
            break;
    }
    cout<<"read total "<<labels.size() <<"training data"<<endl;

    //--检查数据是否正确读入
    for (int n = 0; n < NTRAINING_SAMPLES; n++)
    {
        cout<<"label:"<<labels.at<int>(n,0)<<endl;
        cout<<" b"<<trainData.at<float>(n,0)<<" g"<<trainData.at<float>(n,1)<<endl;//<<" r"<<trainData.at<float>(i,2)<<endl;
    }











    //------------------------ 2. Set up the support vector machines parameters --------------------
    //------------------------ 3. Train the svm ----------------------------------------------------
    cout << "Starting training process" << endl;
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setC(0.1);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, (int)1e7, 1e-6));
    //train
    svm->train(trainData, ROW_SAMPLE, labels);
    
    cout << "Finished training process" << endl;

    //------------------------ 4. Show the decision regions ----------------------------------------
    Vec3b green(0,100,0), blue (100,0,0), red (0,0,100);
    for (int i = 0; i < I.rows; ++i)
        for (int j = 0; j < I.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,2) << i, j);
            float response = svm->predict(sampleMat);

            if      (response == 1)    I.at<Vec3b>(j, i)  = green;
            else if (response == 2)    I.at<Vec3b>(j, i)  = blue;
            else                       I.at<Vec3b>(j, i)  = red;
        }
    



    //----------------------- 5. Show the training data --------------------------------------------
    int thick = -1;
    int lineType = 8;
    float px, py;
    
    for (int i = 0; i < NTRAINING_SAMPLES; ++i)
    {
        if (labels.at<int>(i,0) == 1){
            px = trainData.at<float>(i,0);
            py = trainData.at<float>(i,1);
            circle(I, Point( (int) px,  (int) py ), 3, Scalar(0, 250, 0), thick, lineType);
        }
        else if (labels.at<int>(i,0) == 2){
            px = trainData.at<float>(i,0);
            py = trainData.at<float>(i,1);
            circle(I, Point( (int) px,  (int) py ), 3, Scalar(255, 0, 0), thick, lineType);
        }
    }
    
    



    //------------------------- 6. Show support vectors --------------------------------------------
    thick = 2;
    lineType  = 8;
    Mat sv = svm->getUncompressedSupportVectors();

    for (int i = 0; i < sv.rows; ++i)
    {
        const float* v = sv.ptr<float>(i);
        circle(	I,  Point( (int) v[0], (int) v[1]), 6, Scalar(128, 128, 128), thick, lineType);
    }


    //imwrite("result.png", I);	                   // save the Image
    imshow("SVM for Non-Linear Training Data", I); // show it to the user
    waitKey(0);
}