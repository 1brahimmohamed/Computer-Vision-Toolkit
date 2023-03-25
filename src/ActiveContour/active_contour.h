#ifndef ACTIVE_CONTOUR
#define ACTIVE_CONTOUR

#include <opencv2/opencv.hpp>
#include <cmath>
#include "cvector.h"
#include "image.h"
#include "utils.h"
#include <stdio.h>


double area_triangle(double a, double b, double c);
void circle_contour(cv::Point center, double radius, int numberOfPoints, int *x_cooridinates, int *y_cooridinates);
void draw_contour(cv::Mat Image, int numberOfPoints, int *x_cooridinates, int *y_cooridinates);
double contour_area(int numberOfPoints, int *x_cooridinates, int *y_cooridinates);
double contour_perimeter(int *x_points, int *y_points, int points_n);
cvector<cvector<int>> window_neighbours(int size);
cv::Mat greedy_contour(img::Image source, int iterations ,float alpha, float beta, float gamma,int* x_points, int* y_points, int points_n, int window_size, bool plot);
cv::Mat active_contour(cv::Mat mat,int iterations, float alpha, float beta, float gamma, int points, int radius, int centerX, int centerY);
std::vector<int> chainCode(int* x_points, int* y_points, int points_n);
//std::vector<int> get_8_chain_code(int* x_points, int* y_points, int points_n);
std::vector<std::pair<int, int>> chain_code(std::vector<int> x, std::vector<int> y);
#endif
