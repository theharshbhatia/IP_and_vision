/*

Aim: To display contours and controlling countour constant with tracbar
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;


IplImage* original = NULL;
IplImage* grayscale = NULL;
int g_thresh = 100; // value of contours effecting
CvMemStorage* memstorage = NULL;


void on_trackbar(int) {
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
	//grayscale conversion
	cvCvtColor( original, grayscale, CV_BGR2GRAY );
	//threshold conversion
	cvThreshold( grayscale, grayscale, g_thresh, 255, CV_THRESH_BINARY );
	cvFindContours( grayscale, memstorage, &contours );
	cvZero( grayscale );
	
	if( contours )
		cvDrawContours(
		grayscale,
		contours,
		cvScalarAll(255),
		cvScalarAll(255),
		100
		);
	
	cvShowImage( "Contours", grayscale );
}

int main( int argc, char** argv )
{
	original = cvLoadImage("i.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow( "Contours", 1 );
	
	//creating trackbar for threshold value of contours
	cvCreateTrackbar(
	"Threshold",
	"Contours",
	&g_thresh,
	255,
	on_trackbar
	);

	on_trackbar(0);
	cvWaitKey();
	//cleaning mess
	cvDestroyWindow("Contours");
	return 0;
}