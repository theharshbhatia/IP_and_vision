/*

Aim: to convert an image into grayscale
by: slashharsh
contact: slashharsh@hotmail.com

*/
#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;


 int main()
{
    int camera_index = 0;
    IplImage *original = NULL;
    int exit_key_press = 0;
	int Canny_value=10;//intiating threshold
    CvCapture *capture = NULL;
    capture = cvCaptureFromCAM(camera_index);
    
	if (!capture)
    {
        printf("ERROR: no capture\n");
        return -1;
    }
	cvNamedWindow("RAW", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Grayscale", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Canny", CV_WINDOW_AUTOSIZE);
	
	//loop
    while (exit_key_press != 27)
    {
        // frame from capture
        original = cvQueryFrame(capture);
        if (original == NULL)
        {
            printf("!!! ERROR: \n");
            break;
        }
        else
        {
			//working on image frame
            IplImage* grayscale = cvCreateImage(cvSize(original->width, original->height), original->depth, 1);  
			IplImage* Canny = cvCreateImage(cvSize((grayscale->width), grayscale->height), IPL_DEPTH_8U, 1); 
			//trackbar creation 
			cvCreateTrackbar("Canny Value", "Canny", &Canny_value, 100);
						
			if (grayscale == NULL)
            {
                printf("!!! ERROR: cvCreateImage\n");
                continue;
            }
			//conversion section
            cvCvtColor(original, grayscale, CV_BGR2GRAY);
            cvShowImage("Grayscale", grayscale);
            cvShowImage("RAW", original);
			cvCanny(grayscale, Canny, Canny_value, Canny_value*3, 3);
			cvShowImage("Canny",Canny);
			cvReleaseImage(&grayscale);
		}

            exit_key_press = cvWaitKey(1);
    }
	
	//cleaning mess
    cvDestroyWindow("Grayscale video");
	cvDestroyWindow("RAW");
    cvReleaseCapture(&capture);
    return 0;
}
 