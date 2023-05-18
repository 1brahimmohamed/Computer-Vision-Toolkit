#include "houghwidget.h"
#include "ui_houghwidget.h"

#include "houghwidget.h"
#include "src/Helpers/helperfunctions.h"

#include "src/Hough/houghcircle.h"
#include "src/Hough/houghline.h"
#include "src/Hough/houghellipse.h"
#include "src/ActiveContour/active_contour.h"


HoughWidget::HoughWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HoughWidget)
{
  ui->setupUi(this);
  this->houghImage.threshold = 150;
  this->houghImage.maxRaduis = 35;
  this->houghImage.minRaduis = 10;
  this->houghImage.numberOfPoints = 80;
  this->houghImage.initRaduis = 100;
  this->houghImage.xBais = 150;
  this->houghImage.yBais = 50;
}

HoughWidget::~HoughWidget()
{
  delete ui;
}


// -------------------------- Download & Upload -------------------------- //
void HoughWidget::on_uploadBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows > 1){
      this->houghImage.originalImage = Image;
      HelperFunctions::viewImageOnLabel(this->houghImage.originalImage, ui->imageOriginal);
    }
}

void HoughWidget::on_downloadBtn_clicked()
{
  HelperFunctions::downloadImage(houghImage.shapeDetectedImage);
}

// -------------------------- Hough Transform Events -------------------------- //

void HoughWidget::on_lineBtn_clicked()
{
  if(!houghImage.originalImage.empty())
    lineDetectionOnImage();
}

void HoughWidget::on_circleBtn_clicked()
{
  if(!houghImage.originalImage.empty())
    circleDetectionOnImage();
}

void HoughWidget::on_ellipseBtn_clicked()
{
  if(!houghImage.originalImage.empty()){
      this->houghImage.shapeDetectedImage = HoughEllipse::houghEllipseDetection(this->houghImage.originalImage, 10, 10, 10, 10);
      HelperFunctions::viewImageOnLabel(this->houghImage.shapeDetectedImage, ui->imageFiltered);
    }
}


// -------------------------- Action Handlers -------------------------- //

void HoughWidget::lineDetectionOnImage(){
  if(!houghImage.originalImage.empty()){
      this->houghImage.shapeDetectedImage = HoughLine::detectLines(this->houghImage.originalImage, this->houghImage.threshold);
      HelperFunctions::viewImageOnLabel(this->houghImage.shapeDetectedImage, ui->imageFiltered);
    }
}

void HoughWidget::circleDetectionOnImage(){
  if(!houghImage.originalImage.empty()){
      houghImage.shapeDetectedImage = HoughCircle::HoughCircleCall(houghImage.originalImage, houghImage.minRaduis, houghImage.maxRaduis);
      HelperFunctions::viewImageOnLabel(houghImage.shapeDetectedImage, ui->imageFiltered);
    }
}


// -------------------------- Hough Sliders Event listeners -------------------------- //


void HoughWidget::on_lineThreshSlider_sliderReleased()
{
  int value = ui->lineThreshSlider->value();
  this->houghImage.threshold = value;
  ui->lineThreshSliderValue->setText(QString::number(value));

  if(!houghImage.originalImage.empty())
    lineDetectionOnImage();
}


void HoughWidget::on_lineThreshSlider_valueChanged(int value)
{
  ui->lineThreshSliderValue->setText(QString::number(value));
}


void HoughWidget::on_minRaduisSlider_sliderReleased()
{
  int value = ui->minRaduisSlider->value();
  this->houghImage.minRaduis = value;
  ui->minRaduisSliderValue->setText(QString::number(value));

  if(!houghImage.originalImage.empty())
    circleDetectionOnImage();
}


void HoughWidget::on_minRaduisSlider_valueChanged(int value)
{
  ui->minRaduisSliderValue->setText(QString::number(value));
}


void HoughWidget::on_maxRaduisSlider_sliderReleased()
{
  int value = ui->maxRaduisSlider->value();
  this->houghImage.maxRaduis = value;
  ui->maxRaduisSliderValue->setText(QString::number(value));

  if(!houghImage.originalImage.empty())
    circleDetectionOnImage();
}


void HoughWidget::on_maxRaduisSlider_valueChanged(int value)
{
  ui->maxRaduisSliderValue->setText(QString::number(value));
}


// -------------------------- Active Contour -------------------------- //

void HoughWidget::activeContourOnImage(){

  if(!houghImage.originalImage.empty()){
      Mat activeContouredImage = ACTIVE_CONTOUR::active_contour(this->houghImage.originalImage,
                                                                50, // # of iterations
                                                                1, // Alpha
                                                                2, // Beta
                                                                5, // Gamma
                                                                this->houghImage.numberOfPoints, // # of points
                                                                this->houghImage.initRaduis, // init snake radius
                                                                this->houghImage.xBais, // init snake CenterX Bias
                                                                this->houghImage.yBais); // init snake CenterY Bias
      HelperFunctions::viewImageOnLabel(activeContouredImage, ui->imageFiltered);
    }
}

void HoughWidget::on_activeContBtn_clicked()
{
  activeContourOnImage();
}

// -------------------------- Active Contours Sliders Event listeners -------------------------- //


void HoughWidget::on_alphaSlider_sliderReleased()
{
  float value = mapSliderValue(0, 500 ,10, ui->alphaSlider);
  this->houghImage.numberOfPoints = value;
  ui->alphaValue->setText(QString::number(value));

  if(!houghImage.originalImage.empty())
    activeContourOnImage();
}


void HoughWidget::on_alphaSlider_valueChanged(int value)
{
  float fvalue = mapSliderValue(0, 500 ,10, ui->alphaSlider);
  ui->alphaValue->setText(QString::number(fvalue));
}


void HoughWidget::on_betaSlider_sliderReleased()
{
  float value = mapSliderValue(0, 500, 10, ui->betaSlider);
  this->houghImage.initRaduis = value;
  ui->betaValue->setText(QString::number(value));
  if(!houghImage.originalImage.empty())
    activeContourOnImage();
}


void HoughWidget::on_betaSlider_valueChanged(int value)
{
  float fvalue = mapSliderValue(0, 500 ,10, ui->betaSlider);
  ui->betaValue->setText(QString::number(fvalue));}


void HoughWidget::on_gammaSlider_sliderReleased()
{
  float value = mapSliderValue(0, 500, 10, ui->gammaSlider);
  this->houghImage.xBais = value;
  ui->gammaValue->setText(QString::number(value));

  if(!houghImage.originalImage.empty())
    activeContourOnImage();
}


void HoughWidget::on_gammaSlider_valueChanged(int value)
{
  float fvalue = mapSliderValue(0, 500 ,10, ui->gammaSlider);
  ui->gammaValue->setText(QString::number(fvalue));
}

void HoughWidget::on_thetaSlider_sliderReleased()
{
  float value = mapSliderValue(0, 500, 10, ui->thetaSlider);
  this->houghImage.yBais = value;
  ui->thetaValue->setText(QString::number(value));

  if(!houghImage.originalImage.empty())
    activeContourOnImage();
}

void HoughWidget::on_thetaSlider_valueChanged(int value)
{
  float fvalue = mapSliderValue(0, 500 ,10, ui->thetaSlider);
  ui->thetaValue->setText(QString::number(fvalue));
}


// -------------------------- Helpers -------------------------- //

float HoughWidget::mapSliderValue(float mappedLowerLimit, float mappedUpperLimit, float step, QSlider* slider) {
  float range = mappedUpperLimit - mappedLowerLimit;
  float factor = range / (slider->maximum() - slider->minimum());
  float fvalue = floor(slider->value() * factor / step + 0.5) * step + mappedLowerLimit;
  return fvalue;
}

