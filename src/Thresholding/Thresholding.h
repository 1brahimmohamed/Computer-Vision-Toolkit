#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class Thresholding
{
public:
    Thresholding();
    static Mat getOptimalThreshold(Mat InputImage, int max_iterations , double threshold );
    static Mat Otsu(Mat InputImage);
};

#endif // THRESHOLDING_H
