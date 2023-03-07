#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QByteArray>
#include <QPixmap>
#include <QFileDialog>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class HelperFunctions
{
public:
  HelperFunctions();
  ~HelperFunctions();
  static QByteArray readImage_QByte();
  static Mat readImage_Mat();
  static QPixmap convertQByteArrToPixmap(QByteArray arr);
  static QPixmap convertMatToPixmap(Mat imageMat);
};

#endif // HELPERFUNCTIONS_H
