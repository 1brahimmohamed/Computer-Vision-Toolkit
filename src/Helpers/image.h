#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class Image
{
public:
  Image();

  int kenerlSize;
  float sigma;

  void setFirstUpload(Mat image);
  void setCurrentImage(Mat image);
  void setFilteredImage(Mat image);
  void setNormalizedImage(Mat image);

  Mat getOriginalImage();
  Mat getCurrentImage();
  Mat getFilteredImage();
  Mat getNormalizedImage();

private:
  Mat Original;
  Mat Current;
  Mat Filtered;
  Mat Previous;
  Mat Normalized;
};

#endif // IMAGE_H
