#ifndef OPTIMALTHRESHOLDING_H
#define OPTIMALTHRESHOLDING_H

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class OptimalThresholding
{
public:
    OptimalThresholding();
    static Mat getOptimalThreshold(Mat InputImage);
};

#endif // OPTIMALTHRESHOLDING_H
