/*

Aim: Thresholding Green color from an image
by: slashharsh
contact: slashharsh@hotmail.com

*/
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;

 int main() {
	//loading image present in folder of exe file named i.jpg
	IplImage *original=cvLoadImage("F:\\colortiles.jpg",1);

	//error catch if the image is not loaded
	if(original==NULL ) 
		{
			puts("unable to load the frame");
			exit(0);
		}

	//Name of window to be displayed	
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Green detect",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Green extract",CV_WINDOW_AUTOSIZE);
	//Displaying image
	cvShowImage("original",original);
	IplImage *redsplit = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	IplImage *bluesplit = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	IplImage *greensplit = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	
	IplImage *greenextract = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	//splitting image into 3 different filters
	cvSplit(original,bluesplit,greensplit,redsplit,0);

	cvAdd(redsplit,bluesplit,bluesplit);
	cvSub(greensplit,bluesplit,greensplit);
	
	//thresholding highest value with binary thresh
	cvThreshold(greensplit,greenextract,20,255,CV_THRESH_BINARY);
	cvShowImage("Green detect",greensplit);
	cvShowImage("Green extract",greenextract);

	//waiting till User press esc key
	cvWaitKey(0);
	//Clearing mess
	cvDestroyWindow("original");
	cvDestroyWindow("Green detect");
	cvDestroyWindow("Green extract");

	return 0;
 }