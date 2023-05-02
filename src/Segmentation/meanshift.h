#ifndef MEANSHIFT_H
#define MEANSHIFT_H

#include <opencv2\opencv.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace cv;
using namespace std;

#define MAX_CONVERGENCE_ITRS            10										// up to 10 steps are for convergence
#define TOLERANCE_COLOR			0.3										// minimum mean color shift change
#define TOLERANCE_SPATIAL		0.3										// minimum mean spatial shift change

struct PixelDataContainer
{
  float x;			// X-Coordinate
  float y;			// Y-Coordinate
  float l;			// Lightness
  float u;			// (-)
  float v;			// (-)
};

class MeanShift
{
public:
  MeanShift();
  static Mat MeanShiftSegmentation(Mat Img, float distanceBandwidth, float colorBandwidth);

private:
  static void setPixelData(PixelDataContainer* pixel, float pixelX, float pixelY, float pixelL, float pixelU, float pixelV);
  static void setUpLUVPixel(PixelDataContainer* pixel);
  static void setUpRGBPixel(PixelDataContainer* pixel);
  static float CalculateColorDistance(PixelDataContainer pixel1, PixelDataContainer pixel2);
  static float CalculateSpatialDistance(PixelDataContainer pixel1, PixelDataContainer pixel2);
  static void MuliplyPixelDataByScale(PixelDataContainer* pixel, float scale);
  static void addPixels(PixelDataContainer* mainPixel, PixelDataContainer pixelAdded);
  static void copyPixel(PixelDataContainer* pixelCopyingTo, PixelDataContainer* pixelCopyingFrom);

};

#endif // MEANSHIFT_H
