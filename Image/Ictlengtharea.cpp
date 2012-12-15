/*

Aim: Drawing countors on red colors in image
by: slashharsh
contact: slashharsh@hotmail.com

*/
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;
using namespace std;


IplImage* original = NULL;
IplImage* grayscale = NULL;
int g_thresh = 100; // value of contours effecting
CvMemStorage* memstorage = NULL;


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
	//cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Red detect",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Red extract",CV_WINDOW_AUTOSIZE);
	//Displaying image
	//cvShowImage("original",original);
	IplImage *redsplit = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	IplImage *bluesplit = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	IplImage *greensplit = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	
	IplImage *redextract = cvCreateImage(cvGetSize(original),IPL_DEPTH_8U,1);
	//splitting image into 3 different filters
	cvSplit(original,bluesplit,greensplit,redsplit,0);
	cvAdd(bluesplit,greensplit,greensplit);
	cvSub(redsplit,greensplit,redsplit);
	
	//thresholding highest value with binary thresh
	cvThreshold(redsplit,redextract,20,255,CV_THRESH_BINARY);
	
	//cvShowImage("Red detect",redsplit);
	cvShowImage("Red extract",redextract);


	if( memstorage==NULL )
	{
		grayscale = cvCreateImage( cvGetSize(original), 8, 1 );
		memstorage = cvCreateMemStorage(0);
	} 
	else 
	{
		cvClearMemStorage( memstorage );
	}
	
	CvSeq* contours = 0;
	cvFindContours( redextract, memstorage, &contours );
	cvZero( redextract );
	
	if( contours )
		cvDrawContours(
		original,
		contours,
		cvScalarAll(000),
		cvScalarAll(255),
		100
		);
	
	double Area=cvContourArea(contours,CV_WHOLE_SEQ);
	double length=cvArcLength(contours,CV_WHOLE_SEQ,1);
		cvShowImage( "Red extract", original );

		cout <<"Measurement of contours\n"
			<<"area:" << Area<<"\n"
			<< "length:"<<length;

	//waiting till User press esc key
	cvWaitKey(0);
	//Clearing mess
	cvDestroyWindow("original");
	cvDestroyWindow("Red detect");

	return 0;
 }