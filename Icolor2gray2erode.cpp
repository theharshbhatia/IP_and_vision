/*

Aim: to convert an image into grayscale
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;


int main()
{
	// Initiating an image to load from folder of project exe.
	IplImage *Original=cvLoadImage("i.jpg",1);
	//creating an image of same size as loaded image
	IplImage *Grayscale = cvCreateImage( cvSize(Original->width, Original->height), Original->depth, 1 );
	//if image is not present or not loaded into program
	if(Original==NULL ) 
	{
		puts("ERROR: Can't upload frame");
		exit(0);
	}
	//printing on command window if image is loaded
	printf("frame loaded");
	//converting it into grayscale image
	cvCvtColor(Original, Grayscale, CV_RGB2GRAY);
	//creating windows and displaying both images in seperate windows.
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Grayscale",CV_WINDOW_AUTOSIZE);
	
	// Irode Function
	IplImage *erode=cvCreateImage(cvSize(Original->width,Original->height), IPL_DEPTH_8U,1);
	cvErode(Grayscale,erode,0,1); // the last param= iterations
	cvNamedWindow("erode",CV_WINDOW_AUTOSIZE);
	cvShowImage("erode",erode);
	cvShowImage("original",Original);
	cvShowImage("Grayscale",Grayscale);
	cvWaitKey(0);
	//cleaning mess
	cvDestroyWindow("original");
	cvDestroyWindow("Grayscale");
	cvDestroyWindow("dilate");
	return 0;
}
