#include"function_declare.h"

#define num 450

/**
 * @function ProjectiveTransform
 * @author William Yu
 * @brief 投影变换校准相机外参
 * @Reference: 
 * 		https://docs.opencv.org/3.3.1/da/d54/group__imgproc__transform.html#ga8c1ae0e3589a9d77fffc962c49b22043
 * 		https://docs.opencv.org/3.3.1/d2/de8/group__core__array.html#gad327659ac03e5fd6894b90025e6900a7
 */
void ProjectiveTransform(Mat &src, Mat &dst, Mat &transform)
{   
	//计算投影变换
	int img_height = src.rows;
	int img_width = src.cols;

	vector<Point2f> corners(4);
	corners[0] = Point2f(0, 0);
	corners[1] = Point2f(img_width, 0);
	corners[2] = Point2f(0, img_height);
	corners[3] = Point2f(img_width, img_height);

	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(0, 0);
	corners_trans[1] = Point2f(img_width, 0);
	corners_trans[2] = Point2f(num, img_height);
	corners_trans[3] = Point2f(img_width-num, img_height);
 
	transform = getPerspectiveTransform(corners,corners_trans);
	cout<<transform<<endl;
 	warpPerspective(src, dst, transform, src.size() );

	namedWindow("Perspective", CV_WINDOW_NORMAL );
	imshow("Perspective", dst );
	//waitKey(0);
}

/**
 * @function ProjectiveTransform
 * @author William Yu
 * @brief 点投影变换————直接对图片变换无用计算量太大
 */
void ProjectiveTransformPoint(vector<Point> &ponits, vector<Point> &points_trans, Mat& transform)
{
	cout<<"你猜这条函数是干什么的？"<<endl;
	Mat src=imread("./data/ball_7.jpg");
	if (src.empty())
	{
		cout << "Image load error";
		//return 0;
	}
	int img_height = src.rows;
	int img_width = src.cols;

	vector<Point2f> corners(4);
	corners[0] = Point2f(0, 0);
	corners[1] = Point2f(img_width, 0);
	corners[2] = Point2f(0, img_height);
	corners[3] = Point2f(img_width, img_height);

	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(0, 0);
	corners_trans[1] = Point2f(img_width, 0);
	corners_trans[2] = Point2f(num, img_height);
	corners_trans[3] = Point2f(img_width-num, img_height);
 
	Mat transformm = getPerspectiveTransform(corners,corners_trans);
	cout<<transformm<<endl;


	//--自己采用点投影实现的图像投影与opencv函数warpPerspective效果对比
	vector<Point2f> ponitsm, points_transm;
	for(int i=0;i<img_height;i++)
	{
		for(int j=0;j<img_width;j++)
		{
			ponitsm.push_back(Point2f(j,i));
		}
	}
 
	if (!transformm.empty())
	{   
		perspectiveTransform( ponitsm, points_transm, transformm); //<Point>不可用，必须是<Point2f>
		Mat img_trans = Mat::zeros(img_height, img_width,CV_8UC3);
		int count = 0;
		for(int i=0; i<img_height; i++)
		{
			uchar* p = src.ptr<uchar>(i);
			for(int j=0;j<img_width;j++)
			{
				int y = points_transm[count].y;
				int x = points_transm[count].x;
				uchar* temp = img_trans.ptr<uchar>(y);
				temp[x*3]  = p[j*3];
				temp[x*3+1]  = p[j*3+1];
				temp[x*3+2]  = p[j*3+2];
				count++;
			}
		}
		namedWindow("Perspectivebypoint", CV_WINDOW_NORMAL );
		imshow("Perspectivebypoint", img_trans ); 
	}

}