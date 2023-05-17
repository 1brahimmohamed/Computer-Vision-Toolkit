#include "pca.h"

Pca::Pca()
{

}

Mat Pca::CalculateCovarianceMatrix(Mat normalizedImages){
  // initialize the covariance matrix

  // get the transpose of the normalized images matrix
  Mat normalizedImagesT;
  transpose(normalizedImages, normalizedImagesT);

  qDebug() << normalizedImages.rows << normalizedImages.cols;
  qDebug() << normalizedImagesT.rows << normalizedImagesT.cols;


  Mat covarianceMatrix, mu;

  // calculate the covariance matrix
  cv::calcCovarMatrix(normalizedImages, covarianceMatrix, mu, COVAR_NORMAL | cv::COVAR_ROWS);

  covarianceMatrix /= static_cast<double>(normalizedImages.cols - 1);

  qDebug() << "Covariance Matrix Shape: " << covarianceMatrix.rows <<  covarianceMatrix.cols;

  return covarianceMatrix;
}

Mat Pca::computeEign(Mat covarianceMatrix, Mat& eigenVals){
//  Mat eigenVectors;

//  eigen(covarianceMatrix,eigenVals ,eigenVectors);

//  return oneMatSortedEigenVectors;
}
