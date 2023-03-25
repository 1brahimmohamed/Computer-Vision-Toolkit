/******************************************************************************
 *
 * File Name: helperfunctions.h
 * Description: Header file for helper functions like reading image, converting
 * the image into different represenation types that are used all over the program
 * Author: Ibrahim Mohamed
 * Last Modified: 24 Mar 23 - 01:38
 *
 *******************************************************************************/

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <QPixmap>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class HelperFunctions
{
public:
  HelperFunctions();
  ~HelperFunctions();
  static Mat readImage_Mat();
  static QPixmap convertMatToPixmap(Mat imageMat);
  static void viewImageOnLabel(Mat newImage, QLabel* label);
  static void downloadImage(Mat image);
};

#endif // HELPERFUNCTIONS_H
