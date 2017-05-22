#ifndef _MAINHEAD_H_
#define _MAINHEAD_H_


#include <time.h>
#include <conio.h>
#include "RegionGrowing.h"
#include "rtcprgb2gray.h"
#include "convolution1.h"
#include "convolution2.h"
#include "convolution3.h"
#include "ImageQuality.h"
#include "Photoshop.h"
#include "bm3d.h"
#include "denoising.h"
#include "ImageEnhancement.h"
#include "dehazing.h"
class mainHead
{
public:
	Mat Srcnn(Mat image, double UP_SCALE);
	Mat elemet = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	Mat compute(Mat image0);
	Mat  splitAndmerge(Mat a);
public:
#define CONV1_FILTERS	64
#define CONV2_FILTERS	32
#define spatialRad  3
#define colorRad  2
#define maxPyrLevel 6;
#define photoNum 14 //图片个数
#define fileLength   50//文件名字长度
#define inputString  "src//0411//0411%d.png"
#define outputString "dst//0411%d.png"
#define scale 2 //放大倍数
#define iGrowingPoint 100

};
#endif