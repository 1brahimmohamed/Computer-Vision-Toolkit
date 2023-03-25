/******************************************************************************
 *
 * File Name: noiseaddivates.cpp
 * Description: Source file for Noise Addatives Class including Unifrom,
 * Guassian & Salt-Pepper noise
 * Author(s): Omina Sayed
 * Last Modified: 3 Mar 23 - 23:11
 *
 *******************************************************************************/


#include "noiseaddatives.h"
#include <QDebug>

#include <cstdint>
#include <iostream>
#include <random>


using namespace cv;
using namespace std;
NoiseAddatives::NoiseAddatives()
{

}
NoiseAddatives::~NoiseAddatives()
{

}

/**
 * @brief Inline function for calculating Clamp
 * @param n {int} - number
 * @return {unsigned char}
 */
inline unsigned char NoiseAddatives::Clamp(int n)
{
  n = n>255 ? 255 : n;
  return n<0 ? 0 : n;
}

/**
 * @brief Function to add Gaussian Noise on Image
 * @param SrcImg {cv::Mat}
 * @param Mean {double} - mean of the guassian distribution
 * @param StdDev {double} - standart devation of the guassian distribution
 * @return DstImg {cv::Mat}
 */
Mat NoiseAddatives::GaussianNoise(const Mat SrcImg, double Mean=0.0, double StdDev=10.0)
{
  //check for the provided image
  Mat DstImg = SrcImg.clone();

  if(SrcImg.empty())
    {
      std::cout<<"[Error]! Input Image Empty!";
    }

  // create a new Mat object with the src img size and its type is 16 bit signed 3 channel
  Mat mGaussian_noise = Mat(SrcImg.size(),CV_16SC3);
  //generate uniformaly distributed and random noise to add later with specific mean & std
  randn(mGaussian_noise,Scalar::all(Mean),Scalar::all(StdDev));
  //gaussian noise + pixel value

  int Dest_Pixel = 0;

  for (int Rows = 0; Rows < SrcImg.rows; Rows++)
    {
      for (int Cols = 0; Cols < SrcImg.cols; Cols++)
        {
          Vec3b Source_Pixel= SrcImg.at<Vec3b>(Rows,Cols);
          Vec3b &Des_Pixel = DstImg.at<Vec3b>(Rows,Cols);
          Vec3s Noise_Pixel= mGaussian_noise.at<Vec3s>(Rows,Cols);

          for (int i = 0; i < 3; i++)
            {
              Dest_Pixel = Source_Pixel.val[i] + Noise_Pixel.val[i];
              Des_Pixel.val[i] = Clamp(Dest_Pixel);
            }
        }
    }
  return DstImg;
}


/**
 * @brief Function to add Salt & Pepper Noise on Image
 * @param SrcImg {cv::Mat}
 * @return resultImg {cv::Mat}
 */
Mat NoiseAddatives::SaltAndPepperNoise(Mat SrcImg)
{
  Mat resultImg  = SrcImg.clone();
  int r = 15;
  int random = 0;

  for (int i = 0; i < resultImg.rows; i++) {

      for (int k = 0; k < resultImg.cols; k++) {

        random = rand() % r + 1;

        if (random == 1)
          resultImg.at<Vec3b>(i, k) = Vec3b(255,0,0);

        else if (random == 2)
          resultImg.at<Vec3b>(i, k) = Vec3b(0,255,0);

        else if (random == 3)
          resultImg.at<Vec3b>(i, k) = Vec3b(0,0,255);
      }
    }
  return resultImg;
}

