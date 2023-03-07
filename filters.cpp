#include <vector>
#include <QDebug>
#include <algorithm>
#include <queue>

#include "filters.h"

Filters::Filters()
{

}

Filters::~Filters()
{

}


/**
 * @brief filters image using the Average filter method
 * @param inputImage {cv::Mat} - input image
 * @param kernelSize {int} - size of the used kernel
 * @return filteredImage {cv::Mat}
 */
Mat Filters::applyAverageFilter(Mat inputImage, int kernelSize){

  // make a copy of the input image
  Mat outputImage = inputImage.clone();

  // image size
  int rows = inputImage.rows;
  int cols = inputImage.cols;

  /**
   * first loop iterats over rows, second loop iterats ofver columns
   * the inner two loops calculates the sum of the pixels around this pixel with the size
   * of the kernel to get the averge
   */

  for (int i = 0; i < rows; i++)
  {
      for (int j = 0; j < cols; j++)
      {
          Vec3i sum(0, 0, 0);
          int count = 0;
          for (int k = -kernelSize / 2; k <= kernelSize / 2; k++)
          {
              for (int l = -kernelSize / 2; l <= kernelSize / 2; l++)
              {
                  if (i + k >= 0 && i + k < rows && j + l >= 0 && j + l < cols)
                  {
                      sum += inputImage.at<Vec3b>(i + k, j + l);
                      count++;
                  }
              }
          }
          // value of the pixel is the average
          outputImage.at<Vec3b>(i, j) = sum / count;
      }
  }
  return outputImage;
}



/**
 * @brief Filters image using the guassian filter method
 * @param inputImage {cv::Mat} - input image
 * @param kernelSize {int} - size of the used kernel
 * @param sigma {float} - standard deviation
 * @return filteredImage {cv::Mat}
 */
Mat Filters::applyGaussianFilter(Mat inputImage, int kernelSize, float sigma){
   // Split input image into its color channels
   std::vector<Mat> channels;
   split(inputImage, channels);
   vector<vector<double>> kernel = computeGuassianKernel(kernelSize, sigma);

   // Apply Gaussian filter on each color channel
   vector<Mat> filteredChannels(channels.size());

   for (int k = 0; k < channels.size(); k++)
   {
       Mat filteredChannel = channels[k].clone();
       int rows = channels[k].rows;
       int cols = channels[k].cols;
       for (int i = kernelSize / 2; i < rows - kernelSize / 2; i++)
       {
           for (int j = kernelSize / 2; j < cols - kernelSize / 2; j++)
           {
               double sum = 0;
               for (int x = -kernelSize / 2; x <= kernelSize / 2; x++)
               {
                   for (int y = -kernelSize / 2; y <= kernelSize / 2; y++)
                   {
                       sum += kernel[x + kernelSize / 2][y + kernelSize / 2] * channels[k].at<uchar>(i + x, j + y);
                   }
               }
               filteredChannel.at<uchar>(i, j) = static_cast<uchar>(sum);
           }
       }
       filteredChannels[k] = filteredChannel;
   }

   Mat outputImage;
   merge(filteredChannels, outputImage);

   return outputImage;
}




/**
 * @brief Filters image using the Median method
 * @param kernelSize {int} - size of the kernel
 * @param sigma {float} - standard deviation
 * @return kernel {vector<vector<double>>}
 */
vector<vector<double>> Filters::computeGuassianKernel(int kernelSize, float sigma){

  // Compute Gaussian kernel
  vector<vector<double>> kernel(kernelSize,vector<double>(kernelSize, 0.0));
  double sum = 0;

  for (int i = -kernelSize / 2; i <= kernelSize / 2; i++)
  {
      for (int j = -kernelSize / 2; j <= kernelSize / 2; j++)
      {
          kernel[i + kernelSize / 2][j + kernelSize / 2] = exp(-(i * i + j * j) / (2 * sigma * sigma));
          sum += kernel[i + kernelSize / 2][j + kernelSize / 2];
      }
  }

  for (int i = 0; i < kernelSize; i++)
  {
      for (int j = 0; j < kernelSize; j++)
      {
          kernel[i][j] /= sum;
      }
  }

  return kernel;
}




// ------------------------------------ OpenCV Functions  -----------------------------------------//

Mat Filters::OpenCVAvgFilter(Mat inputImage, int kernelSize){
   Mat outputImage;
   Mat kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize*kernelSize);

   // Apply filter on input image
   filter2D(inputImage, outputImage, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT);

   return outputImage;
}

Mat Filters::OpenCVGuassianFilter(Mat inputImage, int kernelSize, float sigma){
  Mat outputImage;
  GaussianBlur(inputImage, outputImage, Size(kernelSize, kernelSize), sigma);
  return outputImage;
}

Mat Filters::OpenCVMedianFilter(Mat inputImage, int kernelSize){
  Mat outputImage;
  medianBlur(inputImage, outputImage, kernelSize);
  return outputImage;
}
