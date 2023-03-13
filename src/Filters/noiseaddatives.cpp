#include "noiseaddatives.h"

#include <cstdint>
#include <iostream>
using namespace cv;
using namespace std;
NoiseAddatives::NoiseAddatives()
{

}
NoiseAddatives::~NoiseAddatives()
{

}
inline unsigned char NoiseAddatives::Clamp(int n)
{
  n = n>255 ? 255 : n;
  return n<0 ? 0 : n;
}

Mat NoiseAddatives::GaussianNoise(const Mat SrcImg, Mat &DstImg,double Mean=0.0, double StdDev=10.0)
{   //check for the provided image
  if(SrcImg.empty())
    {
      std::cout<<"[Error]! Input Image Empty!";
    }
  // create a new Mat object with the src img size and its type is 16 bit signed 3 channel
  Mat mGaussian_noise = Mat(SrcImg.size(),CV_16SC3);
  //generate uniformaly distributed and random noise to add later with specific mean & std
  randn(mGaussian_noise,Scalar::all(Mean),Scalar::all(StdDev));
  //gaussian noise + pixel value
  for (int Rows = 0; Rows < SrcImg.rows; Rows++)
    {
      for (int Cols = 0; Cols < SrcImg.cols; Cols++)
        {
          Vec3b Source_Pixel= SrcImg.at<Vec3b>(Rows,Cols);
          Vec3b &Des_Pixel= DstImg.at<Vec3b>(Rows,Cols);
          Vec3s Noise_Pixel= mGaussian_noise.at<Vec3s>(Rows,Cols);
          for (int i = 0; i < 3; i++)
            {
              int Dest_Pixel= Source_Pixel.val[i] + Noise_Pixel.val[i];
              Des_Pixel.val[i]= Clamp(Dest_Pixel);
            }
        }
    }
  return DstImg;
}
Mat NoiseAddatives::SaltAndPepperNoise(Mat SrcImg)
{
  Mat ResultImg = SrcImg.clone();
    int r = 15;
      for (int i = 0; i < ResultImg.rows; i++) {
          for (int k = 0; k <ResultImg.cols; k++) {
              int random = rand() % r + 1;
              if (random == 1) {
                  ResultImg.at<uchar>(i, k) = 255;
                }
              if (random == 2) {
                  ResultImg.at<uchar>(i, k) = 0;
                }

            }

        }
        return ResultImg;
}

