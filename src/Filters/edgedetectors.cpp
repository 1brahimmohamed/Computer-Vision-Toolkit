#include "edgedetectors.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include<cstdint>
#include <iostream>
using namespace cv;
using namespace std;
EdgeDetectors::EdgeDetectors()
{

}
EdgeDetectors:: ~EdgeDetectors()
{

}
/*
Apply a Gaussian Filter
Apply sobel : method to compute the x and y gradient vector components.
Apply non-maximum suppression: edge thinning technique used to remove extraneous edge candidates.
Apply double thresholding: is used to categorize the remaining edge pixels into three categories using a low, high and very low threshold value
Apply hysteresis
 */
Mat EdgeDetectors::CannyEdgeDetector(Mat SrcImg)
{
    Mat blurred;
    blur(SrcImg, blurred, Size(3, 3));
    Mat xComponent, yComponent;
    Sobel(blurred, xComponent, CV_64F, 1, 0, 3);
    Sobel(blurred, yComponent, CV_64F, 0, 1, 3);
    Mat magnitude, angle;
    cartToPolar(xComponent, yComponent, magnitude, angle, true);
    //normalization to get evenly distributed data
    normalize(magnitude, magnitude, 0, 1, NORM_MINMAX);
    int neighbor1X, neighbor1Y, neighbor2X, neighbor2Y;
    float gradientAngle;
    for (int x = 0; x < blurred.rows; x++) {
      for (int y = 0; y < blurred.cols; y++) {
        gradientAngle = angle.at<float>(y, x);
        //grediant angle between 0-180
        if (abs(gradientAngle) > 180)
          gradientAngle = abs(gradientAngle-180);
        else
          gradientAngle = abs(gradientAngle);
        if (gradientAngle <= 22.5) {
          neighbor1X = x-1; neighbor1Y = y;
          neighbor2X = x+1; neighbor2Y = y;
        } else if (22.5 < gradientAngle <= 67.5) {
          neighbor1X = x-1; neighbor1Y = y-1;
          neighbor2X = x+1; neighbor2Y = y+1;
        } else if (67.5 < gradientAngle <= 112.5) {
          neighbor1X = x; neighbor1Y = y-1;
          neighbor2X = x; neighbor2Y = y+1;
        } else if (112.5 < gradientAngle <= 157.5) {
          neighbor1X = x-1; neighbor1Y = y+1;
          neighbor2X = x+1; neighbor2Y = y-1;
        } else if (157.5 < gradientAngle <= 202.5) {
          neighbor1X = x-1; neighbor1Y = y;
          neighbor2X = x+1; neighbor2Y = y;
        }
        if ((0 <= neighbor1X < blurred.rows)
        && (0 <= neighbor1Y < blurred.cols)) {
          if (magnitude.at<float>(y, x) < magnitude.at<float>             (neighbor1Y, neighbor1X)) {
             magnitude.at<float>(y, x) = 0;
             continue;
          }
        }
        if ((0 <= neighbor2X < blurred.rows)
        && (0 <= neighbor2Y < blurred.cols)) {
          if (magnitude.at<float>(y, x) < magnitude.at<float>          (neighbor2Y, neighbor2X)) {
            magnitude.at<float>(y, x) = 0;
            continue;
          }
        }
      }
    }



    float magMax = 0.5, magMin = 0.1;
    Mat strong = Mat::zeros(magnitude.rows, magnitude.cols, CV_64F);
    Mat weak = Mat::zeros(magnitude.rows, magnitude.cols, CV_64F);
    Mat suppress = Mat::zeros(magnitude.rows, magnitude.cols, CV_64F);
    float gradientMagnitude;
    for (int x = 0; x < magnitude.cols; x++) {
      for (int y = 0; y < magnitude.rows; y++) {
        gradientMagnitude = magnitude.at<float>(x, y);
        if (gradientMagnitude > magMax)
          strong.at<float>(x, y) = gradientMagnitude;
        else if (gradientMagnitude <= magMax && gradientMagnitude > magMin)
          weak.at<float>(x, y) = gradientMagnitude;
        else
          suppress.at<float>(x, y) = gradientMagnitude;
      }
    }
//The process simply checks to see if a weak edge pixel is connected (neighbored by) a strong edge pixel.
    for (int x = 0; x < weak.cols; x++) {
      for (int y = 0; y < weak.rows; y++) {
        if (weak.at<float>(x, y) != 0) {
          if ((strong.at<float>(x+1, y))
          || (strong.at<float>(x-1, y))
          || (strong.at<float>(x, y+1))
          || (strong.at<float>(x, y-1))
          || (strong.at<float>(x-1, y-1))
          || (strong.at<float>(x+1, x-1))
          || (strong.at<float>(x-1, y+1))
          || (strong.at<float>(x+1, y-1)))
            strong.at<float>(x, y) = weak.at<float>(x, y);
        }
      }
    }
    return strong;
}
