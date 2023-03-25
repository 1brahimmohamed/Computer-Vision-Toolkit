#ifndef THRESHOLD_H
#define THRESHOLD_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


Mat LocalThresholdImage(Mat inputImage, int blockSize, double k);
Mat GlobalthresholdImage(Mat inputImage, int thresholdValue);

#endif // THRESHOLD_H
