#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
// #include <D:/Tools/opencv/build/include/opencv2/opencv.hpp>

#include "OHD_statemachine.hpp"
#include "OHD_types.hpp"

using namespace cv;

int main(int argc, char **argv)
{
    Mat image;
    OHD_StateMachine sm;
    event_t event = EVENT_INITIALIZE_REQUEST;
    int counter = 0;

    image = imread("D:/workspace/opencv-hood-detection/triangles.png");
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);

    sm.OHD_StateMachine::ProcessEvent(event);

    while (true)
    {
        counter++;
        if (counter % 1000 == 0)
        {
            std::cout << counter << "\n";
        }
        else if (counter == 20001)
        {
            std::cout << "main end.";
            return 0;
        }
    };
}