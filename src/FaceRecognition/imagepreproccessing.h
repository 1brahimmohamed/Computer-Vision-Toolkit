#ifndef IMAGEPREPROCCESSING_H
#define IMAGEPREPROCCESSING_H

#include <QString>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

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
  vector<QString> readImagesPath(QString inputFolder, vector<QString> &labels);
  Mat FlattenImages(vector<Mat> images);
  Mat normalizeImages(Mat flattenImages, Mat &sentMean);
  QString getLabelFromImagePath(QString imagePath);
  Mat imageNormalization(Mat image, Mat mean);
  void saveMatricesToJson(const cv::Mat weights, const cv::Mat mean, const QString filePath);
  void loadMatricesFromJson(cv::Mat& weights, cv::Mat& mean, const QString filePath);

private:
  QDir currentDir;
  QString classiferFilePath;
  CascadeClassifier cascade;

  QString inputFolderPath;
  QString outputFolderPath;
};

#endif // IMAGEPREPROCCESSING_H
