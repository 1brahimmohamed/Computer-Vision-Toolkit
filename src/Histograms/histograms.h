/******************************************************************************
 *
 * File Name: histograms.h
 * Description: Header file for Histograms Class.
 * Authors: Marina Nasser & Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:39
 *
 *******************************************************************************/

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class Histograms
{
public:
    Histograms();
    ~Histograms();

    static vector<int> Histo(Mat image);

    static vector<int> cumHist(vector<int> histogram);
    static void histDisplay(int histogram[], const char* name);
    static int  calculateImageSize(Mat image);
    static vector<int> calcuateScale(Mat image,vector<int> cumhistogram);

    static Mat  equilization(Mat image, vector<int> Sk);
    static vector<int> equalizedHistogram(Mat image, vector<int> histogram, vector<int> sk);

    static Mat NormalizeImage(Mat inputImage);
    static Mat normalizeMat(Mat inputMat, double minVal, double maxVal);

    static Mat plotRGBHistogramPDF(Mat img);
    static Mat plotRGBHistogramCDF(Mat img);
};

#endif // HISTOGRAM_H
