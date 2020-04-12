//Opencv C++ Program to solve mazes using mathematical morphology
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
 
using namespace cv;
using namespace std;
 
int main()
{
    Mat src = imread("eg1.png");
    if( !src.data ) { printf("Error loading src \n"); return -1;}
 
 //Convert the given image into Binary Image
    Mat bw;
    cvtColor(src, bw, CV_BGR2GRAY);
    threshold(bw, bw, 10, 255, CV_THRESH_BINARY_INV);
 
 //Detect Contours in an Image
    vector<std::vector<cv::Point> > contours;
    findContours(bw, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
 
    if (contours.size() != 2)
    {
        // "Perfect maze" should have 2 walls
        std::cout << "This is not a 'perfect maze' with just 2 walls!" << std::endl;
        return -1;
    }
 
    Mat path = Mat::zeros(src.size(), CV_8UC1);
    drawContours(path, contours, 0, CV_RGB(255,255,255), CV_FILLED);
  
 //Dilate the Image
    Mat kernel = Mat::ones(21, 21, CV_8UC1); 
    dilate(path, path, kernel);
 
 //Erode the Image
    Mat path_erode;
    erode(path, path_erode, kernel);
 
 //Subtract Eroded Image from the Dilate One
    absdiff(path, path_erode, path);
 
 //Draw the Path by Red Color
    vector<Mat> channels;
    split(src, channels);
    channels[0] &= ~path;
    channels[1] &= ~path;
    channels[2] |= path;
 
    Mat dst;
    merge(channels, dst);
    imshow("solution", dst);
    waitKey(0);
 
    return 0;
}
