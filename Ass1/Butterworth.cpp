
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
//#include "Distance.cpp"

using namespace cv;


static double CalcButterworth(int i, int j, Point center, int D0, int n)
{
	//double distance = D(i,j,center);
	double distance = sqrt(pow(i-center.y,2)+pow(j-center.x,2));
	double ans = 1/(1+pow(distance/D0,2*n));
	return ans;
}

static Mat CreateButterworthLowFilter(Size size, Point center, int D0, int n)
{
	Mat ans = Mat(size, CV_32F);
	for (int i = 0; i < ans.rows; i++)
	{
		for (int j = 0; j < ans.cols; j++)
		{
			double value = CalcButterworth(i,j,center,D0,n); 
			ans.at<float>(i,j) = value;
		}
	}

	return ans;
	
}

static Mat CreateButterworthHighFilter(Size size, Point center, int D0, int n)
{
	Mat ans = CreateButterworthLowFilter(size, center, D0, n);
	for (int i = 0; i < ans.rows; i++)
	{
		for (int j = 0; j < ans.cols; j++)
		{
			ans.at<float>(i, j) = 1 - ans.at<float>(i, j);
		}
	}
	return ans;
}

