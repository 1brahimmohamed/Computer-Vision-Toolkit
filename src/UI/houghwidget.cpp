
#include "houghwidget.h"
#include "ui_houghwidget.h"

#include "houghwidget.h"
#include "src/Helpers/helperfunctions.h"

#include "src/Hough/houghcircle.h"
#include "src/Hough/houghline.h"
#include "src/Hough/houghellipse.h"


HoughWidget::HoughWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::HoughWidget)
{
  ui->setupUi(this);
  this->houghImage.threshold = 150;
  this->houghImage.maxRaduis = 35;
  this->houghImage.minRaduis = 10;
}

HoughWidget::~HoughWidget()
{
  delete ui;
}

// ------------------------------- EVENT LISENTERS FUNCTIONS ------------------------------------- //


// Upload & Download
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


// Line Detetcion
void HoughWidget::on_lineBtn_clicked()
{
  lineDetectionOnImage();
}
void HoughWidget::lineDetectionOnImage(){
  this->houghImage.shapeDetectedImage = HoughLine::detectLines(this->houghImage.originalImage, this->houghImage.threshold);
  HelperFunctions::viewImageOnLabel(this->houghImage.shapeDetectedImage, ui->imageFiltered);
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

// Circle Detetcion
void HoughWidget::on_circleBtn_clicked()
{
  circleDetectionOnImage();
}
void HoughWidget::circleDetectionOnImage(){
  houghImage.shapeDetectedImage = HoughCircle::HoughCircleCall(houghImage.originalImage, houghImage.minRaduis, houghImage.maxRaduis);
  HelperFunctions::viewImageOnLabel(houghImage.shapeDetectedImage, ui->imageFiltered);
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

// Ellipse Detetcion
void HoughWidget::on_ellipseBtn_clicked()
{
  this->houghImage.shapeDetectedImage = HoughEllipse::houghEllipseDetection(this->houghImage.originalImage, 10, 10, 10, 10);
  HelperFunctions::viewImageOnLabel(this->houghImage.shapeDetectedImage, ui->imageFiltered);
}

// Active Contour
void HoughWidget::on_activeContBtn_clicked()
{
  // @TODO: Some Function
}
void HoughWidget::on_betaSlider_sliderReleased()
{
  int value = ui->betaSlider->value();
  this->houghImage.beta = value;
  ui->betaValue->setText(QString::number(value));
  // @TODO: Some Function
}
void HoughWidget::on_betaSlider_valueChanged(int value)
{
  ui->betaValue->setText(QString::number(value));
}
void HoughWidget::on_alphaSlider_sliderReleased()
{
  int value = ui->alphaSlider->value();
  this->houghImage.alpha = value;
  ui->alphaValue->setText(QString::number(value));
  // @TODO: Some Function
}
void HoughWidget::on_alphaSlider_valueChanged(int value)
{
  ui->alphaValue->setText(QString::number(value));
}
void HoughWidget::on_gammaSlider_sliderReleased()
{
  int value = ui->gammaSlider->value();
  this->houghImage.gamma = value;
  ui->gammaValue->setText(QString::number(value));
  // @TODO: Some Function
}
void HoughWidget::on_gammaSlider_valueChanged(int value)
{
  ui->gammaValue->setText(QString::number(value));
}



