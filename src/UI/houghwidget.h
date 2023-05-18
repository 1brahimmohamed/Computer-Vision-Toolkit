/******************************************************************************
 *
 * File Name: houghwidget.cpp
 * Description: Source file for Hough UI Widget
 * Author(s): Ibrahim Mohamed
 * Last Modified: 25 Mar 23 - 02:02
 *
 *******************************************************************************/


#ifndef HOUGHWIDGET_H
#define HOUGHWIDGET_H

#include <QWidget>
#include <QSlider>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

struct HoughImage{
  Mat originalImage;
  Mat shapeDetectedImage;
  int threshold;
  int maxRaduis;
  int minRaduis;
  float numberOfPoints;
  float initRaduis;
  int xBais;
  int yBais;
};

namespace Ui {
  class HoughWidget;
}

class HoughWidget : public QWidget
{
  Q_OBJECT

public:
  explicit HoughWidget(QWidget *parent = nullptr);
  ~HoughWidget();

private slots:
  void on_uploadBtn_clicked();
  void on_lineBtn_clicked();
  void on_circleBtn_clicked();
  void on_ellipseBtn_clicked();
  void on_lineThreshSlider_sliderReleased();
  void on_lineThreshSlider_valueChanged(int value);
  void on_minRaduisSlider_sliderReleased();
  void on_minRaduisSlider_valueChanged(int value);
  void on_maxRaduisSlider_sliderReleased();
  void on_maxRaduisSlider_valueChanged(int value);
  void on_betaSlider_sliderReleased();
  void on_betaSlider_valueChanged(int value);
  void on_alphaSlider_sliderReleased();
  void on_alphaSlider_valueChanged(int value);
  void on_gammaSlider_sliderReleased();
  void on_gammaSlider_valueChanged(int value);
  void on_activeContBtn_clicked();
  void on_downloadBtn_clicked();
  void on_thetaSlider_sliderReleased();
  void on_thetaSlider_valueChanged(int value);

private:
  Ui::HoughWidget *ui;
  HoughImage houghImage;

  void lineDetectionOnImage();
  void circleDetectionOnImage();
  void activeContourOnImage();
  float mapSliderValue(float mappedLowerLimit, float mappedUpperLimit, float step, QSlider* slider);
};

#endif // HOUGHWIDGET_H
