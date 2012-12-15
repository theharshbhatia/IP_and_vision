/*

Aim: To take live input from a webcamera and display it on screen.
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;

 int main() {
 
	CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
	if ( !capture ) {
	fprintf( stderr, "ERROR: Capture not found \n" );
	getchar();
	return -1;
	}
   
	// window in which the captured images will be presented
	cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
	 
	// Repeating image frame extraction and display in while loop
	while ( 1 ) 
	{
		// extracting one frame from capture
		IplImage* frame = cvQueryFrame( capture );
		if ( !frame ) 
		{		
			fprintf( stderr, "ERROR: frame is null...\n" );
			getchar();
			break;
		}
		
		cvShowImage( "mywindow", frame );
		// Holing frame to kep live stream
		//Note: if frame is released, first captured frame from webcam will only be displayed. 
		if ( (cvWaitKey(10) & 255) == 27 ) break;
	}
	  
	//cleaning mess
	cvReleaseCapture( &capture );
	cvDestroyWindow( "mywindow" );
	return 0;
}