#ifndef REGIONGROWING_H
#define REGIONGROWING_H

#include <opencv2/opencv.h>

class RegionGrowing {
public:
    // Constructor
    RegionGrowing(cv::Size imageSize);

    // Define a struct to represent a pixel
    struct Pixel {
        int row;
        int col;
    };

    // Define a function to check if a pixel is within the image bounds
    bool isPixelInBounds(const cv::Mat& image, int row, int col);

    // Define the region growing function
    cv::Mat growRegion(cv::Mat& inputImage, int seedRow, int seedCol, int threshold);

private:
    cv::Size m_imageSize;
};

#endif // REGIONGROWING_H
