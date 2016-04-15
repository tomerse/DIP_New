
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
//#include "Distance.cpp"
using namespace cv;


static Mat CreateGaussianLowFilter(Mat fourier, int D0)
{
	int height = fourier.rows;
	int length = fourier.cols;
	Point center = Point(length/2, height/2);

	Mat *ans = new Mat(height,length,CV_8UC1);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			//double distance = D(i,j,center);	
			double distance = sqrt(pow(i-center.y,2)+pow(j-center.x,2));
			double exponent = ((-1)*pow(distance,2))/(2*pow(D0,2));
			ans->at<uchar>(i,j) = exp(exponent);
		}
	}

	 imshow("gaussian low filter"       , *ans   );    // Show the result
   

	return *ans;
	/*Mat ans;
	return ans;*/
}

static Mat CreateGaussianHighFilter(Mat fourier, int D0)
{
		Mat ans;
	return ans;
}