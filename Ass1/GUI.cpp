#include <opencv2\opencv.hpp>
#include <cstdio>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include "ideal.cpp"
#include "Gaussian.cpp"
#include "Butterworth.cpp"
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

	const char* filename = argv[1];
	*/

	
	GUI^ win = gcnew GUI();
	/*System::IntPtr ptr(image.ptr());
	win->pb_org->Image->FromHbitmap(ptr);*/
	//DrawCVImage(win->pb_org,hBitmap);
	
	//win->pb_org->ImageLocation=(System::String^)argv[1];
	win->pb_org->ImageLocation="C:\\Users\\Tomer\\Desktop\\New folder\\pic.jpg";
	Mat org = win->getOrgImage();
	imshow("Input Image"       , org   );
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
	Mat org = getOrgImage();
	//imshow("Input Image"       , org   );    
    
	Mat fourier = CreateFourierImg(org);
	imshow("spectrum magnitude", fourier);

	Mat filtered = CreateFilterImg(fourier, filter, settings, d0, n);
	imshow("Filtered Image"       , filtered   ); 

	Mat fourierInverse =  CreateFourierInverseImg(filtered);
	imshow("Fourier Inverse Image"       , fourierInverse   ); 
}

Mat GUI::getOrgImage()
{
	Mat org;
	System::String ^path = pb_org->ImageLocation;
	std::string unmanagedPath = msclr::interop::marshal_as<std::string>(path);
	org = imread(unmanagedPath, CV_LOAD_IMAGE_GRAYSCALE);  

	/*cvtColor(image, image, CV_BGRA2RGBA);
	HBITMAP  hBitmap = CreateBitmap(image.cols, image.rows, 1, 32, image.data);*/

    if(! org.data )                              
    {
		throw exception("Could not open or find the image");
    }
	   /*
	namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", org ); // Show our image inside it.
	*/
	return org;
}

Mat GUI::CreateFourierImg(Mat org)
{
	Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( org.rows );
    int n = getOptimalDFTSize( org.cols ); // on the border add zero values
    copyMakeBorder(org, padded, 0, m - org.rows, 0, n - org.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    dft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    //imshow("Input Image"       , org   );    // Show the result
    //imshow("spectrum magnitude", magI);
    //waitKey();

	return magI;
	
}

Mat GUI::CreateFilterImg(const Mat fourier, int filter, int settings, int d0, int n)
{
	Mat filterImg;
	if (filter == 1) //low
	{
		if (settings == 1) //low-ideal
		{
			filterImg = CreateIdealLowFilter(fourier, d0);
		}
		else
			if (settings == 2) //low-butterworth
			{
				filterImg = CreateButterworthLowFilter(fourier, d0, n);
			}
			else
				if (settings == 3) //low-gaussian
				{
					filterImg = CreateGaussianLowFilter(fourier, d0);
				}
	}
	else
		if (filter == 2) //high
		{
			if (settings == 1) //high-ideal
			{
				filterImg = CreateIdealHighFilter(fourier, d0);
			}
			else
				if (settings == 2) //high-butterworth
				{
					filterImg = CreateButterworthHighFilter(fourier, d0, n);
				}
				else
					if (settings == 3) //high-gaussian
					{
						filterImg = CreateGaussianHighFilter(fourier, d0);
					}
		}



	int height = fourier.rows;
	int length = fourier.cols;

	Mat *ans = new Mat(height,length,CV_8UC1);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			
				ans->at<uchar>(i,j) = fourier.at<uchar>(i,j)*filterImg.at<uchar>(i,j);

		}
	}




		return *ans;

}

Mat GUI::CreateFourierInverseImg(Mat filtered)
{
	Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( filtered.rows );
    int n = getOptimalDFTSize( filtered.cols ); // on the border add zero values
    copyMakeBorder(filtered, padded, 0, m - filtered.rows, 0, n - filtered.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

    idft(complexI, complexI);            // this way the result may fit in the source matrix

    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;

    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).

    //imshow("Input Image"       , org   );    // Show the result
    //imshow("Inverse Fourier", magI);
    //waitKey();

	return magI;
}




