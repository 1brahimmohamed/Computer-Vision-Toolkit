/******************************************************************************
 *
 * File Name: mainwindow.cpp
 * Description: Source file for the GUI main window of the program
 * Authors: Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:40
 *
 *******************************************************************************/

#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/Helpers/helperfunctions.h"

#include "src/Filters/imagesmoothers.h"
#include "src/Filters/edgedetectors.h"
#include "src/Filters/noiseaddatives.h"
#include "src/Histograms/histograms.h"


using namespace cv;

Image filterTabImage, grayscaleTabImage, HistoTabImage,HybridImage1, HybridImage2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFilteredPicture(Mat updatedImage){
  filterTabImage.setFilteredImage(updatedImage);
  QPixmap pixmap = HelperFunctions::convertMatToPixmap(updatedImage);
  QPixmap scaledpixmap = pixmap.scaled(ui->tabFilterFilteredImage->size(), Qt::IgnoreAspectRatio);
  ui->tabFilterFilteredImage->setPixmap(scaledpixmap);
}

void MainWindow::updateCurrentPicture(Mat updatedImage){
  filterTabImage.setCurrentImage(updatedImage);
  QPixmap pixmap = HelperFunctions::convertMatToPixmap(updatedImage);
  QPixmap scaledpixmap = pixmap.scaled(ui->tabFilterFilteredImage->size(), Qt::IgnoreAspectRatio);
  ui->tabFilterOriginalImage->setPixmap(scaledpixmap);
}

void MainWindow::downloadImage(Image &imgObj){
  QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Image", QDir::homePath(), "PNG Image (*.png);;JPEG Image (*.jpg)");

  if (!fileName.isEmpty()) {
      bool result = cv::imwrite(fileName.toStdString(), imgObj.getFilteredImage());

      if (!result) {
          QMessageBox::warning(nullptr, "Error", "Failed to save image!");
        }
    }
}


// ------------------------  Filter Tab Handlers ------------------------ //

// upload & download
void MainWindow::on_uploadBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols != 1 && Image.rows != 1){
      filterTabImage.setFirstUpload(Image);
      QPixmap pixmap = HelperFunctions::convertMatToPixmap(Image);
      QPixmap scaledpixmap = pixmap.scaled(ui->tabFilterOriginalImage->size(), Qt::IgnoreAspectRatio);
      ui->tabFilterOriginalImage->setPixmap(scaledpixmap);
  }
}

void MainWindow::on_downloadBtn_clicked()
{
  downloadImage(filterTabImage);
}

// Photo Smoothness
void MainWindow::on_averageRemoveBtn_clicked()
{
  Mat outputImage = ImageSmoothers::applyAverageFilter(filterTabImage.getCurrentImage(), filterTabImage.kenerlSize);
  updateFilteredPicture(outputImage);
}

void MainWindow::on_gaussianRemoveBtn_clicked()
{
  Mat outputImage = ImageSmoothers::applyGaussianFilter(filterTabImage.getCurrentImage(), filterTabImage.kenerlSize, filterTabImage.sigma);
  updateFilteredPicture(outputImage);
}

void MainWindow::on_medianRemoveBtn_clicked()
{

  Mat outputImage = ImageSmoothers::applyMedianFilter(filterTabImage.getCurrentImage(), filterTabImage.kenerlSize);
  updateFilteredPicture(outputImage);
}


// Noise addition
void MainWindow::on_uniformNoiseBtn_clicked()
{
  // @TODO: HERE IMPLEMENT
}

void MainWindow::on_saltNoiseBtn_clicked()
{
  Mat outputImage = NoiseAddatives::SaltAndPepperNoise(filterTabImage.getCurrentImage());
  updateFilteredPicture(outputImage);
}

void MainWindow::on_gaussianNoiseBtn_clicked()
{
  Mat outputImage = NoiseAddatives::GaussianNoise(filterTabImage.getCurrentImage(), outputImage, 1,1);
  updateFilteredPicture(outputImage);
}

// Edge Detectors
void MainWindow::on_sobelBtn_clicked()
{
  Mat outputImage = EdgeDetectors::SobalEdgeDetector(filterTabImage.getCurrentImage());
  updateFilteredPicture(outputImage);
}

void MainWindow::on_robertsBtn_clicked()
{
  Mat outputImage = EdgeDetectors::RobertEdgeDetector(filterTabImage.getCurrentImage());
  updateFilteredPicture(outputImage);
}

void MainWindow::on_prewittBtn_clicked()
{
  Mat outputImage = EdgeDetectors::PerwittEdgeDetector(filterTabImage.getCurrentImage());
  updateFilteredPicture(outputImage);
}

void MainWindow::on_cannyBtn_clicked()
{
  Mat outputImage = EdgeDetectors::CannyEdgeDetector(filterTabImage.getCurrentImage());
  updateFilteredPicture(outputImage);
}

// Frequency Filters
void MainWindow::on_lowFrequencyFilterBtn_clicked()
{

}

void MainWindow::on_highFrequencyFilterBtn_clicked()
{

}

void MainWindow::on_gaussianFrequencyFilterBtn_clicked()
{

}

// Controls
void MainWindow::on_applyBtn_clicked()
{
    filterTabImage.setPreviousActionImage(filterTabImage.getCurrentImage());
    updateCurrentPicture(filterTabImage.getFilteredImage());
}

void MainWindow::on_resetBtn_clicked()
{
  updateCurrentPicture(filterTabImage.getOriginalImage());
}


// ------------------------  Grayscale Tab Handlers ------------------------ //


void MainWindow::on_uploadRGB_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols != 1 && Image.rows != 1){
      grayscaleTabImage.setFirstUpload(Image);
      QPixmap pixmap = HelperFunctions::convertMatToPixmap(Image);
      QPixmap scaledpixmap = pixmap.scaled(ui->tabGrayOriginalImage->size(), Qt::IgnoreAspectRatio);
      ui->tabGrayOriginalImage->setPixmap(scaledpixmap);

      Mat grayscaleMat;
      cvtColor(Image,grayscaleMat, COLOR_BGR2GRAY);
      QPixmap grayPixmap = HelperFunctions::convertMatToPixmap(grayscaleMat);
      ui->tabGrayGrayImage->setPixmap(grayPixmap);
  }
}

void MainWindow::on_downloadGray_clicked()
{
    downloadImage(grayscaleTabImage);
}


// ------------------------  Histograms Tab Handlers ------------------------ //


void MainWindow::on_uploadHist_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();

  if (Image.cols != 1 && Image.rows != 1){
      HistoTabImage.setFirstUpload(Image);
      Mat grayscaleMat;
      cvtColor(Image,grayscaleMat, COLOR_BGR2GRAY);

      QPixmap pixmap = HelperFunctions::convertMatToPixmap(grayscaleMat);

      QPixmap scaledpixmap = pixmap.scaled(ui->tabHistOriginalImage->size(), Qt::IgnoreAspectRatio);
      ui->tabHistOriginalImage->setPixmap(scaledpixmap);

      // Equalize
      vector<int> histogram = Histograms::Histo(grayscaleMat);
      vector<int> cumlautiveHistogram = Histograms::cumHist(histogram);
      vector<int> scale = Histograms::calcuateScale(Image, cumlautiveHistogram);

      Mat matEqualized = Histograms::equilization(grayscaleMat, scale);

      QPixmap equalizedPixmap = HelperFunctions::convertMatToPixmap(matEqualized);
      QPixmap scaledEqualizedPixmap = equalizedPixmap.scaled(ui->tabHistEqualizedImage->size(), Qt::IgnoreAspectRatio);
      ui->tabHistEqualizedImage->setPixmap(scaledEqualizedPixmap);

      vector<int> equalizedHistogram = Histograms::equalizedHistogram(grayscaleMat, histogram, scale);

      // Normalize
      Mat matNormalized = Histograms::normalizeMat(grayscaleMat, 0, 255);
      QPixmap normalizedPixmap = HelperFunctions::convertMatToPixmap(matNormalized);
      QPixmap scaledNormalizedPixmap = normalizedPixmap.scaled(ui->tabHistNormalizedImage->size(), Qt::IgnoreAspectRatio);
      ui->tabHistNormalizedImage->setPixmap(scaledNormalizedPixmap);
  }
}

// ------------------------  Hybird Tab Handlers ------------------------ //




void MainWindow::on_uploadImage1_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols != 1 && Image.rows != 1){
      HybridImage1.setFirstUpload(Image);
      QPixmap pixmap = HelperFunctions::convertMatToPixmap(Image);
      QPixmap scaledpixmap = pixmap.scaled(ui->tabMixerImage1->size(), Qt::IgnoreAspectRatio);
      ui->tabMixerImage1->setPixmap(scaledpixmap);
    }
}


void MainWindow::on_uploadImage1_2_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols != 1 && Image.rows != 1){
      HybridImage2.setFirstUpload(Image);
      QPixmap pixmap = HelperFunctions::convertMatToPixmap(Image);
      QPixmap scaledpixmap = pixmap.scaled(ui->tabMixerImage2->size(), Qt::IgnoreAspectRatio);
      ui->tabMixerImage2->setPixmap(scaledpixmap);
      ui->tabMixerImageMixed->setPixmap(scaledpixmap);
    }
}

