#ifndef HARRISOPERATOR_H
#define HARRISOPERATOR_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include<cmath>
#include<cstdint>
#include <random>
#include <iostream>

using namespace cv;
using namespace std;
class HarrisOperator
{
public:
    HarrisOperator();
    static double threshold_level;
    static Mat XDerivative(Mat SrcImg);
    static Mat YDerivative(Mat SrcImg);
    static Mat convertToGrayScale(Mat SrcImg);
    static void HarrisDetector(Mat SrcImg, Mat& R, double threshold_level);
    static void getLocalMax(Mat R, Mat& localMax);
    static Mat drawPointsToImg(Mat img, Mat localMax);
    static Mat HarrisDrivingFunction(Mat SrcImg, double threshold_level);
};
#endif // HARRISOPERATOR_H
