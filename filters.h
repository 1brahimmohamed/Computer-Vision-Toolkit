#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Filters
{
public:
  Filters();
  ~Filters();

  static Mat OpenCVAvgFilter(Mat inputImage, int kernelSize);
  static Mat OpenCVGuassianFilter(Mat inputImage, int kernelSize, float sigma);
  static Mat OpenCVMedianFilter(Mat inputImage, int kernelSize);

  static Mat applyAverageFilter(Mat inputImage, int kernelSize);
  static Mat applyGaussianFilter(Mat inputImage, int kernelSize, float sigma);
  static Mat applyMedianFilter(Mat inputImage, int kernelSize);

  static vector<vector<double>> computeGuassianKernel(int kernelSize, float sigma);

};

#endif // FILTERS_H
