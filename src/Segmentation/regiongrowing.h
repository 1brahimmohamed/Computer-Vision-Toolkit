#ifndef REGIONGROWING_H
#define REGIONGROWING_H

#include <opencv2/opencv.hpp>

class RegionGrowing {
public:
  // Constructor
  RegionGrowing();

  // Define a struct to represent a pixel
  struct Pixel {
    int row;
    int col;
  };

  // Define the region growing function
  static cv::Mat growRegion(cv::Mat inputImage, int seedRow, int seedCol, int threshold, cv::Size m_imageSize);

private:

  // Define a function to check if a pixel is within the image bounds
  static bool isPixelInBounds(const cv::Mat& image, int row, int col);
};

#endif // REGIONGROWING_H
