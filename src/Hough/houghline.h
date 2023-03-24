#ifndef HOUGHLINE_H
#define HOUGHLINE_H

#include <stdio.h>
#include <iostream>

#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;




class HoughLine
{
public:
  HoughLine();

  static double LinePI;
  static int numThetas;
  static int numRadii;
  static int hough_threshold;

  static Mat detectEdge(Mat Image);
  static void polarToCartesian(double rho, int theta, Point& p1, Point& p2);
  static Mat detectLines(Mat Image, int threshold);
  static Mat houghEllipse(Mat& edges, Mat& output);
  static Mat linesHough(Mat edges, Mat output ,int threshold, double rho, int theta);

};

#endif // HOUGHLINE_H
