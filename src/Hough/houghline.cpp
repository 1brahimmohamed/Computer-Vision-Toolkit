/******************************************************************************
 *
 * File Name: houghline.cpp
 * Description: Source file for Line Detection using Hough Transfrom Class
 * Author(s): Marina Nasser & Ibrahim Mohamed
 * Last Modified: 23 Mar 23 - 16:09
 *
 *******************************************************************************/


#include "houghline.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

#define BIN_WIDTH 1
#define NUM_BINS 180 / BIN_WIDTH

/* === PARAMETERS FOR CANNY EDGE DETECTION === */

#define KERNEL_SIZE 3
#define TRESHOLD1 50
#define RATIO 3

double HoughLine::LinePI = 3.14159265358979323846;
int HoughLine::hough_threshold = 120;
int HoughLine::numThetas       = 180;
int HoughLine::numRadii        = 100;

HoughLine::HoughLine()
{

}


Mat HoughLine::detectEdge(Mat Image) {
  Mat output;
  Canny(Image, output, 50 , 150, 3);
  return output;
}

void HoughLine::polarToCartesian(double rho, int theta, Point& p1, Point& p2) {

  int x0 = cvRound(rho * cos(theta));
  int y0 = cvRound(rho * sin(theta));

  p1.x = cvRound(x0 + 1000 * (-sin(theta)));
  p1.y = cvRound(y0 + 1000 * (cos(theta)));

  p2.x = cvRound(x0 - 1000 * (-sin(theta)));
  p2.y = cvRound(y0 - 1000 * (cos(theta)));
}

Mat HoughLine::linesHough(Mat edges, Mat output, int threshold ,double rho = 0, int theta = 0){

  int maxDistance = hypot(edges.rows, edges.cols);
  vector<vector<int>> votes(2 * maxDistance, vector<int>(NUM_BINS, 0));

  for (int i = 0; i < int(votes.size()); ++i) {
      for (int j = 0; j < int(votes[0].size()); ++j) {
          votes[i][j]=0;
        }
    }

  for(int i = 0; i < edges.rows; ++i) {
      for(int j = 0; j < edges.cols; ++j) {
          if(edges.at<uchar>(i, j) == 255) {
              for(theta = 0; theta <= 180; theta += BIN_WIDTH) {
                  rho = round(j * cos(theta - 90) + i * sin(theta - 90)) + maxDistance;
                  votes[rho][theta]++;
                }
            }
        }
    }

  // find peaks
  for(int i = 0; i < int(votes.size()); ++i) {
      for(int j = 0; j <int(votes[0].size()); ++j) {
          if(votes[i][j] > threshold) {
              rho = i - maxDistance;
              theta = j - 90;
              Point p1, p2;
              polarToCartesian(rho, theta, p1, p2);
              line(output, p1, p2, Scalar(0, 0, 255), 2, LINE_AA);
            }
        }
    }

  return output;
}

Mat HoughLine::detectLines(Mat Image,int threshold = 160){

  cvtColor(Image, Image, COLOR_BGR2GRAY);
  Mat edges = detectEdge(Image);
  Mat linesImage = linesHough(edges, Image, threshold, 0, 0);
  return linesImage;
}

Mat HoughLine::houghEllipse(Mat& edges, Mat& output) {

  int width = edges.cols;
  int height = edges.rows;

  // create accumulator array
  int aMax = (int)sqrt((double) width * width + height * height); //maximum values for the two radii parameters
  int bMax = aMax;
  int cMax = 360 ;//maximum value for the angle parameter.

  vector<vector<vector<int>>> accumulator(2*aMax, vector<vector<int>>(2*bMax, vector<int>(cMax)));

  cout<< edges.rows <<" " << edges.cols << "";

  // populate accumulator array
  for (int y = 0; y < edges.rows; y++) {
      for (int x = 0; x < edges.cols; x++) {

          if (edges.at<uchar>(y, x) == 255) {
              for (int c = 0; c < cMax; c++) {
                  double angle = c * LinePI / 180.0;
                  double a = round(x * cos(angle) + y * sin(angle));
                  double b = round(-x * sin(angle) + y * cos(angle));
                  int aIndex = (int) a + aMax ;
                  int bIndex = (int) b + bMax ;
                  accumulator[aIndex][bIndex][c]++;
                }
            }

        }
    }

  // Find maximum vote in accumulator array
  int max_vote = 0;
  int max_a = 0, max_b = 0, max_c = 0;
  for (int a = 0; a < aMax; a++) {
      for (int b = 0; b < bMax; b++) {
          for (int c = 0; c < cMax; c++) {
              if (accumulator[a][b][c] > max_vote) {
                  max_vote = accumulator[a][b][c];
                  max_a = a;
                  max_b = b;
                  max_c = c;
                }
            }
        }
    }

  int major_axis = max_a;
  int minor_axis = max_b;
  int x0 = (int)(max_c / cos(atan((double)(max_a) / max_b)));  // Calculate center x-coordinate
  int y0 = (int)(max_c / sin(atan((double)(max_a) / max_b)));  // Calculate center y-coordinate
  double angle = atan2((double)max_b, (double)max_a) * 180 / M_PI;  // Calculate angle of rotation in degrees


  // Draw detected ellipse
  Point center(abs(cvRound(x0)), abs(cvRound(y0)));

  Size axes(cvRound(major_axis), cvRound(minor_axis));

  Mat img(output.rows, output.cols, CV_8UC3, Scalar(255,255,255));

  ellipse(img, center, axes, angle, 0, 360, Scalar(255, 0, 0), 10, LINE_AA);

  return img;
}

