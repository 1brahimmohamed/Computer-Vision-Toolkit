/******************************************************************************
 *
 * File Name: histograms.cpp
 * Description: Source file for Histograms Class.
 * Authors: Marina Nasser & Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:39
 *
 *******************************************************************************/


#include "histograms.h"


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
    int hist_w = 512; int hist_h = 400;
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

    // display histogram
//     QChart *chart = new QChart();
//     chart->addSeries(histImage);
//     chart->setTitle("Simple barchart example");
//     chart->setAnimationOptions(QChart::SeriesAnimations);
    namedWindow(name, CV_WINDOW_AUTOSIZE);
    imshow(name, histImage);
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

void Histograms:: equalizedHistogram(Mat image, int final[], int histogram[],int Sk[]){
    // Calculate the probability of each intensity
    float PrRk[256];
    for(int i = 0; i < 256; i++)
    {
        PrRk[i] = (double)histogram[i] / 512; //el mfrod bdal 512 dy size el image
    }
    // Generate the equlized histogram
    float PsSk[256];
    for(int i = 0; i < 256; i++)
    {
        PsSk[i] = 0;
    }

    for(int i = 0; i < 256; i++)
    {
        PsSk[Sk[i]] += PrRk[i];
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
