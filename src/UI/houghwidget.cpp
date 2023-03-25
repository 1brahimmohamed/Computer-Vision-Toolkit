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
  this->houghImage.alpha = 1;
  this->houghImage.beta = 2;
  this->houghImage.gamma = 5;
}

HoughWidget::~HoughWidget()
{
  delete ui;
}

void HoughWidget::on_uploadBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows > 1){
      this->houghImage.originalImage = Image;
      HelperFunctions::viewImageOnLabel(this->houghImage.originalImage, ui->imageOriginal);
    }
}


void HoughWidget::on_lineBtn_clicked()
{
  lineDetectionOnImage();
}


void HoughWidget::on_circleBtn_clicked()
{
  circleDetectionOnImage();
}


void HoughWidget::on_ellipseBtn_clicked()
{
  this->houghImage.shapeDetectedImage = HoughEllipse::houghEllipseDetection(this->houghImage.originalImage, 10, 10, 10, 10);
  HelperFunctions::viewImageOnLabel(this->houghImage.shapeDetectedImage, ui->imageFiltered);
}

void HoughWidget::lineDetectionOnImage(){
  this->houghImage.shapeDetectedImage = HoughLine::detectLines(this->houghImage.originalImage, this->houghImage.threshold);
  HelperFunctions::viewImageOnLabel(this->houghImage.shapeDetectedImage, ui->imageFiltered);
}

void HoughWidget::circleDetectionOnImage(){
  houghImage.shapeDetectedImage = HoughCircle::HoughCircleCall(houghImage.originalImage, houghImage.minRaduis, houghImage.maxRaduis);
  HelperFunctions::viewImageOnLabel(houghImage.shapeDetectedImage, ui->imageFiltered);
}


void HoughWidget::on_lineThreshSlider_sliderReleased()
{
  int value = ui->lineThreshSlider->value();
  this->houghImage.threshold = value;
  ui->lineThreshSliderValue->setText(QString::number(value));
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
  circleDetectionOnImage();
}


void HoughWidget::on_maxRaduisSlider_valueChanged(int value)
{
  ui->maxRaduisSliderValue->setText(QString::number(value));
}


void HoughWidget::on_betaSlider_sliderReleased()
{
  float value = mapSliderValue(0, 10, 0.1, ui->betaSlider);
  this->houghImage.beta = value;
  ui->betaValue->setText(QString::number(value));
  activeContourOnImage();
}


void HoughWidget::on_betaSlider_valueChanged(int value)
{
  float fvalue = mapSliderValue(0, 10, 0.1, ui->betaSlider);
  ui->betaValue->setText(QString::number(fvalue));}


void HoughWidget::on_alphaSlider_sliderReleased()
{
  float value = mapSliderValue(0, 10, 0.1, ui->alphaSlider);
  this->houghImage.alpha = value;
  ui->alphaValue->setText(QString::number(value));
  activeContourOnImage();
}


void HoughWidget::on_alphaSlider_valueChanged(int value)
{
  float fvalue = mapSliderValue(0, 10 ,0.1, ui->alphaSlider);
  ui->alphaValue->setText(QString::number(fvalue));
}


void HoughWidget::on_gammaSlider_sliderReleased()
{
  int value = ui->gammaSlider->value();
  this->houghImage.gamma = value;
  ui->gammaValue->setText(QString::number(value));
  activeContourOnImage();
}


void HoughWidget::on_gammaSlider_valueChanged(int value)
{
  ui->gammaValue->setText(QString::number(value));
}

void HoughWidget::on_activeContBtn_clicked()
{
  activeContourOnImage();
}

void HoughWidget::activeContourOnImage(){
  Mat activeContouredImage = ACTIVE_CONTOUR::active_contour(this->houghImage.originalImage,
                                                            50, // # of iterations
                                                            1, // Alpha
                                                            2, // Beta
                                                            5, // Gamma
                                                            80, // # of points
                                                            100, // init snake radius
                                                            150, // init snake CenterX Bias
                                                            50); // init snake CenterY Bias
  HelperFunctions::viewImageOnLabel(activeContouredImage, ui->imageFiltered);
}

float HoughWidget::mapSliderValue(float mappedLowerLimit, float mappedUpperLimit, float step, QSlider* slider) {
  float range = mappedUpperLimit - mappedLowerLimit;
  float factor = range / (slider->maximum() - slider->minimum());
  float fvalue = floor(slider->value() * factor / step + 0.5) * step + mappedLowerLimit;
  return fvalue;
}

void HoughWidget::on_downloadBtn_clicked()
{
  HelperFunctions::downloadImage(houghImage.shapeDetectedImage);
}

