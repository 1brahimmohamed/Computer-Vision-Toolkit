#ifndef FACERECOGNITIONWIDGET_H
#define FACERECOGNITIONWIDGET_H

#include <QWidget>
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


struct RecognitionImage{
  Mat originalImage;
  Mat detectedFacesImage;
  vector<Mat> detectedFacesImages;
};

namespace Ui {
  class FaceRecognitionWidget;
}

class FaceRecognitionWidget : public QWidget
{
  Q_OBJECT

public:
  explicit FaceRecognitionWidget(QWidget *parent = nullptr);
  ~FaceRecognitionWidget();

private slots:
  void on_uploadImageBtn_clicked();

  void on_detectFacesBtn_clicked();

private:
  Ui::FaceRecognitionWidget *ui;

  RecognitionImage recognitionWidgetImage;
  cv::CascadeClassifier cascade;

  void updateFilteredPicture(Mat updatedImage);
  void updateCurrentPicture(Mat updatedImage);
};

#endif // FACERECOGNITIONWIDGET_H
