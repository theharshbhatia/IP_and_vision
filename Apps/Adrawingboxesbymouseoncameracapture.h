/*

Aim: Drawing Boxes of blue color by mouse on first screen capture from webcam.
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
#include<Windows.h> //don't forget to include this header file
using namespace cv;
using namespace std;


//declaration of functions and variables used in code.
void mouse_callback(int event, int x, int y, int flags, void* param );
CvRect box;
bool drawing_box = false;

void draw( IplImage* img, CvRect rect ) 
{
	cvRectangle (
	img,
	cvPoint(box.x,box.y),
	cvPoint(box.x+box.width,box.y+box.height),
	//blue color
	cvScalar(0xff,0x00,0x00) 
	);
}


int main() 
{
	box = cvRect(-1,-1,0,0);
	CvCapture *capture = NULL;
		capture = cvCaptureFromCAM(0);
		IplImage* image = cvQueryFrame(capture);

	//clonning image for operation
	IplImage* temp = cvCloneImage( image );
	cvNamedWindow( "Box Example");

	cvSetMouseCallback(
		"Box Example",
		mouse_callback,
		(void*) image
		);


	while( 1 ) 
	{
		cvCopyImage( image, temp );
		if( drawing_box ) draw( temp, box );
		cvShowImage( "Box Example", temp );
		if( cvWaitKey( 15 )==27 ) break;
	}
	//cleaning mess
	cvReleaseImage( &image );
	cvReleaseImage( &temp );
	cvDestroyWindow( "Box Example" );
}


void mouse_callback(int event, int x, int y, int flags, void* param)
 {
	IplImage* image = (IplImage*) param;
	switch( event ) 
	{
		case CV_EVENT_MOUSEMOVE: 
		{
			if( drawing_box ) 
			{
				box.width = x-box.x;
				box.height = y-box.y;
			}
		}
		break;
		
		case CV_EVENT_LBUTTONDOWN: 
		{
			drawing_box = true;
			box = cvRect(x, y, 0, 0);
		}
		break;
		
		case CV_EVENT_LBUTTONUP: 
		{
		drawing_box = false;
			if(box.width<0) 
			{
				box.x+=box.width;
				box.width *=-1;
			}
			if(box.height<0) 
			{
				box.y+=box.height;
				box.height*=-1;
			}
			
		draw(image, box);
		}
		break;
	}
}