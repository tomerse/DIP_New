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

#include "GUI.h"
using namespace Ass1;
using namespace cv;
using namespace std;
using namespace System::Drawing::Imaging;
using namespace System::Drawing;





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
	
	//win->pb_org->ImageLocation=(System::String^)argv[1];
	win->pb_org->ImageLocation="C:\\Users\\Tomer\\Desktop\\New folder\\lena.jpg";
	win->tb_d0->Value = (win->tb_d0->Maximum -  win->tb_d0->Minimum)/2;
	win->tb_n->Value = (win->tb_n->Maximum -  win->tb_n->Minimum)/2;

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
	
	WidthPadded=org.cols*2;
	HeightPadded=org.rows*2;
	
	int M = getOptimalDFTSize( org.rows );

	Mat fourier = CreateFourierImg(org);

	int height = fourier.rows;
	int width = fourier.cols;
	cv::Size size = cv::Size(width, height);

	Mat filtered = CreateFilterImg(size, filter, settings, d0, n);

	Mat fourierInverse =  CreateFourierInverseImg(fourier,filtered);
	imshow("Inverse Transform Image"       , fourierInverse   ); 

}

Mat GUI::getOrgImage()
{
	Mat org;
	System::String ^path = pb_org->ImageLocation;
	std::string unmanagedPath = msclr::interop::marshal_as<std::string>(path);
	org = imread(unmanagedPath, CV_LOAD_IMAGE_GRAYSCALE);  

    if(! org.data )                              
    {
		throw exception("Could not open or find the image");
    }

	return org;
}

Mat GUI::CreateFourierImg(Mat org)
{
	
	Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( org.rows );
    int n = getOptimalDFTSize( org.cols ); // on the border add zero values
	copyMakeBorder(org, padded, 0, m - org.rows, 0, n - org.cols, BORDER_CONSTANT, Scalar::all(0));
    //copyMakeBorder(org, padded, 0, HeightPadded - org.rows, 0, WidthPadded - org.cols, BORDER_CONSTANT, Scalar::all(0));

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


	imshow("Fourier Transform", magI);
	return complexI;
	//return magI;

}

Mat GUI::CreateFilterImg(cv::Size size, int filter, int settings, int d0, int n)
{
	Mat filterImg;
	
	cv::Point center = cv::Point(size.width/2, size.height/2);

	if (filter == 1) //low
	{
		if (settings == 1) //low-ideal
		{
			filterImg = CreateIdealLowFilter(size, center, d0);
		}
		else
			if (settings == 2) //low-butterworth
			{
				filterImg = CreateButterworthLowFilter(size, center, d0, n);
			}
			else
				if (settings == 3) //low-gaussian
				{
					filterImg = CreateGaussianLowFilter(size, center, d0);
				}
	}
	else
		if (filter == 2) //high
		{
			if (settings == 1) //high-ideal
			{
				filterImg = CreateIdealHighFilter(size, center, d0);
			}
			else
				if (settings == 2) //high-butterworth
				{
					filterImg = CreateButterworthHighFilter(size, center, d0, n);
				}
				else
					if (settings == 3) //high-gaussian
					{
						filterImg = CreateGaussianHighFilter(size, center, d0);
					}
		}

		
		imshow("Filter", filterImg);

		normalize(filterImg, filterImg, 0, 1, CV_MINMAX);
		Mat padded;
		copyMakeBorder(filterImg, padded, 0, size.height - filterImg.rows, 0, size.width - filterImg.cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		Mat complexImg;
		merge(planes, 2, complexImg);

		return complexImg;

}


Mat GUI::CreateFourierInverseImg(Mat fourier, Mat filtered)
{
		Mat res;
		Mat img = getOrgImage();

		cv::mulSpectrums(fourier,filtered,res,DFT_COMPLEX_OUTPUT);		
		idft(res,res,DFT_COMPLEX_OUTPUT,img.rows);

		Mat padded;
		copyMakeBorder(img, padded, 0, img.rows, 0, img.cols, BORDER_CONSTANT, Scalar::all(0));
		Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
		split(res, planes);
		magnitude(planes[0], planes[1], planes[0]);
		Mat mag = planes[0];
		mag += Scalar::all(1);
		log(mag, mag);

		// crop the spectrum, if it has an odd number of rows or columns
		mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

		int cx = mag.cols/2;
		int cy = mag.rows/2;

		normalize(mag, mag, 1, 0, CV_MINMAX);

		//cv::Mat croped = mag(cv::Rect(cx, cy, img.cols,img.rows));
		//cv::threshold(croped , croped , 0.56, 1, cv::THRESH_BINARY);

		//imshow("fftPLUShpf", mag);
		//imshow("cropedBinary", croped);


		return mag;
}




