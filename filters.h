#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

class Filters
{
public:
  Filters();
  ~Filters();

  static Mat OpenCVAvgFilter(Mat inputImage, int kernelSize);
  static Mat OpenCVGuassianFilter(Mat inputImage, int kernelSize, float sigma);
  static Mat OpenCVMedianFilter(Mat inputImage, int kernelSize);

};

#endif // FILTERS_H
