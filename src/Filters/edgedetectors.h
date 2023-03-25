/******************************************************************************
 *
 * File Name: edgedectectors.h
 * Description: Header file for Edge Detectors Class including Sobel,
 * Prewitte, Roberts & Canny
 * Author(s): Omina Sayed & Ibrahim Mohamed
 * Last Modified: 24 Mar 23 - 03:11
 *
 *******************************************************************************/

#ifndef EDGEDETECTORS_H
#define EDGEDETECTORS_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class EdgeDetectors
{
public:
    EdgeDetectors();
   ~EdgeDetectors();
    static Mat CannyEdgeDetector(Mat srcImg);
    static Mat RobertEdgeDetector(Mat SrcImg);
    static Mat PerwittEdgeDetector(Mat SrcImg);
    static Mat SobalEdgeDetector(Mat SrcImg);
};

#endif // EDGEDETECTORS_H
