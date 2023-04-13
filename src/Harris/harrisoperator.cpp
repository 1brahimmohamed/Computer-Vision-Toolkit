#include "harrisoperator.h"

using namespace cv;
using namespace std;
double HarrisOperator::threshold_level = 0.02;
HarrisOperator::HarrisOperator()
{

}
Mat HarrisOperator::XDerivative(Mat SrcImg)
{
   Mat GrediantImg_X(SrcImg.size(), CV_64F);
   Mat Sobel_X = (Mat_<double>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
   filter2D(SrcImg, GrediantImg_X,  CV_64F, Sobel_X);
   return GrediantImg_X;
}
Mat HarrisOperator::YDerivative(Mat SrcImg)
{
   Mat GrediantImg_Y(SrcImg.size(), CV_64F);
   Mat Sobel_Y = (Mat_<double>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
   filter2D(SrcImg, GrediantImg_Y,CV_64F,Sobel_Y);
   return GrediantImg_Y;
}
Mat HarrisOperator::convertToGrayScale(Mat SrcImg)
{
    Mat DstImg;
    cvtColor(SrcImg, DstImg, COLOR_BGR2GRAY);
    return DstImg;
}
void HarrisOperator::HarrisDetector(Mat SrcImg, Mat& R, double threshold_level)
{
    float k =0.05;
    //Spatial derivative calculation
    Mat Ix = XDerivative(SrcImg);
    Mat Iy = YDerivative(SrcImg);

    //calculate matrix elements
    Mat Ix2 = Ix.mul(Ix);
    Mat Iy2 = Iy.mul(Iy);
    Mat Ixy = Ix.mul(Iy);

    //gaussian Blur
    Mat Ix2_sum, Iy2_sum, IxIy_sum;
    blur(Ix2, Ix2_sum, Size(5, 5));
    blur(Iy2, Iy2_sum, Size(5, 5));
    blur(Ixy, IxIy_sum, Size(5, 5));

   //calculate harris response
    double A, B, C, d, t;
        for (int i = 0; i < SrcImg.rows; i++) {
            for (int j = 0; j < SrcImg.cols; j++) {
                A = Ix2_sum.at<double>(i, j);
                B = IxIy_sum.at<double>(i, j);
                C = Iy2_sum.at<double>(i, j);
                d = A * C - B * B;
                t = A + C;
                R.at<double>(i, j) = d - k * t * t;
            }
        }
//      normalize(R, R, 0, 255, NORM_MINMAX); //normalize the harris response to a specific range
      //apply non-max suppression
      double R_max;
      minMaxLoc(R, NULL, &R_max, NULL, NULL);
      double threshold = threshold_level * R_max;
      for (int i = 0; i < R.rows; i++) {
          for (int j = 0; j < R.cols; j++) {
              if (R.at<double>(i, j) < threshold) {
                  R.at<double>(i, j) = 0;
              }
          }
      }
    return ;
}
void HarrisOperator::getLocalMax(Mat R, Mat& localMax) {
    Mat dilated;
    dilate(R, dilated, Mat());
    compare(R, dilated, localMax, CMP_EQ);
    localMax = localMax - 255 + (dilated > 0);
    return;
}
Mat HarrisOperator::drawPointsToImg(Mat img, Mat localMax) {
    localMax.convertTo(localMax, CV_64F);
    for (int i = 0; i < localMax.rows; i++)
    {
        for (int j = 0; j < localMax.cols; j++)
        {
            if (localMax.at<double>(i, j) != 0) {
                Point p = Point(j, i);
                circle(img, p, 1, Scalar(0, 255, 0), -1);
            }
        }
    }
    return img;
}
Mat HarrisOperator::HarrisDrivingFunction(Mat SrcImg, double threshold_level)
{
    Mat GrayImg = convertToGrayScale(SrcImg);
    Mat R(GrayImg.size(), CV_64F);
    HarrisDetector(GrayImg, R, threshold_level);
    Mat localMax;
    getLocalMax(R, localMax);
    drawPointsToImg(SrcImg, localMax);
    return SrcImg;
}

