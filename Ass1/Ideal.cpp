
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;


static Mat CreateIdealLowFilter(Mat fourier, int D0)
{
	int length = fourier.rows;
	int height = fourier.cols;
	Point center = (length/2, height/2);


	Mat ans;
	return ans;
}

static Mat CreateIdealHighFilter(Mat fourier, int D0)
{
		Mat ans;
	return ans;
}