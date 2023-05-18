#include "QDebug"
#include "pca.h"
#include <src/FaceRecognition/imagepreproccessing.h>

using namespace cv;
using namespace std;
Pca::Pca()
{

}

Mat Pca::calculateCovarianceMatrix(Mat normalizedImages)
{
  // initialize the covariance matrix
  // get the transpose of the normalized images matrix
  Mat normalizedImagesT;

  transpose(normalizedImages, normalizedImagesT);
  //  qDebug() << normalizedImages.rows << normalizedImages.cols;
  //  qDebug() << normalizedImagesT.rows << normalizedImagesT.cols;
  Mat covarianceMatrix, mu;

  // calculate the covariance matrix
  calcCovarMatrix(normalizedImagesT, covarianceMatrix, mu, COVAR_NORMAL | COVAR_ROWS);
  covarianceMatrix /= static_cast<double>(normalizedImages.cols - 1);

  //  qDebug() << "Covariance Matrix Shape: " << covarianceMatrix.rows <<  covarianceMatrix.cols;
  return covarianceMatrix;
}

Mat Pca::computePca(Mat covariance_matrix, Mat NormalizedDataMat)
{
  int num_components = 10;
  // Compute the eigenvectors of the covariance matrix
  Mat eigenvalues, eigenvectors;
  eigen(covariance_matrix, eigenvalues, eigenvectors);

  Mat eigenfaces_mat;
  cv::Mat eigenvectors_transpose = eigenvectors.t();
  cv::Mat normalized_data_transpose = NormalizedDataMat.t();

  // Convert the matrix types if necessary
  eigenvectors_transpose.convertTo(eigenvectors_transpose, CV_64FC1);
  normalized_data_transpose.convertTo(normalized_data_transpose, CV_64FC1);
  eigenfaces_mat =  normalized_data_transpose * eigenvectors_transpose;


  // Normalize the eigenfaces
  for (int i = 0; i < eigenfaces_mat.rows; i++)
    {
      normalize(eigenfaces_mat.row(i), eigenfaces_mat.row(i), 0, 255, NORM_MINMAX);
    }

  // Select the top num_components eigenfaces
  Mat eigenfaces = eigenfaces_mat.rowRange(0, num_components);

  return eigenfaces;
}


Mat Pca::computeWeights(Mat EigenFacesMat, Mat NormalizedImag)
{
  Mat weights;
  cv::Mat eigenfaces_transpose = EigenFacesMat.t();
  cv::Mat normalized_transpose = NormalizedImag.t();

  // Convert the matrix types if necessary
  eigenfaces_transpose.convertTo(eigenfaces_transpose, CV_32F);
  normalized_transpose.convertTo(normalized_transpose, CV_32F);

  weights = normalized_transpose*eigenfaces_transpose;
  return weights;
}
