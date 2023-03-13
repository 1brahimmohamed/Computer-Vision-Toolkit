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
  void setPreviousActionImage(Mat image);
  void setNextActionImage(Mat image);

  Mat getOriginalImage();
  Mat getCurrentImage();
  Mat getFilteredImage();
  Mat getPreviousActionImage();
  Mat getNextActionImage();

private:
  Mat Original;
  Mat Current;
  Mat Filtered;
  Mat Previous;
  Mat Next;
};

#endif // IMAGE_H
