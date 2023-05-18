#ifndef IMAGEPREPROCCESSING_H
#define IMAGEPREPROCCESSING_H

#include <QString>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

class ImagePreproccessing
{
public:
  ImagePreproccessing();

  void DetectFacesInFolder();

  static vector<QString> readImagesPath(QString inputFolder, vector<QString> &labels);
  static Mat FlattenImages(vector<Mat> images);
  static Mat normalizeImages(Mat flattenImages, Mat &sentMean);
  static QString getLabelFromImagePath(QString imagePath);
  static Mat imageNormalization(Mat image, Mat mean);
  static void saveMatricesToJson(const cv::Mat eigenFaces, const cv::Mat weights, const cv::Mat mean, const QString filePath);
  static void loadMatricesFromJson(cv::Mat& eigenFaces, cv::Mat& weights, cv::Mat& mean, const QString filePath);
  static void training(QString modelPath);

private:
  QDir currentDir;
  QString classiferFilePath;
  CascadeClassifier cascade;

  QString inputFolderPath;
  QString outputFolderPath;
};

#endif // IMAGEPREPROCCESSING_H
