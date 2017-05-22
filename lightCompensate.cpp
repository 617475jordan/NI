#include "lightCompensate.h"

/***根据高光区域直方图计算进行光线补偿***/
Mat  lightCompensate::Compensate(Mat dst)
{
	int histogram[256] = { 0 };
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int b = dst.at<Vec3b>(i, j)[0];
			int g = dst.at<Vec3b>(i, j)[1];
			int r = dst.at<Vec3b>(i, j)[2];
			//计算灰度值
			int gray = (r * 299 + g * 587 + b * 114) / 1000;
			histogram[gray]++;
		}
	}
	int calnum = 0;
	int total = dst.rows * dst.cols;
	int num;
	//下面的循环得到满足系数thresholdco的临界灰度级
	for (int i = 0; i < 256; i++)
	{
		if ((float)calnum / total < thresholdco) //得到前5%的高亮像素。
		{
			calnum += histogram[255 - i];//histogram保存的是某一灰度值的像素个数,calnum是边界灰度之上的像素数
			num = i;
		}
		else
			break;
	}
	int averagegray = 0;
	calnum = 0;
	//得到满足条件的象素总的灰度值
	for (int i = 255; i >= 255 - num; i--)
	{
		averagegray += histogram[i] * i; //总的像素的个数*灰度值
		calnum += histogram[i]; //总的像素数
	}
	averagegray /= calnum;
	//得到光线补偿的系数
	alpha = 255.0 / (float)averagegray-0.65
		
		
		;//对比度因子
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(alpha*dst.at<Vec3b>(i, j)[0] + beta);
			dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(alpha*dst.at<Vec3b>(i, j)[1] + beta);
			dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(alpha*dst.at<Vec3b>(i, j)[2] + beta);
		}
	}
	return  dst;
}

