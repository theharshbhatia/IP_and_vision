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

IplImage* ETBImage(IplImage* img)
{	
	IplImage *redsplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *bluesplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	IplImage *greensplit = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	
	IplImage *blueextract = cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	//splitting image into 3 different filters
	cvSplit(img,bluesplit,greensplit,redsplit,0);

	cvAdd(redsplit,greensplit,greensplit);
	cvSub(bluesplit,greensplit,bluesplit);
	
	//thresholding highest value with binary thresh
	cvThreshold(bluesplit,blueextract,20,255,CV_THRESH_BINARY);
	return blueextract;
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
		IplImage* blueextract = ETBImage(original);
		//removing background impurities
		cvErode(redextract,redextract,0,5);
		cvErode(blueextract,blueextract,0,5);
		//////////////////////	
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
		
	////////////////
		CvMoments *moments1 = (CvMoments*)malloc(sizeof(CvMoments));
		cvMoments(blueextract, moments1, 1);

		double moment10b = cvGetSpatialMoment(moments1, 1, 0);
		double moment01b = cvGetSpatialMoment(moments1, 0, 1);
		double area1B = cvGetCentralMoment(moments1, 0, 0);

		// Holding the last and current ball positions
		static int posBX = 0;
		static int posBY = 0;

		int lastBX = posBX;
		int lastBY = posBY;

		posBX = moment10b/area1B;
		posBY = moment01b/area1B;

		int changebx=lastBX-posBX;
		int changeby=lastBY-posBY;
		// Print it out for debugging purposes
		
		if(posBX-posX<140 && posX!=2147483648)
		{
		cout<<"collide";
		mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
		Sleep(10);
		mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
		}
		
		//cout<<posBX-posX<<"\n";


		delete moments1;
		delete moments;
		cvShowImage( "Original", original );
		// Release thresholded image
		cvReleaseImage(&redextract);
		cvReleaseImage(&blueextract);
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
    cvDestroyWindow("original");
	return 0;
}