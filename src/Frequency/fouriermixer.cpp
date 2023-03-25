/******************************************************************************
 *
 * File Name: fouriermixer.cpp
 * Description: Source file for Fourier Domain Mainpulation Class including fft shift,
 * DFT calculations & filtering using frequncy domain
 * Author(s): Mahmoud Yaser & Maye Khaled
 * Last Modified: 3 Mar 23 - 20:26
 *
 *******************************************************************************/


#include "fouriermixer.h"
#include <QDebug>
#include <iostream>

FourierMix::FourierMix()
{

}

FourierMix::~FourierMix()
{

}

// Standard Size of the image is 500 * 500 Pixel
Size2i imageSize = Size(500,500);

/**
 * @brief function to apply Fast Fourier Transform Shift
 * @param input_img
 * @param output_img
 */
void FourierMix::fftshift(const Mat &input_img, Mat &output_img)
{
  output_img = input_img.clone();
  int cx = output_img.cols / 2;
  int cy = output_img.rows / 2;
  Mat q1(output_img, Rect(0, 0, cx, cy));
  Mat q2(output_img, Rect(cx, 0, cx, cy));
  Mat q3(output_img, Rect(0, cy, cx, cy));
  Mat q4(output_img, Rect(cx, cy, cx, cy));

  Mat temp;
  q1.copyTo(temp);
  q4.copyTo(q1);
  temp.copyTo(q4);
  q2.copyTo(temp);
  q3.copyTo(q2);
  temp.copyTo(q3);
}

/**
 * @brief function to calculate Discrete Fourier Transform
 * @param scr {cv::Mat &} - source image
 * @param dst {cv::Mat &} - distnation image
 */
void FourierMix::calculateDFT(Mat &scr, Mat &dst)
{
  // define mat consists of two mat, one for real values and the other for complex values
  Mat planes[] = { scr, Mat::zeros(scr.size(), CV_32F) };
  Mat complexImg;
  merge(planes, 2, complexImg);

  dft(complexImg, complexImg);
  dst = complexImg;
}

/**
 * @brief function to construct the ####
 * @param scr {cv::Mat &} - source image
 * @param dst {cv::Mat &} - distnation image
 * @param type {String} - type of the filter
 * @param D0 {float} - diameter of the circle
 */
void FourierMix::construct_H(Mat &scr, Mat &dst, String type, float D0)
{
  Mat H(scr.size(), CV_32F, Scalar(1));
  float D = 0;
  if (type == "Ideal Low Pass")
    {
      for (int u = 0; u < H.rows; u++)
        {
          for (int  v = 0; v < H.cols; v++)
            {
              D = sqrt((u - scr.rows / 2)*(u - scr.rows / 2) + (v - scr.cols / 2)*(v - scr.cols / 2));
              if (D > D0)
                {
                  H.at<float>(u, v) = 0;
                }
            }
        }
      dst = H;
    }
  else if (type == "Gaussian")
    {

      for (int  u = 0; u < H.rows; u++)
        {
          for (int v = 0; v < H.cols; v++)
            {
              D = sqrt((u - scr.rows / 2)*(u - scr.rows / 2) + (v - scr.cols / 2)*(v - scr.cols / 2));
              H.at<float>(u, v) = exp(-D*D / (2 * D0*D0));
            }
        }
      dst = H;
    }
  else if (type == "Ideal High Pass")
    {

      for (int u = 0; u < H.rows; u++)
        {
          for (int  v = 0; v < H.cols; v++)
            {
              D = sqrt((u - scr.rows / 2)*(u - scr.rows / 2) + (v - scr.cols / 2)*(v - scr.cols / 2));
              if (D <= D0)
                {
                  H.at<float>(u, v) = 0;
                }
            }
        }
      dst = H;
    }
}

/**
 * @brief FourierMix::filtering
 * @param scr {cv::Mat &} - source image
 * @param dst {cv::Mat &} - distnation image
 * @param H   {cv::Mat &} - ###
 */
void FourierMix::filtering(Mat &scr, Mat &dst, Mat &H)
{
  fftshift(H, H);
  Mat planesH[] = { cv::Mat_<float>(H.clone()), cv::Mat_<float>(H.clone()) };

  Mat planes_dft[] = { scr, Mat::zeros(scr.size(), CV_32F) };
  split(scr, planes_dft);

  Mat planes_out[] = { Mat::zeros(scr.size(), CV_32F), Mat::zeros(scr.size(), CV_32F) };
  planes_out[0] = planesH[0].mul(planes_dft[0]);
  planes_out[1] = planesH[1].mul(planes_dft[1]);

  merge(planes_out, 2, dst);

}

/**
 * @brief function to apply frequency domain filter
 * @param imgIn {cv::Mat}
 * @param filter_type {String} - type of the filter
 * @param D0 {float} - diameter of the circle
 * @return imgOut {cv::Mat}
 */
Mat FourierMix::apply_filter(Mat imgIn, String filter_type, float D0){
  Mat imgOut;

  cvtColor(imgIn, imgIn, COLOR_BGR2GRAY);

  resize(imgIn, imgIn, imageSize);

  imgIn.convertTo(imgIn, CV_32F);

  // DFT
  Mat DFT_image;
  FourierMix::calculateDFT(imgIn, DFT_image);

  // construct H
  Mat H;
  FourierMix::construct_H(imgIn, H, filter_type, D0);

  // filtering
  Mat complexIH;
  FourierMix::filtering(DFT_image, complexIH, H);

  // IDFT
  dft(complexIH, imgOut, DFT_INVERSE | DFT_REAL_OUTPUT);

  normalize(imgOut, imgOut, 0, 1, NORM_MINMAX);


  return imgOut;
}


/**
 * @brief function to add 2 images intensities
 * @param imgLow  {cv::Mat} - Low Pass Image
 * @param imgHigh {cv::Mat} - High Pass Image
 * @return imgHybrid {cv::Mat} - Mixed Image
 */
Mat FourierMix::mix_images(Mat imgLow, Mat imgHigh){
  Mat imgHybrid;
  imgHybrid = imgLow + imgHigh;
  return imgHybrid;
}
