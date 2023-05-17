#ifndef PCA_H
#define PCA_H
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include<cmath>
#include<cstdint>
#include <random>
using namespace std;
using namespace cv;

class Pca
{
public:
    Pca();
private:
  static Mat CalculateCovarianceMatrix(Mat normalizedImages);
  static Mat computePca(Mat covariance_matrix, Mat NormalizedDataMat);
  static Mat ComputeWeights(Mat EigenFacesMat, Mat NormalizedImag);
  static Mat ComputeProjection(Mat EigenFacesMat, Mat WeightsMat);
};

#endif // PCA_H
