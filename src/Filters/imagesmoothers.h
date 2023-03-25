/******************************************************************************
 *
 * File Name: imagesmoothers.h
 * Description: Header file for Image Smoothers Class to remove noise
 * including removing  noise using Average, Guassian & Median Filters
 * Author: Ibrahim Mohamed
 * Last Modified: 25 Mar 23 - 01:36
 *
 *******************************************************************************/

#ifndef IMAGESMOOTHERS_H
#define IMAGESMOOTHERS_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

#include <vector>
#include <QDebug>
#include <algorithm>
#include <queue>
#include <vector>

using namespace cv;
using namespace std;
class ImageSmoothers
{
public:
  ImageSmoothers();
  ~ImageSmoothers();

  // original CV functions
  static Mat OpenCVAvgFilter(Mat inputImage, int kernelSize);
  static Mat OpenCVGuassianFilter(Mat inputImage, int kernelSize, float sigma);
  static Mat OpenCVMedianFilter(Mat inputImage, int kernelSize);

  // implemented functions
  static Mat applyAverageFilter(Mat inputImage, int kernelSize);
  static Mat applyGaussianFilter(Mat inputImage, int kernelSize, float sigma);
  static Mat applyMedianFilter(Mat inputImage, int kernelSize);

  static vector<vector<double>> computeGuassianKernel(int kernelSize, float sigma);
  static Mat cannyEdgeDetection(const Mat& input, double threshold1, double threshold2);
};

#endif // IMAGESMOOTHERS_H
