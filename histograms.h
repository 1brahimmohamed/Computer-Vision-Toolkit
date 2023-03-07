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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;


class Histograms
{
public:
    Histograms();
    ~Histograms();
    void Histo(Mat image, int histogram[]);
    void cumHist(int histogram[], int cumhistogram[]);
    void histDisplay(int histogram[], const char* name);
    int calculateImageSize(Mat image);
    Mat equilization(Mat image, int histogram[], int cumhistogram[],int Sk[]);
    void equalizedHistogram(Mat image, int final[],int histogram[],int Sk[]);

    static Mat NormalizeImage(Mat inputImage);


private:
    int histogram[256];
    int cumhistogram[256];
    int final[256];
    int Sk[256];

};

#endif // HISTOGRAM_H
