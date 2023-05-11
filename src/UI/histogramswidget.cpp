/******************************************************************************
 *
 * File Name: histogramswidget.cpp
 * Description: Source file for Histogram UI Widget
 * Author(s): Ibrahim Mohamed
 * Last Modified: 24 Mar 23 - 15:19
 *
 *******************************************************************************/


#include "histogramswidget.h"
#include "ui_histogramswidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

#include <QGraphicsLayout>

#include "src/Helpers/helperfunctions.h"
#include "src/Histograms/histograms.h"

using namespace cv;

HistogramsWidget::HistogramsWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HistogramsWidget)
{
  ui->setupUi(this);
}

HistogramsWidget::~HistogramsWidget()
{
  delete ui;
}

// ------------------------------- GENERAL FUNCTIONS ------------------------------------- //

void HistogramsWidget::plotHistogram(const vector<int>& data , QString ChartName, QChartView* widget){
  QChart *chart = new QChart();
  QBarSeries *series = new QBarSeries();

  QBarSet *set = new QBarSet(ChartName);
  for (int value : data) {
      *set << value;
    }

  series->append(set);
  chart->addSeries(series);
//  chart->setTitle(ChartName);
  chart->setBackgroundBrush(Qt::black);
  chart->layout()->setContentsMargins(0, 0, 0, 0);
  widget->setChart(chart);
}

void HistogramsWidget::equalizeImage(){

  // get the histogtam, cumulative histogram, equalizedHistogram
  vector<int> histogram = Histograms::Histo(this->HistImage.grayScaleImage);
  vector<int> cumlautiveHistogram = Histograms::cumHist(histogram);
  vector<int> scale = Histograms::calcuateScale(this->HistImage.originalImage, cumlautiveHistogram);
  vector<int> equalizedHistogram = Histograms::equalizedHistogram(this->HistImage.grayScaleImage, histogram, scale);

  // equalize Image & view it
  Mat matEqualized = Histograms::equilization(this->HistImage.grayScaleImage, scale);
  this->HistImage.equalizedImage = matEqualized;
  HelperFunctions::viewImageOnLabel(this->HistImage.equalizedImage, ui->HistPictureEqualized);

  plotHistogram(histogram, "Histogram", ui->histogram);
  plotHistogram(cumlautiveHistogram, "Cumulative Histogram", ui->histogramCum);
  plotHistogram(equalizedHistogram, "EqualizedHistogram", ui->histogramNorm);
}

void HistogramsWidget::normalizedImage(){
  Mat matNormalized = Histograms::normalizeMat(this->HistImage.grayScaleImage, 0, 255);
  this->HistImage.normalizedImage = matNormalized;
  HelperFunctions::viewImageOnLabel(this->HistImage.normalizedImage, ui->HistPictureNormalized);
}


// ------------------------------- EVENT LISENTERS FUNCTIONS ------------------------------------- //

void HistogramsWidget::on_histUploadBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols != 1 && Image.rows != 1){
      // set Image
      this->HistImage.originalImage = Image;
      HelperFunctions::viewImageOnLabel(this->HistImage.originalImage, ui->HistPictureOrginal);

      // convert to grayscale & view it
      cvtColor(Image,this->HistImage.grayScaleImage, COLOR_BGR2GRAY);
      HelperFunctions::viewImageOnLabel(this->HistImage.grayScaleImage, ui->HistPictureGrey);

      // Equalization
      equalizeImage();

      // Normalization
      normalizedImage();

      // CDF & PDF Histograms
      Mat CDF = Histograms::plotRGBHistogramCDF(this->HistImage.originalImage);
      Mat PDF = Histograms::plotRGBHistogramPDF(this->HistImage.originalImage);

      HelperFunctions::viewImageOnLabel(CDF, ui->histogramCDF);
      HelperFunctions::viewImageOnLabel(PDF, ui->histogramPDF);

    }
}

void HistogramsWidget::on_downloadEqualBtn_clicked()
{
    if(!HistImage.originalImage.empty())
      HelperFunctions::downloadImage(this->HistImage.equalizedImage);
}

void HistogramsWidget::on_downloadNormalBtn_clicked()
{
  if(!HistImage.originalImage.empty())
    HelperFunctions::downloadImage(this->HistImage.normalizedImage);
}

void HistogramsWidget::on_histGrayBtn_clicked()
{
  if(!HistImage.originalImage.empty())
    HelperFunctions::downloadImage(this->HistImage.grayScaleImage);
}

