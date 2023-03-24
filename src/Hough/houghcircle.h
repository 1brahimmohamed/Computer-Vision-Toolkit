#ifndef HOUGHCIRCLE_H
#define HOUGHCIRCLE_H

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <time.h>


using namespace cv;
using namespace std;


// Struct to store center points and pixel intensities
struct cent
{
    int bright;
    int Xbright;
    int Ybright;
};

// Vector to print circles
vector<Vec3f> circles;
int Xc, Yc;

// Maximum and minimum radius values
int maxradius = 40;
int minradius = 9;
int radius = maxradius;
// Array of structs to store center points
cent accumul[40];

class HoughCircle
{
public:
  HoughCircle();
  static Mat HoughCircleCall(Mat HoughCircle);
  static Mat Accumulate(Mat SrcImg);
};

#endif // HOUGHCIRCLE_H
