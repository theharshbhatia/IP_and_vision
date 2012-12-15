/*

Aim: Thresholding live stream by green color.
by: slashharsh
contact: slashharsh@hotmail.com
Note :green detection doesnt work fine with this thresholding technique
*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  

using namespace cv;


 
 IplImage* ExtractThresholdedImage(IplImage* img)
{	
	IplImage *redsplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *bluesplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *greensplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	
	IplImage *greenextract = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	//splitting image into 3 different filters
	cvSplit(img,bluesplit,greensplit,redsplit,0);

	cvAdd(redsplit,bluesplit,bluesplit);
	cvSub(greensplit,bluesplit,greensplit);
	
	//thresholding highest value with binary thresh
	cvThreshold(greensplit,greenextract,0,255,CV_THRESH_BINARY);
	return greenextract;
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