/*

Aim: Webcam live stream editor
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
using namespace cv;
using namespace std;

void help()
{
cout<<"This is a webcam live stream editor"
	<<"\t p : Take pic at current time"
	<<"\t g : convert into grayscale";
	
}

 int main() {
	 help();
 bool takepic = false;
    bool convertgrayscale = false;
	bool conedge = false;
	

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
		IplImage* original = cvQueryFrame( capture );
		if ( !original ) 
		{		
			fprintf( stderr, "ERROR: frame is null...\n" );
			getchar();
			break;
		}
		cvShowImage( "mywindow", original );
		IplImage* grayscale = cvCreateImage(cvSize(original->width, original->height), original->depth, 1); 
		
		
		if(takepic)
		{
			if(convertgrayscale==true)
			{cvSaveImage("grayimage.jpg",grayscale,0);}
			else cvSaveImage("originalimage.jpg",original,0);
		
			cout<<"print";
			takepic=false;
		}

		
		if(convertgrayscale)
		{
		 
            if (grayscale == NULL)
            {
                printf("!!! ERROR: cvCreateImage\n");
                continue;
            }
			//conversion into grayscale
            cvCvtColor(original, grayscale, CV_BGR2GRAY);
            cvShowImage("mywindow", grayscale);
           
		}

		
		char c = (char)waitKey(10);
        if( c == 27 )
            break;
        switch( c )
        {
        case 'p':
            takepic = true;
            break;
        case 'g':
			if(convertgrayscale==false)
			convertgrayscale=true;
			else convertgrayscale=false;
            break;
        case 'n':
            conedge =true;
            break;
        default:
            ;
        }


	}
	  
	//cleaning mess
	cvReleaseCapture( &capture );
	cvDestroyWindow( "mywindow" );
	return 0;
}