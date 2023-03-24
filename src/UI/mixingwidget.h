#ifndef MIXINGWIDGET_H
#define MIXINGWIDGET_H

#include <QWidget>
#include <QLabel>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Ui {
  class MixingWidget;
}

struct MixingImage{
  Mat Image;
  float dNote;
};

class MixingWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MixingWidget(QWidget *parent = nullptr);
  ~MixingWidget();

private slots:
  void on_mixImage1Btn_clicked();
  void on_mixImage2Btn_clicked();

  void on_mixBtn_clicked();
  void on_image1D0Slider_valueChanged(int value);
  void on_kernelSlider_4_valueChanged(int value);

private:
  Ui::MixingWidget *ui;

  MixingImage image1;
  MixingImage image2;
  Mat hybridImage;

  void uploadImage(MixingImage &ImageStruct, QLabel * Label);
  void mixImages();
};

#endif // MIXINGWIDGET_H
