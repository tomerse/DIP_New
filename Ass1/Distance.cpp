#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <math.h>
using namespace cv;



static int D(int i, int j, Point p)
{
	return sqrt(pow(i-p.x,2)+pow(j-p.y,2));
}