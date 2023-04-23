#include "thresholding.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Thresholding::Thresholding()
{

}

Mat Thresholding::getOptimalThreshold(Mat InputImage, int max_iterations = 100, double threshold = 0.5){
      int threshold_value = 128;
      int delta = 1;
      int iterations = 0;
      int total_pixels = InputImage.rows * InputImage.cols;

      while (delta > threshold && iterations < max_iterations) {
          iterations++;
          int sum1 = 0, sum2 = 0, count1 = 0, count2 = 0;

          for (int i = 0; i < InputImage.rows; i++) {
              for (int j = 0; j < InputImage.cols; j++) {
                  if (InputImage.at<uchar>(i, j) <= threshold_value) {
                      sum1 += InputImage.at<uchar>(i, j);
                      count1++;
                  }
                  else {
                      sum2 += InputImage.at<uchar>(i, j);
                      count2++;
                  }
              }
          }

          int mean1 = sum1 / count1;
          int mean2 = sum2 / count2;

          int new_threshold_value = (mean1 + mean2) / 2;

          delta = abs(threshold_value - new_threshold_value);
          threshold_value = new_threshold_value;
      }
      cv::Mat output_image;
      cvtColor(InputImage, output_image, COLOR_BGR2GRAY);
      cv::threshold(output_image, output_image, threshold, 255, THRESH_BINARY);

      return output_image;
}

Mat Thresholding::Otsu(Mat InputImage)
{
    // Calculate the histogram of the image
    vector<int> hist(256, 0);
    for (int i = 0; i < InputImage.rows; i++)
    {
        for (int j = 0; j < InputImage.cols; j++)
        {
            int pixel_value = static_cast<int>(InputImage.at<uchar>(i, j));
            hist[pixel_value]++;
        }
    }

    // Calculate the optimal threshold value
    int threshold = 0;
    float max_variance = -1;
    for (int t = 0; t < 256; t++)
    {
        int num_pixels_low = 0;
        int num_pixels_high = 0;
        int sum_pixels_low = 0;
        int sum_pixels_high = 0;
        for (int i = 0; i < t; i++)
        {
            num_pixels_low += hist[i];
            sum_pixels_low += i * hist[i];
        }
        for (int i = t; i < 256; i++)
        {
            num_pixels_high += hist[i];
            sum_pixels_high += i * hist[i];
        }
        if (num_pixels_low == 0 || num_pixels_high == 0)
        {
            continue;
        }
        float mean_low = static_cast<float>(sum_pixels_low) / num_pixels_low;
        float mean_high = static_cast<float>(sum_pixels_high) / num_pixels_high;
        float variance = static_cast<float>(num_pixels_low) * static_cast<float>(num_pixels_high) * pow((mean_low - mean_high), 2);
        if (variance > max_variance)
        {
            max_variance = variance;
            threshold = t;
        }
    }

    cv::Mat output_image;
    cvtColor(InputImage, output_image, COLOR_BGR2GRAY);
    cv::threshold(output_image, output_image, threshold, 255, THRESH_BINARY);

    return output_image;
}



