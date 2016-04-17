
#include <windows.h>
#include <sstream>
#include <iostream>

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Distance.cpp"
using namespace cv;


static Mat CreateIdealLowFilter(Size size, Point center, int D0)
{
	Mat ans(size, CV_32F);

	for (int i = 0; i < ans.rows; i++)
	{
		for (int j = 0; j < ans.cols; j++)
		{
			if (D(i,j,center) > D0)
				ans.at<float>(i,j) = 0;
			else
				ans.at<float>(i,j) = 1;
		}
	}

	return ans;
}

static Mat CreateIdealHighFilter(Size size, Point center, int D0)
{
	Mat ans(size, CV_32F);

	for (int i = 0; i < ans.rows; i++)
	{
		for (int j = 0; j < ans.cols; j++)
		{
			if (D(i,j,center) > D0)
				ans.at<float>(i,j) = 1;
			else
				ans.at<float>(i,j) = 0;
		}
	}

	return ans;
}