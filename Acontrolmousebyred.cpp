/*

Aim: controlling mouse with red color
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
#include <stdio.h>
#include <windows.h>



using namespace cv;
using namespace std;

IplImage* original = NULL;
IplImage* grayscale = NULL;
int g_thresh = 100; // value of contours effecting

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
 
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
	HWND myWindow;
AllocConsole();

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
			
		
	
	
		CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(redextract, moments, 1);

		double moment10 = cvGetSpatialMoment(moments, 1, 0);
		double moment01 = cvGetSpatialMoment(moments, 0, 1);
		double area1 = cvGetCentralMoment(moments, 0, 0);

		// Holding the last and current ball positions
		static int posX = 0;
		static int posY = 0;

		int lastX = posX;
		int lastY = posY;

		posX = moment10/area1;
		posY = moment01/area1;

		int changex=lastX-posX;
		int changey=lastY-posY;
		// Print it out for debugging purposes
		
		
		if(changex>0)
		{
			//cout<<"movement";
			mouse_event(MOUSEEVENTF_MOVE,changex*2,0,0,0);//(left,down);
			
		}
		if(changex<0)
		{
			//cout<<"movement";
			mouse_event(MOUSEEVENTF_MOVE,changex*2,0,0,0);//(left,down);
			
		}
		if(changey<0)
		{
			//cout<<"movement";
			mouse_event(MOUSEEVENTF_MOVE,0,-changey*2,0,0);//(left,down);
			
		}
		if(changey>0)
		{
			//cout<<"movement";
			mouse_event(MOUSEEVENTF_MOVE,0,-changey*2,0,0);//(left,down);
			
		}
		delete moments;
	
	cvShowImage( "Original", original );
	// Release thresholded image
	cvReleaseImage(&redextract);
	//cvClearMemStorage(memstorage);
	//cvReleaseImage(&original);
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