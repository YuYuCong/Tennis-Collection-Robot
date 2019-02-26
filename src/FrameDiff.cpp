#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    VideoCapture capture;
    capture = VideoCapture("../data/tennis.avi");
    if(!capture.isOpened())
    {
        cout<<"ERROR:video wrong!"<<endl;
        return 0;
    }

    Mat tmpFrame, tmpFrameBackup;
    Mat currentFrame, currentFrameBackup;
    Mat previousFrame, previousFrameBackup;
    int frameNum = 0;
    capture >> tmpFrame;
    while(!tmpFrame.empty())
    {
        capture >> tmpFrame;
        frameNum++;
        if(frameNum == 1) //初始化
        {
            previousFrame.create(tmpFrame.size(), CV_8UC1);
            currentFrame.create(tmpFrame.size(), CV_8UC1);
            currentFrameBackup.create(tmpFrame.size(), CV_32FC1);
            previousFrameBackup.create(tmpFrame.size(), CV_32FC1);
            tmpFrameBackup.create(tmpFrame.size(), CV_32FC1);
        }

        if(frameNum >= 2)
        {
            cvtColor(tmpFrame, currentFrame, CV_BGR2GRAY);
            currentFrame.convertTo(tmpFrameBackup, CV_32FC1);
            previousFrame.convertTo(previousFrameBackup, CV_32FC1);
            absdiff(tmpFrameBackup, previousFrameBackup, currentFrameBackup);
            currentFrameBackup.convertTo(currentFrame, CV_8UC1);
            threshold(currentFrame, currentFrame, 30, 255, CV_THRESH_BINARY);
            int g_nStructElementSize = 3;
            
            // Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point( g_nStructElementSize, g_nStructElementSize ));
            // dilate(currentFrame, currentFrame, element);
            // erode(currentFrame, currentFrame, element);
        }
        cvtColor(tmpFrame, previousFrame, CV_BGR2GRAY);

        imshow("Frame", tmpFrame);
        imshow("Moving Object", currentFrame);
        waitKey(23);
    }
}

//--TODO: add color check!
//        add points trajectory pridects!