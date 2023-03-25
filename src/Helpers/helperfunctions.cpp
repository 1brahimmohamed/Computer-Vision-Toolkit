/******************************************************************************
 *
 * File Name: helperfunctions.cpp
 * Description: Source file for helper functions like reading image, converting
 * the image into different represenation types that are used all over the program
 * Author: Ibrahim Mohamed
 * Last Modified: 24 Mar 23 - 01:38
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

/**
 * @brief function that converts openCV Mat object to pixmap to be viewed on Qt Labels
 * @param imageMat {cv::Mat}
 * @return outputPixmap {Pixmap}
 */
QPixmap HelperFunctions::convertMatToPixmap(Mat imageMat){

  QPixmap outputPixmap;

  // Check the image type
  switch(imageMat.type())
    {
    // Colored Image
    case CV_8UC3:
      {
        QImage qimage(imageMat.data, imageMat.cols, imageMat.rows, static_cast<int>(imageMat.step), QImage::Format_BGR888);
        outputPixmap = QPixmap::fromImage(qimage);
        break;
      }
      // Grayscale Image
    case CV_8UC1:
      {
        QImage qimage(imageMat.data, imageMat.cols, imageMat.rows, static_cast<int>(imageMat.step), QImage::Format_Grayscale8);
        outputPixmap = QPixmap::fromImage(qimage.rgbSwapped());
        break;
      }

      // float 32 Image
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

        QImage qimage(scaled_image.data,
                      scaled_image.cols,
                      scaled_image.rows,
                      static_cast<int>(scaled_image.step),
                      QImage::Format_Grayscale8);

        outputPixmap = QPixmap::fromImage(qimage.rgbSwapped());
      }
    }
  return outputPixmap;
}

/**
 * @brief function that read Image as openCV Mat Object from Local Computer
 * @return image {cv::Mat}
 */
Mat HelperFunctions::readImage_Mat(){

  // get path from the window
  QString filePath = QFileDialog::getOpenFileName(nullptr, "Open Image File", "", "Image Files (*.png *.jpg *.bmp)");

  // if the path is okay read the image else return 1*1 image (like return -1)
  if (!filePath.isEmpty()){
      Mat image = cv::imread(filePath.toStdString());
      return image;
    }
  return Mat::zeros(1,1,CV_32F);
}

/**
 * @brief function to view openCV Mat Object on any Qt QLabel given the Mat and pointer to the UI element
 * @param newImage {cv::Mat}
 * @param label {QLabel*}
 */
void HelperFunctions::viewImageOnLabel(Mat newImage, QLabel* label){
  QPixmap pixmap = convertMatToPixmap(newImage);
  QPixmap scaledpixmap = pixmap.scaled(label->size(), Qt::IgnoreAspectRatio);
  label->setPixmap(scaledpixmap);
}


/**
 * @brief  function to download openCV Mat Object
 * @param image {cv::Mat}
 */
void HelperFunctions::downloadImage(Mat image){

  // get path from the window
  QString fileName = QFileDialog::getSaveFileName(nullptr,
                                                  "Save Image",
                                                  QDir::homePath(),
                                                  "PNG Image (*.png);;JPEG Image (*.jpg);;JPEG Image (*.jpeg) ");

  // if the path is not empty write the image to the path
  if (!fileName.isEmpty()) {
      bool result = cv::imwrite(fileName.toStdString(), image);
      if (!result) {
          QMessageBox::warning(nullptr, "Error", "Failed to save image!");
        }
    }
}
