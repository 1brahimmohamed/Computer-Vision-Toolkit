#ifndef HOUGHELLIPSE_H
#define HOUGHELLIPSE_H

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

class HoughEllipse
{
public:
  HoughEllipse();

  static int approximate(float x, int step);
  static Mat houghEllipseDetection(Mat img, float threshold, int neighbour_size, int rad_step, int center_step);
};

#endif // HOUGHELLIPSE_H
