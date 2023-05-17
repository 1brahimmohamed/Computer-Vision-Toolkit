#include "pca.h"
using namespace cv;
using namespace std;
Pca::Pca()
{

}

Mat Pca::CalculateCovarianceMatrix(Mat normalizedImages)
{
  // initialize the covariance matrix
  // get the transpose of the normalized images matrix
  Mat normalizedImagesT;
  transpose(normalizedImages, normalizedImagesT);
//  qDebug() << normalizedImages.rows << normalizedImages.cols;
//  qDebug() << normalizedImagesT.rows << normalizedImagesT.cols;
  Mat covarianceMatrix, mu;
  // calculate the covariance matrix
  calcCovarMatrix(normalizedImages, covarianceMatrix, mu, COVAR_NORMAL | COVAR_ROWS);
  covarianceMatrix /= static_cast<double>(normalizedImages.cols - 1);
//  qDebug() << "Covariance Matrix Shape: " << covarianceMatrix.rows <<  covarianceMatrix.cols;
  return covarianceMatrix;
}

Mat Pca::computePca(Mat covariance_matrix, Mat NormalizedDataMat)
{
    int num_components = 50;
    // Compute the eigenvectors of the covariance matrix
    Mat eigenvalues, eigenvectors;
    eigen(covariance_matrix, eigenvalues, eigenvectors);
    Mat eigenfaces_mat = eigenvectors.t() * NormalizedDataMat.t();
    // Normalize the eigenfaces
    for (int i = 0; i < eigenfaces_mat.rows; i++)
    {
        normalize(eigenfaces_mat.row(i), eigenfaces_mat.row(i), 0, 255, NORM_MINMAX);
    }
    // Select the top num_components eigenfaces
    Mat eigenfaces = eigenfaces_mat.rowRange(0, num_components);
    return eigenfaces;
}
Mat Pca::ComputeWeights(Mat EigenFacesMat, Mat NormalizedImag)
{

    Mat weights = EigenFacesMat.t() * NormalizedImag.t();
    return weights;
}
