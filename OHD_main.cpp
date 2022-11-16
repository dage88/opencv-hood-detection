#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
// #include <D:/Tools/opencv/build/include/opencv2/opencv.hpp>

#include "OHD_statemachine.hpp"
#include "OHD_types.hpp"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    OHD_StateMachine sm;
    VideoCapture cap0(0);
    Mat img, imgGray, imgBlur, imgEdges, imgGrayEdges, imgBlurredEdges;;
    int pressedKey;
    const int ESC_key = 0x1B;

    while (true)
    {
        switch (sm.getState())
        {

        case OHD_STATE_UNINITIALIZED:
            sm.onEntry();

            sm.setEvent(OHD_EVENT_RUN_REQUEST);

            sm.onExit();
            break;

        case OHD_STATE_STARTUP:
            sm.onEntry();

            namedWindow("Display Image", WINDOW_AUTOSIZE);
            if (!cap0.isOpened())
            {
                cout << "Cannot open c0!";
                sm.setEvent(OHD_EVENT_ERROR);
            }
            else
            {
                sm.setEvent(OHD_EVENT_STARTUP_SUCCESSFUL);
            }

            sm.onExit();
            break;

        case OHD_STATE_RUNNING:
            sm.onEntry();

            cap0.read(img);

            cvtColor(img, imgGray, COLOR_BGR2GRAY);
            GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
            Canny(img, imgEdges, 50, 150);
            Canny(imgGray, imgGrayEdges, 50, 150);
            Canny(imgBlur, imgBlurredEdges, 50, 150);

            imshow("Display Image", img);
            imshow("Display gray Image", imgGray);
            imshow("Display blurred Image", imgBlur);
            imshow("Display edges on gray img", imgGrayEdges);
            imshow("Display edges on blurred img", imgBlurredEdges);
            imshow("Display edges on unprocessed img", imgEdges);
            pressedKey = waitKey(1);
            if (pressedKey == ESC_key)
            {
                return -1; // We quit directly, as we do not need de-initialization.
            }

            sm.onExit();
            break;

        case OHD_STATE_ERROR:
            // Continue to default (For now, no logging here)

        default:
            return -1;
        }
    };
}