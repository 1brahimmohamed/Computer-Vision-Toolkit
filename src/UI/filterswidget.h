/******************************************************************************
 *
 * File Name: filterswidget.h
 * Description: Header file for Filters UI Widget
 * Author(s): Ibrahim Mohamed
 * Last Modified: 24 Mar 23 - 14:25
 *
 *******************************************************************************/



#ifndef FILTERSWIDGET_H
#define FILTERSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMessageBox>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;


struct FilterImage{
  Mat originalImage;
  Mat filteredImage;
  Mat currentImage;
  int kernelSize;
  int mean;
  float sigma;
  float dNote;
};

namespace Ui {
  class FiltersWidget;
}

class FiltersWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FiltersWidget(QWidget *parent = nullptr);
  ~FiltersWidget();

private slots:
  void on_uploadBtn_clicked();
  void on_downloadBtn_clicked();
  void on_uniformNoiseBtn_clicked();
  void on_guassianNoiseBtn_clicked();
  void on_saltNoiseBtn_clicked();
  void on_avgFilterBtn_clicked();
  void on_guasssianFilterBtn_clicked();
  void on_medianFilterBtn_clicked();
  void on_sobelBtn_clicked();
  void on_robertsBtn_clicked();
  void on_prewittBtn_clicked();
  void on_cannyBtn_clicked();
  void on_lowPassBtn_clicked();
  void on_highPassBtn_clicked();
  void on_freqGuassianBtn_clicked();
  void on_lThresholdingBtn_clicked();
  void on_gThresholdingBtn_clicked();
  void on_kernelSlider_valueChanged(int value);
  void on_sigmaSlider_valueChanged(int value);
  void on_meanSlider_valueChanged(int value);

  void on_applyBtn_clicked();

  void on_resetBtn_clicked();

private:
  Ui::FiltersWidget *ui;

  FilterImage filtersWidgetImage;

  void updateFilteredPicture(Mat updatedImage);
  void updateCurrentPicture(Mat updatedImage);
  void viewImageOnLabel(Mat newImage, QLabel* label);
  void downloadImage(Mat image);

};

#endif // FILTERSWIDGET_H
