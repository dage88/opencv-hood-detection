#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp> //Evualuates which opencv submodules were actually built, and then includes them

#include "OHD_statemachine.hpp"
#include "OHD_types.hpp"

using namespace cv;
using namespace std;

/* Is executed on each change of a trackbar bar */
static void on_trackbar(int, void *)
{
}

int main(int argc, char **argv)
{
    /**************************************** Variables *****************************************/
    /* SM related variables */
    OHD_StateMachine sm;
    int pressedKey;
    const int ESC_KEY = 0x1B;

    /* General video variables */
    VideoCapture cap0(0);
    Mat img; // unprocessed video input

    /* Gray+Blur variables */
    Mat img_gray, img_gray_blur, kernel, img_gray_blur_edges, img_gray_blur_edges_dilated;
    int kernel_size_int = 7; // GaussianBlur kernel size
    Size kernel_size_mat;

    /* HSV variables (Hue, Saturation lightness Value) */
    Mat img_hsv, img_hsv_masked;
    int h_min = 0, s_min = 100, v_min = 100;
    int h_max = 19, s_max = 200, v_max = 200;
    const int h_slider_max = 179, s_slider_max = 255, v_slider_max = 255;

    /* Shape detection variables */
    vector<vector<Point>> contours, contours_poly;
    vector<Rect> boundRect;
    vector<Vec4i> hierarchy; // Vec4i: opencv-specific vector with 4 integers
    Scalar lower(h_min, s_min, v_min), upper(h_max, s_max, v_max);
    int area; // calculated area of a closed contour
    int min_area_slider;
    const int area_slider_max = 20000;

    /**************************************** Trackbar *****************************************/
    namedWindow("Preprocessing Trackbars", WINDOW_NORMAL);
    namedWindow("HSV Trackbars", WINDOW_NORMAL);
    namedWindow("Shape Trackbars", WINDOW_NORMAL);

    createTrackbar("BlurKsize", "Preprocessing Trackbars", &kernel_size_int, 15, on_trackbar);

    createTrackbar("Hue Min", "HSV Trackbars", &h_min, h_slider_max, on_trackbar);
    createTrackbar("Hue Max", "HSV Trackbars", &h_max, h_slider_max, on_trackbar);
    createTrackbar("Sat Min", "HSV Trackbars", &s_min, s_slider_max, on_trackbar);
    createTrackbar("Sat Max", "HSV Trackbars", &s_max, s_slider_max, on_trackbar);
    createTrackbar("Val Min", "HSV Trackbars", &v_min, v_slider_max, on_trackbar);
    createTrackbar("Val Max", "HSV Trackbars", &v_max, v_slider_max, on_trackbar);

    createTrackbar("MinArea", "Shape Trackbars", &min_area_slider, area_slider_max, on_trackbar);

    /**************************************** Statemachine *****************************************/
    while (true)
    {
        // update slider variables cyclicly
        lower = Scalar(h_min, s_min, v_min);
        upper = Scalar(h_max, s_max, v_max);
        if (kernel_size_int % 2 == 1) // only update kernel size for odd sizes
        {
            kernel_size_mat = Size(kernel_size_int, kernel_size_int);
        }

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

            /**************************************** Read Cam *****************************************/
            cap0.read(img); // For my webcam: 640x480

            /*************************** Gray + Blur + Dilation Preprocessing ***************************/
            cvtColor(img, img_gray, COLOR_BGR2GRAY);
            GaussianBlur(img_gray, img_gray_blur, kernel_size_mat, 3, 0);
            Canny(img_gray_blur, img_gray_blur_edges, 50, 150);

            kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
            dilate(img_gray_blur_edges, img_gray_blur_edges_dilated, kernel);

            /****************** Find shape ***********************/
            findContours(img_gray_blur_edges_dilated, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            contours_poly.resize(contours.size()); // update approximated polygon
            boundRect.resize(contours.size());     // update indication-rectangle

            for (int i = 0; i < contours.size(); i++)
            {
                area = contourArea(contours[i]);
                cout << "area: " << area << endl;

                if (area > min_area_slider)
                {
                    float peri = arcLength(contours[i], true);                     // Check if contour is closed
                    approxPolyDP(contours[i], contours_poly[i], 0.2 * peri, true); // returns an approximation as polygon (array of points)
                    drawContours(img, contours_poly, i, Scalar(255, 0, 255), 1);   // draw onto img the detected contours in purple  with thickness 5
                                                                                   // draw rectangle around detected shapes
                    cout << "contours_poly[" << i << "]:  " << contours_poly[i] << endl;
                    boundRect[i] = boundingRect(contours_poly[i]);
                    rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
                }
            }
            cout << "--------------------------------------------" << endl;

            /****************** HSV conversion and masking with taskbar values ***********************/
            cvtColor(img, img_hsv, COLOR_BGR2HSV);
            inRange(img_hsv, lower, upper, img_hsv_masked);

            /**************************************** Display *****************************************/
            imshow("Display Image", img);
            imshow("Display blurred Image", img_gray_blur);
            imshow("Display edges on gray blurred img (dilated edges)", img_gray_blur_edges_dilated);
            imshow("Display HSV-converted img", img_hsv);
            imshow("Display masked HSV-converted img", img_hsv_masked);

            pressedKey = waitKey(1);
            if (pressedKey == ESC_KEY)
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