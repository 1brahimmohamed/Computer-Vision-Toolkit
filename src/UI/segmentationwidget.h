#ifndef SEGMENTATIONWIDGET_H
#define SEGMENTATIONWIDGET_H

#include <QWidget>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

struct SegmentationImage{
  Mat originalImage;
  Mat segmentedImage;
  Mat currentImage;
  float distanceBandWidth;
  float colorBandWidth;
  int maxItrs;
  double optimalThreshold;
  int regionGrowThreshold;
  int seedX;
  int seedY;
  cv::Size imageSize;
};

namespace Ui {
  class segmentationWidget;
}

class segmentationWidget : public QWidget
{
  Q_OBJECT

public:
  explicit segmentationWidget(QWidget *parent = nullptr);
  ~segmentationWidget();

private slots:
  void on_segUploadBtn_clicked();
  void on_meanshiftBtn_clicked();

  void on_optimalThresBtn_clicked();

  void on_otsuBtn_clicked();

  void on_localThresBtn_clicked();

  void on_globalThresBtn_clicked();

  void on_regionGrowingBtn_clicked();

  void on_agglomerativeBtn_clicked();

private:
  Ui::segmentationWidget *ui;

  SegmentationImage segmentationWidgetImage;

  void updateSegmentedPicture(Mat updatedImage);
  void updateCurrentPicture(Mat updatedImage);
};

#endif // SEGMENTATIONWIDGET_H
