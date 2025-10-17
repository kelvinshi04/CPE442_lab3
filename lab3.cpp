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

    Mat frame;
    while (cap.read(frame)){
        flip(frame, frame, -1);
        Mat gray = to442_grayscale(frame);
        Mat sobel = to442_sobel(gray);
        imshow("gImage", sobel);
        waitKey(1);
    }

    return 0;
}

// Given a colored image, return a grayscale version using ITU-R (BT.709) algorithm
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


// Apply the sobel filter on a grayscale image
Mat to442_sobel(Mat input){
    Mat sobel(input.rows, input.cols, CV_8UC1, Scalar(0));
    int16_t xtotal, ytotal, total;
    for (int r = 1; r < input.rows-1; r++){
        uchar* topRow = input.ptr<uchar>(r-1);
        uchar* midRow = input.ptr<uchar>(r);
        uchar* botRow = input.ptr<uchar>(r+1);
        uchar* sRow = sobel.ptr<uchar>(r);
        for (int c = 1; c < input.cols-1; c++){
            // Apply sobel filter
            xtotal = -topRow[c-1] + topRow[c+1] - midRow[c-1]*2 + midRow[c+1]*2 - botRow[c-1] + botRow[c+1];
            ytotal = topRow[c-1] + topRow[c]*2 +topRow[c+1] - botRow[c-1] - botRow[c]*2 - botRow[c+1];
            total = abs(xtotal) + abs(ytotal);
            total = (total > 255) ? 255 : ((total < 0) ? 0 : total);
            sRow[c] = total;
        }
    }
    return sobel;
} 
