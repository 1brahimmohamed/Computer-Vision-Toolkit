/******************************************************************************
 *
 * File Name: mainwindow.h
 * Description: Header file for the GUI main window of the program
 * Authors: Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:40
 *
 *******************************************************************************/

#include <QMainWindow>
#include <vector>
#include <QtCharts>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "src/Helpers/image.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

using namespace std;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void updateFilteredPicture(cv::Mat updatedImage);
  void updateCurrentPicture(cv::Mat updatedImage);
  void downloadImage(Image &imageObj);
  void plotHistogram(const vector<int>& data , QString ChartName, QChartView* widget);

private slots:

  void on_uploadBtn_clicked();

  void on_averageRemoveBtn_clicked();

  void on_downloadBtn_clicked();

  void on_gaussianRemoveBtn_clicked();

  void on_medianRemoveBtn_clicked();

  void on_uniformNoiseBtn_clicked();

  void on_saltNoiseBtn_clicked();

  void on_gaussianNoiseBtn_clicked();

  void on_sobelBtn_clicked();

  void on_robertsBtn_clicked();

  void on_prewittBtn_clicked();

  void on_cannyBtn_clicked();

  void on_lowFrequencyFilterBtn_clicked();

  void on_highFrequencyFilterBtn_clicked();

  void on_gaussianFrequencyFilterBtn_clicked();

  void on_applyBtn_clicked();

  void on_resetBtn_clicked();

  void on_uploadRGB_clicked();

  void on_downloadGray_clicked();

  void on_uploadHist_clicked();

  void on_uploadImage1_clicked();

  void on_uploadImage1_2_clicked();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
