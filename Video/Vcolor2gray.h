/*

Aim: To convert live video stream from webcam into one channel grayscale vedio.
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  

using namespace cv;


 int main() {
	int camera_index = 0;
    IplImage *original = NULL;
    int exit_key_press = 0;

    CvCapture *capture = NULL;
    capture = cvCaptureFromCAM(camera_index);
    
	if (!capture)
    {
        printf("!!! ERROR: cvCaptureFromCAM\n");
        return -1;
    }
	cvNamedWindow("RAW", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Grayscale", CV_WINDOW_AUTOSIZE);

    while (exit_key_press != 27)
    {
        // Capture a frame 
        original = cvQueryFrame(capture);
        if (original == NULL)
        {
            printf("!!! ERROR: cvQueryFrame\n");
            break;
        }
        else
        {
			//working on image frame
            IplImage* grayscale = cvCreateImage(cvSize(original->width, original->height), original->depth, 1);  
            if (grayscale == NULL)
            {
                printf("!!! ERROR: cvCreateImage\n");
                continue;
            }
			//conversion into grayscale
            cvCvtColor(original, grayscale, CV_BGR2GRAY);
            cvShowImage("Grayscale", grayscale);
            cvReleaseImage(&grayscale);
			cvShowImage("RAW", original);
		}

            exit_key_press = cvWaitKey(1);
    }
	
	//cleaning mess
    cvDestroyWindow("Grayscale video");
    cvReleaseCapture(&capture);

    return 0;
 }