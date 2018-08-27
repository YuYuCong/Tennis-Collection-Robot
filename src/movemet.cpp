#include"function_declare.h"

/// Function Definitions  
/**
 * @function movement
 * @author William Yu
 * @brief 机器人动作组转换.
 * 			输入：路径锚点，输出：动作组
 */
//Refrence:[TODO]

 void movement(vector<cv::Point>& path,  vector<double> & rho, vector<double> & theta, vector<double> & angle)
{
	 //2017-11-01更新：path不包含原点做起点，插入起点
	 path.insert(path.begin(), Point(0,0));
	 
	//--检查传入的path
	 //cout << '\n' << "";
	 //for (int i = 0; i <path.size(); i++) {
		// cout << ' ' << path[i];
	 //}
	 //cout << '\n';

	 vector<double> rho_;  //极径
	 vector<double> theta_; //极角弧度制
	 vector<double> angle_; //极角角度制
	 double alpha1, alpha2;//与x轴正方向夹角//弧度
	 
	//--计算极径
	 //2017-11-01更新：path已经包含了原点做起点，去掉下面两行代码
	 //double rho_0= sqrt((path[0].x - 0)*(path[0].x - 0)  + (path[0].y - 0)*(path[0].y - 0));
	 //rho_.push_back(rho_0);
	 for (int i = 1; i < path.size(); i++) {
		 double rho_i = sqrt((path[i].x - path[i - 1].x)*(path[i].x - path[i - 1].x)
					 + (path[i].y - path[i - 1].y)*(path[i].y - path[i - 1].y));
		 rho_.push_back(rho_i);
	 }

	//--计算极角
	 if ( path.size() == 2)
	 {
		 alpha1 = Pi / 2;
		 alpha2 = acos((path[1].x - path[0].x) / rho_[0]);//反余弦
		 if (path[1].y < path[0].y)
		 {
			 alpha2 = - alpha2 + Pi;
		 }
		 else {};
		 double theta_0 = alpha2 - alpha1;
		 theta_.push_back(theta_0);
	 }
	 else {
		 alpha1 = Pi / 2;
		 alpha2 = acos((path[1].x - path[0].x) / rho_[0]);
		 if (path[1].y < path[0].y)
		 {
			 alpha2 = -alpha2 + Pi;
		 }
		 else {};
		 double theta_0 = alpha2 - alpha1;
		 theta_.push_back(theta_0);

		 for (int i = 1; i < path.size()-1; i++)
		 {
			 double alpha_temp = 0;
			 alpha1 = alpha2;
			 alpha2 = acos((path[i+1].x - path[i].x )/ rho_[i]);
			 if (path[i+1].y < path[i].y)
			 {
				 alpha2 = -alpha2 + Pi;
			 }
			 else {};
			 alpha_temp = alpha2 - alpha1;

			 //左转（逆时针）为正
			 if (alpha_temp > 0 && path[i + 1].y >= path[i].y   &&   path[i].y >= path[i - 1].y)
			 {
				 theta_.push_back(alpha_temp);
			 }
			 else if (alpha_temp > 0 && path[i + 1].y >= path[i].y   &&   path[i].y < path[i - 1].y)
			 {
				 theta_.push_back(-(Pi - alpha_temp));
			 }
			 else if (alpha_temp > 0 && path[i + 1].y < path[i].y   &&   path[i].y >= path[i - 1].y)
			 {
				 theta_.push_back(-(Pi - alpha_temp));
			 }
			 else if (alpha_temp > 0 && path[i + 1].y < path[i].y   &&   path[i].y < path[i - 1].y)
			 {
				 theta_.push_back(alpha_temp);
			 }
			 else if (alpha_temp < 0 && path[i + 1].y >= path[i].y   &&   path[i].y >= path[i - 1].y)
			 {
				 theta_.push_back(-(-alpha_temp));
			 }
			 else if (alpha_temp < 0 && path[i + 1].y >= path[i].y   &&   path[i].y < path[i - 1].y)
			 {
				 theta_.push_back(Pi + alpha_temp);
			 }
			 else if (alpha_temp < 0 && path[i + 1].y < path[i].y   &&   path[i].y >= path[i - 1].y)
			 {
				 theta_.push_back(Pi + alpha_temp);
			 }
			 else if (alpha_temp < 0 && path[i + 1].y < path[i].y   &&   path[i].y < path[i - 1].y)
			 {
				 theta_.push_back(-(-alpha_temp));
			 }
			 else {};
		 }
	 }




	 //--制度转换
	 for (int i = 0; i < theta_.size(); i++) 
	 {
		 double theta_i = theta_[i];
		 angle_.push_back(180 * theta_i / Pi);
	 }

	 rho = rho_;
	 theta = theta_;
	 angle = angle_;
	 





	 //检查极径
	 cout << '\n' << "极径";
	 for (int i = 0; i <rho.size(); i++) {
		 cout << ' ' << rho[i];
	 }
	 cout << '\n';
	 //检查极角弧度
	 cout << '\n' << "极角弧度";
	 for (int i = 0; i <theta.size(); i++) {
		 cout << ' ' << theta[i];
	 }
	 cout << '\n';
	 //检查极角角度
	 cout << '\n' << "极角角度";
	 for (int i = 0; i <angle.size(); i++) {
		 cout << ' ' << angle[i];
	 }
	 cout << '\n';



}

