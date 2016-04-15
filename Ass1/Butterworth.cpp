
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
//#include "Distance.cpp"

using namespace cv;


static Mat CreateButterworthLowFilter(Mat fourier, int D0, int n)
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
			ans->at<uchar>(i,j) = 1/(1+pow(distance/D0,2*n));
		}
	}

	 imshow("butterworth low filter"       , *ans   );    // Show the result
   

	return *ans;
	
	
	/*Mat ans;
	return ans;*/
}

static Mat CreateButterworthHighFilter(Mat fourier, int D0, int n)
{

	Mat ans;
	return ans;
}