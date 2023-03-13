/******************************************************************************
 *
 * File Name: histograms.cpp
 * Description: Source file for Histograms Class.
 * Authors: Marina Nasser & Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:39
 *
 *******************************************************************************/


#include "histograms.h"
#include <vector>
#include <QDebug>

Histograms::Histograms()
{

}

Histograms::~Histograms()
{

}

void Histograms:: Histo(Mat image, int histogram[])
{

  // initialize all intensity values to 0
  for(int i = 0; i < 256; i++)
    {
      histogram[i] = 0;
    }

  // calculate the no of pixels for each intensity values
  for(int y = 0; y < image.rows; y++)
    for(int x = 0; x < image.cols; x++)
      histogram[(int)image.at<uchar>(y,x)]++;

}

void Histograms:: cumHist(int histogram[], int cumhistogram[])
{
  cumhistogram[0] = histogram[0];

  for(int i = 1; i < 256; i++)
    {
      cumhistogram[i] = histogram[i] + cumhistogram[i-1];
    }
}

void Histograms:: histDisplay(int histogram[], const char* name)
{
  int hist[256];
  for(int i = 0; i < 256; i++)
    {
      hist[i]=histogram[i];
    }
  // draw the histograms
  int hist_w = 512; int hist_h = 256;
  int bin_w = cvRound((double) hist_w/256);

  Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

  // find the maximum intensity element from histogram
  int max = hist[0];
  for(int i = 1; i < 256; i++){
      if(max < hist[i]){
          max = hist[i];
        }
    }

  // normalize the histogram between 0 and histImage.rows

  for(int i = 0; i < 256; i++){
      hist[i] = ((double)hist[i]/max)*histImage.rows;
    }


  // draw the intensity line for histogram
  for(int i = 0; i < 256; i++)
    {
      line(histImage, Point(bin_w*(i), hist_h),Point(bin_w*(i), hist_h - hist[i]),Scalar(0,0,0), 1, 8, 0);
    }
}

int Histograms:: calculateImageSize(Mat image){
  int size = image.rows * image.cols;
  return size;
}

Mat Histograms:: equilization(Mat image, int histogram[], int cumhistogram[], int Sk[]){

  int size = calculateImageSize(image);
  float alpha = 255.0/size;


  // Scale the histogram

  for(int i = 0; i < 256; i++)
    {
      Sk[i] = cvRound((double)cumhistogram[i] * alpha);
    }


  Mat new_image = image.clone();

  for(int y = 0; y < image.rows; y++)
    for(int x = 0; x < image.cols; x++)
      new_image.at<uchar>(y,x) = saturate_cast<uchar>(Sk[image.at<uchar>(y,x)]);

  return new_image;
}

void Histograms:: equalizedHistogram(Mat image, int final[], int histogram[],int sk[]){


  // Calculate the probability of each intensity
  float PDF[256];
  for(int i = 0; i < 256; i++)
    {
      PDF[i] = (double)histogram[i] / calculateImageSize(image);
    }



  // Generate the equlized histogram
  float PsSk[256]={0};

  //new level
  for(int i = 0; i < 256; i++)
    {
      PsSk[sk[i]] += PDF[i];
    }


  for(int i = 0; i < 256; i++)
    final[i] = cvRound(PsSk[i]*255);

}
Mat Histograms::NormalizeImage(Mat inputImage){

  vector<Mat> bgr_channels;
  split(inputImage, bgr_channels);

  // Normalize each color channel separately
  vector<Mat> normalized_bgr_channels;
  for (int c = 0; c < bgr_channels.size(); c++) {
      // Find the minimum and maximum pixel values in the color channel
      double channel_min_val, channel_max_val;
      minMaxLoc(bgr_channels[c], &channel_min_val, &channel_max_val);

      // Normalize the color channel
      Mat normalized_channel = (bgr_channels[c] - channel_min_val) / (channel_max_val - channel_min_val);
      normalized_bgr_channels.push_back(normalized_channel);
    }

  // Merge normalized color channels back into RGB image
  Mat normalized_rgb_img;
  merge(normalized_bgr_channels, normalized_rgb_img);

  // return the normalized RGB image
  return normalized_rgb_img;
}

Mat Histograms::normalizeMat(cv::Mat inputMat, double minVal, double maxVal)
{
  // Create an outputMat of the same size and type as the inputMat
  Mat outputMat(inputMat.rows, inputMat.cols, inputMat.type());

  switch (inputMat.type())
    {
    case CV_8UC1: // Grayscale image
      {
        qDebug("CASe 1");
        // Calculate the current min and max values in the inputMat
        uchar currentMinVal = inputMat.at<uchar>(0, 0);
        uchar currentMaxVal = inputMat.at<uchar>(0, 0);

        for (int row = 0; row < inputMat.rows; ++row) {
            for (int col = 0; col < inputMat.cols; ++col) {
                uchar currentVal = inputMat.at<uchar>(row, col);
                if (currentVal < currentMinVal) {
                    currentMinVal = currentVal;
                  }
                if (currentVal > currentMaxVal) {
                    currentMaxVal = currentVal;
                  }
              }
          }

        // Normalize the inputMat to the specified range
        for (int row = 0; row < inputMat.rows; ++row) {
            for (int col = 0; col < inputMat.cols; ++col) {
                uchar currentVal = inputMat.at<uchar>(row, col);
                uchar normalizedVal = static_cast<uchar>((currentVal - currentMinVal) * (maxVal - minVal) / (currentMaxVal - currentMinVal) + minVal);
                outputMat.at<uchar>(row, col) = normalizedVal;
              }
          }

        break;
      }
    case CV_8UC3: // BGR color image
      {
        qDebug("CASe 2");
        // Separate the inputMat into its 3 channels
        std::vector<cv::Mat> inputChannels;
        cv::split(inputMat, inputChannels);

        // Normalize each channel of the inputMat to the specified range using basic arithmetic operations
        for (int channel = 0; channel < 3; ++channel) {
            // Calculate the current min and max values in the inputMat channel
            uchar currentMinVal = inputChannels[channel].at<uchar>(0, 0);
            uchar currentMaxVal = inputChannels[channel].at<uchar>(0, 0);

            for (int row = 0; row < inputMat.rows; ++row) {
                for (int col = 0; col < inputMat.cols; ++col) {
                    uchar currentVal = inputChannels[channel].at<uchar>(row, col);
                    if (currentVal < currentMinVal) {
                        currentMinVal = currentVal;
                      }
                    if (currentVal > currentMaxVal) {
                        currentMaxVal = currentVal;
                      }
                  }
              }

            // Normalize the inputMat channel to the specified range using basic arithmetic operations
            for (int row = 0; row < inputMat.rows; ++row) {
                for (int col = 0; col < inputMat.cols; ++col) {
                    uchar currentVal = inputChannels[channel].at<uchar>(row, col);
                    uchar normalizedVal = static_cast<uchar>((currentVal - currentMinVal) * (maxVal - minVal) / (currentMaxVal - currentMinVal) + minVal);
                    outputMat.at<cv::Vec3b>(row, col)[channel] = normalizedVal;
                  }
              }
          }
        break;
      }
    }

  return outputMat;
}
