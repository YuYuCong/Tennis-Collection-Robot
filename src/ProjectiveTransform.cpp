#include"function_declare.h"

/**
 * @function ProjectiveTransform
 * @author William Yu
 * @brief 投影变换校准相机外参
 * @Reference: 
 * 		https://docs.opencv.org/3.3.1/da/d54/group__imgproc__transform.html#ga8c1ae0e3589a9d77fffc962c49b22043
 * 		https://docs.opencv.org/3.3.1/d2/de8/group__core__array.html#gad327659ac03e5fd6894b90025e6900a7
 */
void ProjectiveTransform(Mat &src, Mat &dst)
{   
    Point2f srcTri[4], dstTri[4];
	Mat transform(3, 3, CV_32FC1);

	//计算投影变换
	srcTri[0].x = 982;
	srcTri[0].y = 2;
	srcTri[1].x = 1882;
	srcTri[1].y = 42;
	srcTri[2].x = 7;
	srcTri[2].y = 512;
	srcTri[3].x = 2882;
	srcTri[3].y = 2477;
 
	dstTri[0].x = 982;
	dstTri[0].y = 2;
	dstTri[1].x = 1882;
	dstTri[1].y = 42;
	dstTri[2].x = 982;
	dstTri[2].y = 512;
	dstTri[3].x = 1882;
	dstTri[3].y = 2477;
 
	transform = getPerspectiveTransform( srcTri, dstTri) ;
	cout<<"transform"<<transform<<endl;
	//注意这里src和dst的输入并不是图像，而是图像对应的坐标。应用前一篇的例子，做个相反的变换：
	//perspectiveTransform( src, dst, transform );
 	warpPerspective(src, dst, transform, src.size() );

	namedWindow("Perspective", CV_WINDOW_NORMAL );
	imshow("Perspective", dst );
	//waitKey(0);
}