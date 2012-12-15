/*

Aim: Printing location of Mouse cursor in window.
by: slashharsh
contact: slashharsh@hotmail.com

*/

#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <stdio.h>  
#include<Windows.h>
using namespace cv;
using namespace std;



 
 int main()
{
    HANDLE hIn;
    HANDLE hOut;
    COORD MouseWhere  = {30, 20};
    COORD DClickWhere = {30, 20};
    
    bool Continue = TRUE;
    DWORD EventCount;
    int LoopCount = 0;
    int KeyEvents = 0;
    INPUT_RECORD InRec;
    DWORD NumRead;

    hIn = GetStdHandle(STD_INPUT_HANDLE);
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    cout<< "Mouse is at     : " <<endl ;
     
	while (Continue)
    {
          
        Sleep(10); // To slow it down!!

        GetNumberOfConsoleInputEvents(hIn,&EventCount);
        while (EventCount > 0)
        {
           ReadConsoleInput(hIn,&InRec,1,&NumRead);

            if (InRec.EventType == KEY_EVENT)
            {
                if (InRec.Event.KeyEvent.uChar.AsciiChar == 'x')
                {
   

                            cout << "Exiting..." << endl;
                            Continue = FALSE;
                }
            }
            else if (InRec.EventType == MOUSE_EVENT)
            {
     
                 if (InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
                {
                    SetConsoleCursorPosition(hOut,
                                             MouseWhere);
                    cout << InRec.Event.MouseEvent.dwMousePosition.X << "," <<
                            InRec.Event.MouseEvent.dwMousePosition.Y << "  " << flush;
                }
                else if (InRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
                {
                    SetConsoleCursorPosition(hOut,
                                             DClickWhere);
                    cout << InRec.Event.MouseEvent.dwMousePosition.X << "," <<
                            InRec.Event.MouseEvent.dwMousePosition.Y << "  " << flush;
                }             
             }
             
          GetNumberOfConsoleInputEvents(hIn,&EventCount);
        }
    }

    return 0;
}