#include"function_declare.h"

/// Function definitions  
/**
* @function Greedy_Algorithm
*/
vector<Point> Greedy_Algorithm( vector<Point>&center_points )
{
	vector<Point> path2;

	//检查传入的中心点数和坐标
	cout << "网球坐标:"<<"  ";
	for (int i = 0; i <center_points.size(); i++) {
		cout << center_points[i] << ' ';
	}
	cout << '\n';


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////建立权重矩阵表
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int row = center_points.size() + 1, column = center_points.size() + 1;
	double **distances = new double*[row];
	for (int i = 0; i < row; ++i) {
		distances[i] = new double[column];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			distances[i][j] = 0;
		}
	}
	distances[0][0] = 0;  //角点
	for (int j = 1; j < center_points.size() + 1; j++) {
		distances[0][j] =
			sqrt((center_points[j - 1].x - 0)*(center_points[j - 1].x - 0)
				+ (center_points[j - 1].y - 0)*(center_points[j - 1].y - 0));
	}
	for (int i = 1; i < center_points.size() + 1; i++) {
		distances[i][0] = distances[0][i];
	}
	for (int i = 1; i < center_points.size() + 1; i++) {
		for (int j = 1; j < center_points.size() + 1; j++) {
			distances[i][j] =
				sqrt((center_points[i - 1].x - center_points[j - 1].x)*(center_points[i - 1].x - center_points[j - 1].x)
					+ (center_points[i - 1].y - center_points[j - 1].y)*(center_points[i - 1].y - center_points[j - 1].y));
		}
	}

	////检查    权重矩阵表
	//for (int j = 0; j < center_points.size() + 1; j++) {
	//	for (int i = 0; i < center_points.size() + 1; i++) {
	//		cout << distances[i][j] << ' ';
	//	}
	//	cout << '\n';
	//}

	int list_size = center_points.size() + 1;
	int *list = new int[list_size];
	for (int i = 0; i < list_size; i++) {
		list[i] = i;
	}

	int n = center_points.size() + 1;
	int i, j, k, l;
	double distances_min = 0;   
	double Dtemp;             
	int flag;               
	i = 1;               
	list[0] = 0;

	do {
		k = 1; Dtemp = 1000000000;
		do {
			l = 0; flag = 0;
			do {
				if (list[l] == k) {
					flag = 1;
					break;
				}
				else
					l++;
			} while (l < i);
			if (flag == 0 && distances[k][list[i - 1]] < Dtemp) {
				j = k;
				Dtemp = distances [ k ] [list[i - 1] ];
			}
			k++;
		} while (k < n);
		list[i] = j;
		i++;
		distances_min += Dtemp;
	} while (i < n);
	//2017-10-30改动：不回原点,注释掉下一行
	//distances_min += distances [0][j];
	for (i = 1; i < n; i++) {
		path2.push_back( center_points[list[i] - 1 ] );
	}

	////检查...输出经过的代号的路径//list里面最前面的0是无效路径
	//for (j = 0; j < n; j++) {
	//	cout << list[j] << " ";
	//}

	//检查传出的最优解坐标
	cout << '\n' << "最优路径";
	for (int i = 0; i <path2.size(); i++) {
		cout << ' ' << path2[i];
	}
	cout << '\n';

	//路径输出
	cout << "最短路径长度" << distances_min << '\n';

	//waitKey();
	delete[]list;
	return path2;
}