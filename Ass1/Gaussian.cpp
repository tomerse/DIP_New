
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
//#include "Distance.cpp"
using namespace cv;


static double CalcGaussian(int i, int j, Point center, int D0)
{
	//double distance = D(i,j,center);
	double distance = sqrt(pow(i-center.y,2)+pow(j-center.x,2));
	double exponent = ((-1)*pow(distance,2))/(2*pow(D0,2));
	double ans = exp(exponent);
	return ans;
}

static Mat CreateGaussianLowFilter(Size size, Point center, int D0)
{
	Mat ans(size, CV_32F);
	for (int i = 0; i < ans.rows; i++)
	{
		for (int j = 0; j < ans.cols; j++)
		{	
			double value = CalcGaussian(i,j,center,D0);
			ans.at<float>(i,j) = value;
		}
	}

	return ans;

}

static Mat CreateGaussianHighFilter(Size size, Point center, int D0)
{
		Mat ans;
	return ans;
}
