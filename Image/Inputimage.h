/*

Aim: To Load an image into program and display it in a window.
by: slashharsh
contact: slashharsh@hotmail.com

*/
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;

 int main() {
	//loading image present in folder of exe file named i.jpg
	IplImage *raw=cvLoadImage("i.jpg",1);

	//errpr catch if the image is not loaded
	if(raw==NULL ) 
		{
			puts("unable to load the frame");
			exit(0);
		}

	//Name of window to be displayed	
	cvNamedWindow("original",CV_WINDOW_AUTOSIZE);

	//Displaying image
	cvShowImage("original",raw);

	//waiting till User press esc key
	cvWaitKey(0);

	//Clearing mess
	cvDestroyWindow("original");

	return 0;
 }