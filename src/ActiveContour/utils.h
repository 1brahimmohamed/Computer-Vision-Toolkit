#ifndef UTILS_H
#define UTILS_H

#include "cvector.h"
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <opencv2/opencv.hpp>

double points_distance(int x1, int y1, int x2, int y2);
cvector<cvector<double>> gaussian_kernel(int size, double std);
int count_edges(cv::Mat img,cv::Mat test);
void draw_circle(cv::Mat img,int x,int y, int r);
void RGBtoHSV(float fR, float fG, float fB, float *fH, float *fS, float *fV);
void HSVtoRGB(float *fR, float *fG, float *fB, float fH, float fS, float fV);
#endif
