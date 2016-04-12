

#include <windows.h>
#include <sstream>
#include <iostream>

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Distance.cpp"
using namespace cv;


static Mat CreateIdealLowFilter(Mat fourier, int D0)
{
	//MessageBox( NULL, "shar", "", MB_OK );
	int length = fourier.rows;
	int height = fourier.cols;
	Point center = (length/2, height/2);

	D0=100;
	Mat *ans = new Mat(length,height,CV_8UC1);
	/*std::string str = "center is x: %d, y: %d", center.x,center.y; 
	MessageBox( NULL, (LPCSTR)str, "", MB_OK );*/
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Point cur = (i,j);
			if (D(i,j,center) > D0)
				ans->at<uchar>(i,j) = 255;
			else
				ans->at<uchar>(i,j) = 255;
		}
	}

	 imshow("Filtered Image"       , *ans   );    // Show the result
   

	return *ans;
}

static Mat CreateIdealHighFilter(Mat fourier, int D0)
{
		Mat ans;
	return ans;
}