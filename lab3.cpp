#include <iostream>
#include <stdlib.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>

using namespace std;
using namespace cv;

Mat to442_grayscale(Mat);
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

    // in the works
    Mat frame;
    while (cap.read(frame)){
        flip(frame, frame, -1);
        Mat gray = to442_grayscale(frame);
        imshow("gImage", gray);
        waitKey(30);
        //Mat sobelFrame = to442_sobel(frame);
        //imshow("win1", sobelFrame);
    }

    return 0;
}

Mat to442_grayscale(Mat frame){
    Mat gray(frame.rows, frame.cols, CV_8UC1, Scalar(0));
    for (int r = 0; r < frame.rows; r++){
        Vec3b* row = frame.ptr<Vec3b>(r);
        uchar* gRow = gray.ptr<uchar>(r);
        for (int c = 0; c < frame.cols; c++){
            Vec3b pixel = row[c];
            gRow[c] = pixel[0]*0.0722 + pixel[1]*0.7152 + pixel[2]*0.2126;
        }
    }
    return gray;
}


