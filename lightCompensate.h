#ifndef _LIGHTCOMPENSATE_H_
#define _LIGHTCOMPENSATE_H_
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

class lightCompensate
{
public:
	Mat  Compensate(Mat dst);
public:
	const float thresholdco = 0.15;
	const int thresholdnum = 50;	
	const int threshold = 108;
	double beta = 0.15;//调整亮度
	double alpha; //调整对比度
public:
	Mat dstImage;
	vector<Mat> g_vChannels;
};
#endif