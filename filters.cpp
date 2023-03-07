#include "filters.h"

Filters::Filters()
{

}

Filters::~Filters()
{

}

// ------------------------------------ OpenCV Functions  -----------------------------------------//

Mat Filters::OpenCVAvgFilter(Mat inputImage, int kernelSize){
   Mat outputImage;
   Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize*kernelSize);

   // Apply filter on input image
   filter2D(inputImage, outputImage, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT);

   return outputImage;
}

Mat Filters::OpenCVGuassianFilter(Mat inputImage, int kernelSize, float sigma){
  Mat outputImage;
  GaussianBlur(inputImage, outputImage, Size(kernelSize, kernelSize), sigma);
  return outputImage;
}

Mat Filters::OpenCVMedianFilter(Mat inputImage, int kernelSize){
  Mat outputImage;
  medianBlur(inputImage, outputImage, kernelSize);
  return outputImage;
}
