#include <opencv\cv.h>
#include <opencv\highgui.h>
int main()
{
    //Window 
    cvNamedWindow("Drawing",CV_WINDOW_AUTOSIZE);
    //Image loading
    IplImage* original=cvLoadImage("i.jpg");
    //font initialize
    CvFont font;
    cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 3, CV_AA);
    
	//Drawing different Elements
    cvLine(original,cvPoint(50,50),cvPoint(50,200),CV_RGB(255,0,0),10,8);
    cvRectangle(original,cvPoint(100,50),cvPoint(200,200),CV_RGB(255,0,0),5,8);
   	cvEllipse( original, cvPoint(450,100), cvSize(100,70), 0, 0, 360,CV_RGB(255,0,0), -1, 8, 0 );
	cvCircle(original,cvPoint(270,100),50,CV_RGB(255,0,0),-1);
	//Printing Text
	cvPutText(original,"Text", cvPoint(600,90), &font, cvScalar(255,0,0));

    //Showing the image
    cvShowImage("Drawing",original);
    
	//Escape Sequence
    cvWaitKey(0);
    //CleanUp
    cvReleaseImage(&original);
    cvDestroyAllWindows();

}

