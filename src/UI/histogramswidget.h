#ifndef HISTOGRAMSWIDGET_H
#define HISTOGRAMSWIDGET_H

#include <QWidget>
#include <vector>

#include <QtCharts/QChartView>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

struct HistoImage{
  cv::Mat originalImage;
  cv::Mat grayScaleImage;
  cv::Mat equalizedImage;
  cv::Mat normalizedImage;
};

namespace Ui {
  class HistogramsWidget;
}

class HistogramsWidget : public QWidget
{
  Q_OBJECT

public:
  explicit HistogramsWidget(QWidget *parent = nullptr);
  ~HistogramsWidget();

private slots:
  void on_histUploadBtn_clicked();

  void on_downloadEqualBtn_clicked();

  void on_downloadNormalBtn_clicked();

  void on_histGrayBtn_clicked();

private:
  Ui::HistogramsWidget *ui;
  HistoImage HistImage;

  void plotHistogram(const vector<int>& data , QString ChartName, QChartView* widget);
  void equalizeImage();
  void normalizedImage();
};

#endif // HISTOGRAMSWIDGET_H
