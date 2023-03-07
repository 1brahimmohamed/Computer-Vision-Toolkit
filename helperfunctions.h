/******************************************************************************
 *
 * File Name: helperfunctions.h
 * Description: Header file for helper functions like reading image & converting
 * the image into different represenation types.
 * Author: Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:38
 *
 *******************************************************************************/

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
