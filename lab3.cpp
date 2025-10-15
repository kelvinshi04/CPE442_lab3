#include <iostream>
#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;

void to442_grayscale(Mat);
Mat to442_sobel(Mat);

int main(int argc, char** argv){
    //ensure number of arguments are correct
    if (argc != 2){
        cout << "Error: Invalid input" << endl;
        return 0;
    }
    string videoPath = argv[1];
    VideoCapture cap(videoPath);

    if (!cap.isOpened()){
        perror("Error: Could not open video file.");
        return 0;
    }

    Mat frame;
    while (cap.read(frame)){
        to442_grayscale(frame);
        Mat sobelFrame = to442_sobel(frame);
        imshow("win1", sobelFrame);
    }
    
    return 0;
}


