/******************************************************************************
 *
 * File Name: noiseaddivates.h
 * Description: Header file for Noise Addatives Class including Unifrom,
 * Guassian & Salt-Pepper noise
 * Author(s): Omina Sayed
 * Last Modified: 3 Mar 23 - 23:11
 *
 *******************************************************************************/


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
    static Mat GaussianNoise(const Mat SrcImg,double Mean, double StdDev);
    static Mat SaltAndPepperNoise(Mat SrcImg);
    static inline unsigned char Clamp(int n);
};

#endif // NOISEADDATIVES_H
