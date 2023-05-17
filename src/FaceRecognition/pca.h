#ifndef PCA_H
#define PCA_H

#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

class Pca
{
public:
  Pca();

private:
  Mat CalculateCovarianceMatrix(Mat normalizedImages);
  Mat computeEign(Mat covarMat, Mat& eigenVals);
};

#endif // PCA_H
