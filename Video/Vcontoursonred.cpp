/*

Aim: Thresholding live stream by red color.
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

 
 IplImage* ExtractThresholdedImage(IplImage* img)
{	
	IplImage *redsplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *bluesplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *greensplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	
	IplImage *redextract = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	//splitting image into 3 different filters
	cvSplit(img,bluesplit,greensplit,redsplit,0);

	cvAdd(bluesplit,greensplit,greensplit);
	cvSub(redsplit,greensplit,redsplit);
	//thresholding highest value with binary thresh
	cvThreshold(redsplit,redextract,10,255,CV_THRESH_BINARY);
	return redextract;
}

int main()
{
	//capture a frame
	CvCapture* capture = 0;
	capture = cvCaptureFromCAM(0);	
	//error in capture
	if(!capture)
    {
        printf("Could not initialize capturing...\n");
        return -1;
    }

	// The two windows we'll be using
    cvNamedWindow("Original");
	cvNamedWindow("Red Extract");

		
	// loop
	while(true)
    {
		// hold a frame captured 
		IplImage* original = 0;
		original = cvQueryFrame(capture);

		//error in frame grabbing
        if(!original)
            break;

		// fucntion call for threshold image by color
		IplImage* redthreshold = ExtractThresholdedImage(original);
		
		cvShowImage("Red Extract", redthreshold);
		cvShowImage("Original", original);

		

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
	cvFindContours( redthreshold, memstorage, &contours );
	cvZero( redthreshold );
	
	if( contours )
		cvDrawContours(
		redthreshold,
		contours,
		cvScalarAll(255),
		cvScalarAll(255),
		100
		);
	
	cvShowImage( "Red extract", redthreshold );
		
		int c = cvWaitKey(10);
		if(c!=-1)
		{
			break;
		}
		
		
		
		// Release thresholded image
		cvReleaseImage(&redthreshold);

		
    }

	//cleaning mess
	cvReleaseCapture(&capture);
    
	return 0;
}