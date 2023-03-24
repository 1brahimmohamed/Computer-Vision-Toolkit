#ifndef HOUGHCIRCLE_H
#define HOUGHCIRCLE_H

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <time.h>

#define PI 3.14159265358979323846264338327950288


using namespace cv;
using namespace std;

class HoughCircle
{
public:
  HoughCircle();

  static vector <Vec3f> circles;
  static int Xc, Yc;
  static int maxradius;
  static int minradius;
  static int radius;
  struct cent
  {
    int bright;
    int Xbright;
    int Ybright;
  };

  static Mat Accumulate(Mat SrcImg, int maxradius, int minradius);
  static Mat HoughCircleCall(Mat HoughCircle, int minRaduis, int maxRaduis);
};

#endif // HOUGHCIRCLE_H
