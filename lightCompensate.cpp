#include "lightCompensate.h"

/***���ݸ߹�����ֱ��ͼ������й��߲���***/
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
			//����Ҷ�ֵ
			int gray = (r * 299 + g * 587 + b * 114) / 1000;
			histogram[gray]++;
		}
	}
	int calnum = 0;
	int total = dst.rows * dst.cols;
	int num;
	//�����ѭ���õ�����ϵ��thresholdco���ٽ�Ҷȼ�
	for (int i = 0; i < 256; i++)
	{
		if ((float)calnum / total < thresholdco) //�õ�ǰ5%�ĸ������ء�
		{
			calnum += histogram[255 - i];//histogram�������ĳһ�Ҷ�ֵ�����ظ���,calnum�Ǳ߽�Ҷ�֮�ϵ�������
			num = i;
		}
		else
			break;
	}
	int averagegray = 0;
	calnum = 0;
	//�õ����������������ܵĻҶ�ֵ
	for (int i = 255; i >= 255 - num; i--)
	{
		averagegray += histogram[i] * i; //�ܵ����صĸ���*�Ҷ�ֵ
		calnum += histogram[i]; //�ܵ�������
	}
	averagegray /= calnum;
	//�õ����߲�����ϵ��
	alpha = 255.0 / (float)averagegray-0.65
		
		
		;//�Աȶ�����
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

