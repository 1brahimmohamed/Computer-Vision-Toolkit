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
  int numberOfClusters;
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

  void on_kmeanBtn_clicked();

  void on_maxItrSlider_sliderReleased();

  void on_maxItrSlider_valueChanged(int value);

  void on_optThresSlider_sliderReleased();

  void on_optThresSlider_valueChanged(int value);

  void on_colorBandSlider_sliderReleased();

  void on_colorBandSlider_valueChanged(int value);

  void on_distanceBandSlider_sliderReleased();

  void on_distanceBandSlider_valueChanged(int value);

  void on_nClustersSlider_sliderReleased();

  void on_nClustersSlider_valueChanged(int value);

  void on_seedXSlider_sliderReleased();

  void on_seedXSlider_valueChanged(int value);

  void on_seedYSlider_sliderReleased();

  void on_seedYSlider_valueChanged(int value);

  void on_rGrowThresholdSlider_sliderReleased();

  void on_rGrowThresholdSlider_valueChanged(int value);

  void on_kClustersSlider_sliderReleased();

  void on_kClustersSlider_valueChanged(int value);

  void on_segDownloadBtn_clicked();

private:
  Ui::segmentationWidget *ui;

  SegmentationImage segmentationWidgetImage;

  void updateSegmentedPicture(Mat updatedImage);
  void updateCurrentPicture(Mat updatedImage);

  void applyOptimalThreshold();
  void applyMeanShift();
  void applyRegionGrowing();
  void applyAgglomerative();
  void applyKMeans();

};

#endif // SEGMENTATIONWIDGET_H
