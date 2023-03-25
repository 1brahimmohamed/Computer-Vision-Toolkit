/******************************************************************************
 *
 * File Name: fouriermixer.h
 * Description: Header file for Fourier Domain Mainpulation Class including fft shift,
 * DFT calculations & filtering using frequncy domain
 * Author(s): Mahmoud Yaser & Maye Khaled
 * Last Modified: 3 Mar 23 - 20:26
 *
 *******************************************************************************/

#ifndef FOURIERMIXER_H
#define FOURIERMIXER_H

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;


class FourierMix
{
public:
    FourierMix();
    ~FourierMix();

    static void fftshift(const Mat &input_img, Mat &output_img);
    static void calculateDFT(Mat &scr, Mat &dst);
    static void construct_H(Mat &scr, Mat &dst, String type, float D0);
    static void filtering(Mat &scr, Mat &dst, Mat &H);
    static Mat apply_filter(Mat imgIn, String filter_type, float D0);
    static Mat mix_images(Mat imgLow, Mat imgHigh);
};

#endif // FOURIERMIXER_H
