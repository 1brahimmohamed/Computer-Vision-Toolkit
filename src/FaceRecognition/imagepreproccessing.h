#ifndef IMAGEPREPROCCESSING_H
#define IMAGEPREPROCCESSING_H

#include <QString>
#include <QDir>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

class ImagePreproccessing
{
public:
  ImagePreproccessing();
  void DetectFacesInFolder();
  vector<QString> readImagesPath();
  Mat FlattenImages(vector<Mat> images);
  Mat normalizeImages(Mat flattenImages, Mat &sentMean);
  Mat CalculateCovarianceMatrix(Mat normalizedImages);
  Mat computeEign(Mat covarMat, Mat& eigenVals);
private:
  QDir currentDir;
  QString classiferFilePath;
  CascadeClassifier cascade;

  QString inputFolderPath;
  QString outputFolderPath;
};

#endif // IMAGEPREPROCCESSING_H
