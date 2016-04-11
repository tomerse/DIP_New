#include <opencv2\opencv.hpp>
#include <cstdio>


#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
//#include <opencv2\core\mat.hpp>

#include "GUI.h"
using namespace Ass1;
using namespace cv;
using namespace std;
	using namespace System::Drawing::Imaging;



void Init(GUI^ win)
{
	win->pb_org->ImageLocation="C:\\Users\\Tomer\\Desktop\\New folder\\pic.jpg";

}

int main(int argc, char **argv)
{
	/*
	if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }*/

   /* Mat image;
    image = imread("C:\\Users\\Tomer\\Desktop\\New folder\\pic.jpg", CV_LOAD_IMAGE_COLOR);   

    if(! image.data )                              
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }*/

	GUI^ win = gcnew GUI(); 
	Init(win);
	win->ShowDialog();
}



