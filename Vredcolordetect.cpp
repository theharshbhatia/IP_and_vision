/*

Aim: red color detection and drawing on live stream from webcam
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

 
 IplImage* ExtractThresholdedImage(IplImage* img)
{	
	IplImage *redsplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *bluesplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *greensplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	
	IplImage *redthreshold = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	//splitting image into 3 different filters
	cvSplit(img,bluesplit,greensplit,redsplit,0);

	cvAdd(bluesplit,greensplit,greensplit);
	cvSub(redsplit,greensplit,redsplit);
	//thresholding highest value with binary thresh
	cvThreshold(redsplit,redthreshold,0,255,CV_THRESH_BINARY);
	return redthreshold;
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

	
    cvNamedWindow("Original");
			
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
		IplImage* redextract = ExtractThresholdedImage(original);
		//removing background impurities
		cvErode(redextract,redextract,0,5);
			

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
	//cvShowImage( "Red Extract", redextract );
	if(contours){
		double area=cvContourArea(contours,CV_WHOLE_SEQ);
		
		CvRect rect= cvBoundingRect(contours,0);
		int cent= rect.x+(rect.width/2);
		int cent1= rect.y+(rect.height/2);
		cout << area<<"\n";
		cvRectangle(original,cvPoint(rect.x,rect.y),cvPoint(rect.x+rect.width,rect.y+rect.height),CV_RGB(0,0,255),2,1,0);
		
	}
	cvShowImage( "Original", original );
	// Release thresholded image
	cvReleaseImage(&redextract);
	cvClearMemStorage(memstorage);

	////////////////////////////////
		int c = cvWaitKey(10);
		if(c!=-1)
		{
			break;
		}
		
    }

	//cleaning mess
	cvReleaseCapture(&capture);
    
	return 0;
}