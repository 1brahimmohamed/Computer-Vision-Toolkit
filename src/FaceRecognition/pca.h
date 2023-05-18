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

    static Mat calculateCovarianceMatrix(Mat normalizedImages);
    static Mat computePca(Mat covariance_matrix, Mat NormalizedDataMat);
    static Mat computeWeights(Mat EigenFacesMat, Mat NormalizedImag);

private:

};

#endif // PCA_H
