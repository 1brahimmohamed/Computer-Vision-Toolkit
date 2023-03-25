#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "cvector.h"
#include "utils.h"
#include <math.h>
#include <cstdlib>
#include <cmath>

#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

double points_distance(int x1, int y1, int x2, int y2)
{

    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int count_edges(cv::Mat img,cv::Mat test)
{
  int count =0;
    for (int i = 0; i < img.rows; i++)
      {
        for (int j = 0; j < img.cols; j++)
          {
            test.at<uchar>(i, j) =0;
            if((int)img.at<uchar>(i, j)!=0)
            count = count +1;
          }
      }
return count;
}

void draw_circle(cv::Mat img,int x,int y, int r)
{
  int a,b;
    for (int theta = 0; theta < 360; theta++)
  {
    a = (int)(x-r - r*cos(theta*3.14159/180));
    b = (int)(y - r*sin(theta*3.14159/180));
    if ( a>0 && a<img.cols && b>0 && b<img.rows)
    img.at<uchar>(a, b) =255;
  }
}

cvector<cvector<double>> gaussian_kernel(int size, double std)
{
  double gaussian_value;
  cvector<cvector<double>> filter;
  for (int row = -size / 2; row <= size / 2; row++)
  {
    cvector<double> row_vector;
    for (int col = -size / 2; col <= size / 2; col++)
    {
      gaussian_value = (1 / (2 * (22 / 7) * pow(std, 2))) * exp(-(pow(row, 2) + pow(col, 2)) / (2 * pow(std, 2)));
//      normalization_sum += gaussian_value;
      row_vector.push_back(gaussian_value);
    }
    filter.push_back(row_vector);
  }

  return filter;
}

void RGBtoHSV(float r, float g, float b, float *h, float *s, float *v)
{
  r = r / 255.0;
  g = g / 255.0;
  b = b / 255.0;

  // h, s, v = hue, saturation, value
  double cmax = max(r, max(g, b)); // maximum of r, g, b
  double cmin = min(r, min(g, b)); // minimum of r, g, b
  double diff = cmax - cmin;       // diff of cmax and cmin.

  // if cmax and cmax are equal then h = 0
  if (cmax == cmin)
    *h = 0;

  // if cmax equal r then compute h
  else if (cmax == r)
    *h = (int)(60 * ((g - b) / diff) + 360) % 360;

  // if cmax equal g then compute h
  else if (cmax == g)
    *h = (int)(60 * ((b - r) / diff) + 120) % 360;

  // if cmax equal b then compute h
  else if (cmax == b)
    *h = (int)(60 * ((r - g) / diff) + 240) % 360;

  // if cmax equal zero
  if (cmax == 0)
    *s = 0;
  else
    *s = (diff / cmax) * 100;

  // compute v
  *v = cmax * 100;
}

void HSVtoRGB(float *fR, float *fG, float *fB, float fH, float fS, float fV)
{
  double fC = fV * fS; // Chroma
  double fHPrime = fmod(fH / 60.0, 6);
  double fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  double fM = fV - fC;

  if (0 <= fHPrime && fHPrime < 1)
  {
    *fR = fC;
    *fG = fX;
    *fB = 0;
  }
  else if (1 <= fHPrime && fHPrime < 2)
  {
    *fR = fX;
    *fG = fC;
    *fB = 0;
  }
  else if (2 <= fHPrime && fHPrime < 3)
  {
    *fR = 0;
    *fG = fC;
    *fB = fX;
  }
  else if (3 <= fHPrime && fHPrime < 4)
  {
    *fR = 0;
    *fG = fX;
    *fB = fC;
  }
  else if (4 <= fHPrime && fHPrime < 5)
  {
    *fR = fX;
    *fG = 0;
    *fB = fC;
  }
  else if (5 <= fHPrime && fHPrime < 6)
  {
    *fR = fC;
    *fG = 0;
    *fB = fX;
  }
  else
  {
    *fR = 0;
    *fG = 0;
    *fB = 0;
  }

  *fR += fM;
  *fG += fM;
  *fB += fM;
}
