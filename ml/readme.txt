/*=================================================================================
 *                      Copyleft! 2018 William Yu
 *          Some rights reserved：CC(creativecommons.org)BY-NC-SA
 *                      Copyleft! 2018 William Yu
 *      版权部分所有，遵循CC(creativecommons.org)BY-NC-SA协议授权方式使用
 *
 * Filename                : 
 * Description             : Machine Learning SVM （编译环境：opencv3.3.1+Linux）
 *                           关于机器学习svm的一些学习和探究
 * Reference               : https://docs.opencv.org/3.3.1/d0/dcc/tutorial_non_linear_svms.html
 *                           http://www.cnblogs.com/LeftNotEasy/archive/2011/05/02/basic-of-svm.html
 * Programmer(s)           : William Yu, windmillyucong@163.com
 * Company                 : HUST, DMET国家重点实验室FOCUS团队
 * Modification History    : ver1.0, 2018.08.29, William Yu
 *                           
=================================================================================*/



# 说明 
0.allinone.cpp 
是一份程序完成数据采集，svm训练，以及图片预测环节。
此文件来源与opencv2.7例程，但是由于opencv3.3.1对与ml模块做了重大改进，不提供此例程，svm的实现函数以及参数有较大变动，具体情况请查看opencv官方说明。

1.get_data.cpp 
2.training_svm.cpp
3.predict.cpp
这三份文件是拆分出来的三个程序，每个程序负责其中一部分

non_linear_svms_test.cpp
此文件改造于opencv官方例程，尝试读取数据集文件../data/data.txt，然后进行svm模型训练，并进行预测，程序有bug，尚未调通。



# Build

mkdic build
cd build
cmake ..
make 



# Usage

cd bin
./0.allinone <path_to_img1待训练图片> <path_to_img2被预测图片>  默认参数为../data/ball.jpg
./1.get...
./2.tra... <path_to_img>"   默认参数为../data/ball.jpg"   
./3.pre... <path_to_img>    默认参数为../data/ball.jpg"   
./non_linear_svms_test
具体使用详情会在终端输出help信息



# 可能出现的问题

$ ./0.allinone <../data/ball_3.jpg><../data/ball_6.jpg>
bash: 未预期的符号 `<' 附近有语法错误

解决方法：$ ./0.allinone '../data/ball_3.jpg' '../data/ball_6.jpg'



# 建议
用比较复杂的环境来训练模型，
保证正样本分布比较相似，负样本包含其他各种杂乱的色彩
比如使用data/ball_4.jpg训练出模型，预测其他图片时，效果很不错。
