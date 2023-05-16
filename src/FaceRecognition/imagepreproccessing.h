#ifndef IMAGEPREPROCCESSING_H
#define IMAGEPREPROCCESSING_H

#include <QString>
#include <QDir>
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

private:
  QDir currentDir;
  QString classiferFilePath;
  CascadeClassifier cascade;

  QString inputFolderPath;
  QString outputFolderPath;
};

#endif // IMAGEPREPROCCESSING_H
