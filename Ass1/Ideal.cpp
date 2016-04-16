

#include <windows.h>
#include <sstream>
#include <iostream>

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Distance.cpp"
using namespace cv;

	//MessageBox( NULL, "shar", "", MB_OK );

static Mat CreateIdealLowFilter(Mat fourier, int D0)
{
	int height = fourier.rows;
	int length = fourier.cols;
	Point center = Point(length/2, height/2);

	D0=10;
	Mat *ans = new Mat(height,length,CV_32F);
	for (int i = 0; i < ans->rows; i++)
	{
		for (int j = 0; j < ans->cols; j++)
		{
			if (D(i,j,center) > D0)
				ans->at<float>(i,j) = 0;
			else
				ans->at<float>(i,j) = 1;
		}
	}

	imshow("ideal low filter"       , *ans   );    // Show the result  

	return *ans;
}

static Mat CreateIdealHighFilter(Mat fourier, int D0)
{
	int height = fourier.rows;
	int length = fourier.cols;
	Point center = Point(length/2, height/2);

	D0=10;
	Mat *ans = new Mat(height,length,CV_32F);
	for (int i = 0; i < ans->rows; i++)
	{
		for (int j = 0; j < ans->cols; j++)
		{
			if (D(i,j,center) > D0)
				ans->at<float>(i,j) = 1;
			else
				ans->at<float>(i,j) = 0;
		}
	}

	 imshow("ideal high filter"       , *ans   );    // Show the result
   

	return *ans;
}