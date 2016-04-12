#include <opencv2\opencv.hpp>
#include <cstdio>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
//#include <opencv2\core\mat.hpp>

#include "GUI.h"
using namespace Ass1;
using namespace cv;
using namespace std;
	using namespace System::Drawing::Imaging;
	using namespace System::Drawing;




void DrawCVImage(System::Windows::Forms::Control^ control, cv::Mat& colorImage)
{
    System::Drawing::Graphics^ graphics = control->CreateGraphics();
    System::IntPtr ptr(colorImage.ptr());
    System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(colorImage.cols, colorImage.rows, colorImage.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
    System::Drawing::RectangleF rect(0, 0, control->Width, control->Height);
    graphics->DrawImage(b, rect);
}



int main(int argc, char **argv)
{
	/*
	if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }
	*/

	
	GUI^ win = gcnew GUI();
	/*System::IntPtr ptr(image.ptr());
	win->pb_org->Image->FromHbitmap(ptr);*/
	//DrawCVImage(win->pb_org,hBitmap);
	
	win->pb_org->ImageLocation="C:\\Users\\Tomer\\Desktop\\New folder\\pic.jpg";
	win->ShowDialog();
}






void GUI::ApplyChanges()
{
	int filter = getFilter();
	int settings = getSettings();
	int d0 = tb_d0->Value;
	int n = tb_n->Value;
	createImages(filter, settings, d0, n);

}

int GUI::getFilter()
{
	if (rb_low->Checked) 
		return 1;
	else
		return 2;
}

int GUI::getSettings()
{
	if (rb_ideal->Checked) 
		return 1;
	else
		if (rb_butter->Checked) 
			return 2;
		else
			return 3;
}

void GUI::createImages(int filter, int settings, int d0, int n)
{
	Mat& org = getOrgImage();


	CreateFourierImg(org, settings, d0, n);
}

Mat& GUI::getOrgImage()
{
	Mat org;
	System::String ^path = pb_org->ImageLocation;
	std::string unmanagedPath = msclr::interop::marshal_as<std::string>(path);
	org = imread(unmanagedPath, CV_LOAD_IMAGE_COLOR);  

	/*cvtColor(image, image, CV_BGRA2RGBA);
	HBITMAP  hBitmap = CreateBitmap(image.cols, image.rows, 1, 32, image.data);*/

    if(! org.data )                              
    {
		throw exception("Could not open or find the image");
    }
	   
	namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", org ); // Show our image inside it.
	return org;
}

void GUI::CreateFourierImg(Mat& org, int settings, int d0, int n)
{

	
}
void GUI::CreateFilterImg()
{

}
void GUI::CreateFourierInverseImg()
{
}




