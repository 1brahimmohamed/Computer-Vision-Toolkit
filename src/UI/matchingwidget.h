#ifndef MATCHINGWIDGET_H
#define MATCHINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

namespace Ui {
  class MatchingWidget;
}

class MatchingWidget : public QWidget
{
  Q_OBJECT

public:
  Mat matchImage1, matchImage2;
  int whatPic;

  explicit MatchingWidget(QWidget *parent = nullptr);
  ~MatchingWidget();

private slots:
  void on_matchImage1Btn_clicked();

  void on_matchImage2Btn_clicked();

  void on_harrisApplyBtn_clicked();

  void on_siftApllyBtn_clicked();

  void on_matchApplyBtn_clicked();

  void on_checkBox_stateChanged(int arg1);

private:
  Ui::MatchingWidget *ui;
  void updateLabel(Mat updatedImage , QLabel *pictureLable);
  Mat operatingImage();
};

#endif // MATCHINGWIDGET_H
