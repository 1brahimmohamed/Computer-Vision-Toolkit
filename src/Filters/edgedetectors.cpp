#include <cstdint>
#include <iostream>
#include <QDebug>

#include"edgedetectors.h"



using namespace cv;
using namespace std;
EdgeDetectors::EdgeDetectors()
{

}

EdgeDetectors::~EdgeDetectors()
{

}

/*
Apply a Gaussian Filter
Apply sobel : method to compute the x and y gradient vector components.
Apply non-maximum suppression: edge thinning technique used to remove extraneous edge candidates.
Apply thresholding: is used to categorize the remaining edge pixels into two categories using a low and high threshold value
 */
Mat EdgeDetectors::CannyEdgeDetector(Mat SrcImg)
{
  //apply gaussian filter to smooth the image and prevent detecting false edges
  Mat blurred;
  blur(SrcImg, blurred, Size(3, 3));

  // two-dimensional gradient vector representing the directional change in intensity (brightness) of an image.
  Mat xComponent, yComponent;
  Sobel(blurred, xComponent, CV_32F, 1, 0, 3);
  Sobel(blurred, yComponent, CV_32F, 0, 1, 3);

  //edge thinning technique used to remove extraneous edge candidates
  Mat magnitude, angle;
  cartToPolar(xComponent, yComponent, magnitude, angle, true);
  normalize(magnitude, magnitude, 0, 1, NORM_MINMAX);//normalization to get evenly distributed data
  int neighbor1X, neighbor1Y, neighbor2X, neighbor2Y;
  float gradientAngle;

  for (int x = 0; x < blurred.rows; x++) {
      for (int y = 0; y < blurred.cols; y++) {

          gradientAngle = angle.at<float>(x, y);

          if (abs(gradientAngle) > 180)//grediant angle between 0-180
            gradientAngle = abs(gradientAngle-180);
          else
            gradientAngle = abs(gradientAngle);

          if (gradientAngle <= 22.5) {
              neighbor1X = x-1; neighbor1Y = y;
              neighbor2X = x+1; neighbor2Y = y;
            } else if (22.5 < gradientAngle && gradientAngle<= 67.5) {
              neighbor1X = x-1; neighbor1Y = y-1;
              neighbor2X = x+1; neighbor2Y = y+1;
            } else if (67.5 < gradientAngle && gradientAngle<= 112.5) {
              neighbor1X = x; neighbor1Y = y-1;
              neighbor2X = x; neighbor2Y = y+1;
            } else if (112.5 < gradientAngle && gradientAngle <= 157.5) {
              neighbor1X = x-1; neighbor1Y = y+1;
              neighbor2X = x+1; neighbor2Y = y-1;
            } else if (157.5 < gradientAngle && gradientAngle <= 180) {
              neighbor1X = x-1; neighbor1Y = y;
              neighbor2X = x+1; neighbor2Y = y;
            }
          if ((0 <= neighbor1X && neighbor1X < magnitude.rows)
              && (0 <= neighbor1Y && neighbor1Y < magnitude.cols)) {
              if (magnitude.at<float>(x, y) < magnitude.at<float>(neighbor1X, neighbor1Y)) {
                  magnitude.at<float>(x, y) = 0;
                  continue;
                }
            }
          if ((0 <= neighbor2X && neighbor2X < blurred.rows)
              && (0 <= neighbor2Y && neighbor2Y < blurred.cols)) {
              if (magnitude.at<float>(x, y) < magnitude.at<float>(neighbor2X,neighbor2Y))
                {
                  magnitude.at<float>(x, y) = 0;
                  continue;
                }
            }
        }
    }

  //  //to categorize the remaining edge pixels into three categories using a low and high threshold value.
  //  float magMax = 0.5, magMin = 0.1;
  //  Mat strong = Mat::zeros(magnitude.rows, magnitude.cols, CV_32F);
  //  Mat strong = magnitude.clone();
  //  inRange(magnitude, magMin, magMax, strong);

  float magMax = 0.2, magMin = 0.1;
  Mat strong = Mat::zeros(magnitude.rows, magnitude.cols, CV_32F);
  Mat weak = Mat::zeros(magnitude.rows, magnitude.cols, CV_32F);
  Mat suppress = Mat::zeros(magnitude.rows, magnitude.cols, CV_32F);
  float gradientMagnitude;

  //  for (int x = 0; x < magnitude.cols; x++) {
  //      for (int y = 0; y < magnitude.rows; y++) {
  //          gradientMagnitude = magnitude.at<float>(x, y);
  //          if (gradientMagnitude > magMax)
  //            strong.at<float>(x, y) = gradientMagnitude;
  //          else if (gradientMagnitude <= magMax && gradientMagnitude > magMin)
  //            weak.at<float>(x, y) = gradientMagnitude;
  //          else
  //            suppress.at<float>(x, y) = gradientMagnitude;
  //        }
  //    }

  //  float magMax = 0.5, magMin = 0.1;
  //      Mat strong = Mat::zeros(magnitude.rows, magnitude.cols, CV_32F);
  inRange(magnitude, magMin, magMax, strong);

  return strong ;
}

Mat EdgeDetectors::PerwittEdgeDetector(Mat SrcImg)
{
  Point anchor = Point(-1, -1);
  double delta = 0;
  int ddepth = -1;
  Mat DstImg_X = Mat::zeros(SrcImg.rows, SrcImg.cols, CV_32F);
  Mat DstImg_Y= Mat::zeros(SrcImg.rows, SrcImg.cols, CV_32F);

  Mat Perwitt_X = (Mat_<double>(3,3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
  Mat Perwitt_Y = (Mat_<double>(3,3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);

  filter2D(SrcImg, DstImg_X, ddepth , Perwitt_X, anchor, delta, BORDER_DEFAULT );
  filter2D(SrcImg, DstImg_Y, ddepth , Perwitt_Y, anchor, delta, BORDER_DEFAULT );
  Mat PerwittImage = DstImg_X + DstImg_Y;

  return PerwittImage;
}


Mat EdgeDetectors::SobalEdgeDetector(Mat SrcImg)
{
  Point anchor =Point(-1, -1);
  double delta = 0;
  int ddepth = -1;
  Mat DstImg_X = Mat::zeros(SrcImg.rows, SrcImg.cols, CV_32F);
  Mat DstImg_Y= Mat::zeros(SrcImg.rows, SrcImg.cols, CV_32F);
  Mat Perwitt_X = (Mat_<double>(3,3) << -1, 0, 1, -2, 0, 1, -1, 0, 1);
  Mat Perwitt_Y = (Mat_<double>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
  filter2D(SrcImg, DstImg_X, ddepth , Perwitt_X, anchor, delta, BORDER_DEFAULT );
  filter2D(SrcImg, DstImg_Y, ddepth , Perwitt_Y, anchor, delta, BORDER_DEFAULT );
  Mat PerwittImage = DstImg_X + DstImg_Y;
  return PerwittImage;
}


Mat EdgeDetectors::RobertEdgeDetector(Mat SrcImg)
{
  Point anchor =Point(-1, -1);
  double delta = 0;
  int ddepth = -1;
  Mat DstImg_X = Mat::zeros(SrcImg.rows, SrcImg.cols, CV_32F);
  Mat DstImg_Y= Mat::zeros(SrcImg.rows, SrcImg.cols, CV_32F);
  Mat Perwitt_X = (Mat_<double>(2,2) << 1, 0, 0, -1);
  Mat Perwitt_Y = (Mat_<double>(2,2) << 0, 1, -1, 0);
  filter2D(SrcImg, DstImg_X, ddepth , Perwitt_X, anchor, delta, BORDER_DEFAULT );
  filter2D(SrcImg, DstImg_Y, ddepth , Perwitt_Y, anchor, delta, BORDER_DEFAULT );
  Mat PerwittImage = DstImg_X + DstImg_Y;
  return PerwittImage;
}
