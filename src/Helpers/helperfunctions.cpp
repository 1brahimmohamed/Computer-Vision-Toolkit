/******************************************************************************
 *
 * File Name: helperfunctions.cpp
 * Description: Source file for helper functions like reading image & converting
 * the image into different represenation types.
 * Author: Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:38
 *
 *******************************************************************************/


#include "helperfunctions.h"
#include <vector>
using namespace std;

HelperFunctions::HelperFunctions()
{

}

HelperFunctions::~HelperFunctions()
{

}

QPixmap HelperFunctions::convertQByteArrToPixmap(QByteArray arr){
    QPixmap pixmap;
    pixmap.loadFromData(arr);
    return pixmap;
}

QPixmap HelperFunctions::convertMatToPixmap(Mat imageMat){

    QPixmap outputPixmap;

    switch(imageMat.type())
      {
        case CV_8UC3:
          {
            QImage qimage(imageMat.data, imageMat.cols, imageMat.rows, static_cast<int>(imageMat.step), QImage::Format_BGR888);
            outputPixmap = QPixmap::fromImage(qimage);
            break;
          }
      case CV_8UC1:
        {
          QImage qimage(imageMat.data, imageMat.cols, imageMat.rows, static_cast<int>(imageMat.step), QImage::Format_Grayscale8);
          outputPixmap = QPixmap::fromImage(qimage.rgbSwapped());
          break;
        }
      case CV_32F:
        {
            // scaled image
            Mat scaled_image;
            double min_val, max_val;

            // get max & min value of the image
            minMaxLoc(imageMat, &min_val, &max_val);

            // convert image into grayscale 8bit image
            double scale_factor = 255.0 / (max_val - min_val);
            imageMat.convertTo(scaled_image, CV_8UC1, scale_factor, -scale_factor * min_val);

            QImage qimage(scaled_image.data, scaled_image.cols, scaled_image.rows, static_cast<int>(scaled_image.step), QImage::Format_Grayscale8);
            outputPixmap = QPixmap::fromImage(qimage.rgbSwapped());
        }
      }
    return outputPixmap;
}

QByteArray HelperFunctions::readImage_QByte(){
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.bmp *.jpeg)");

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray imageData = file.readAll();

    return imageData;
}

Mat HelperFunctions::readImage_Mat(){
  QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.bmp)");
  if (!filePath.isEmpty()){
      Mat image = cv::imread(filePath.toStdString());
      return image;
  }
  return Mat::zeros(1,1,CV_32F);
}


