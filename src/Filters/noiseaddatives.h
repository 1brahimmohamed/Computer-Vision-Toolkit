#ifndef NOISEADDATIVES_H
#define NOISEADDATIVES_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
class NoiseAddatives
{
public:
    NoiseAddatives();
   ~NoiseAddatives();
    static Mat GaussianNoise(const Mat SrcImg, Mat &DstImg,double Mean, double StdDev);
    static Mat SaltAndPepperNoise(Mat SrcImg);
    static inline unsigned char Clamp(int n);
};

#endif // NOISEADDATIVES_H
