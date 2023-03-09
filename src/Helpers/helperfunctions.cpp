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
    Mat rgbImage;
    cvtColor(imageMat, rgbImage, COLOR_BGR2RGB);
    QImage qimage(rgbImage.data, rgbImage.cols, rgbImage.rows, static_cast<int>(rgbImage.step), QImage::Format_RGB888);
    QPixmap pixmap= QPixmap::fromImage(qimage);
    return pixmap;
}

QByteArray HelperFunctions::readImage_QByte(){
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.bmp)");

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray imageData = file.readAll();

    return imageData;
}

Mat HelperFunctions::readImage_Mat(){
  QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.bmp)");
  cv::Mat image = cv::imread(filePath.toStdString());
  return image;
}
