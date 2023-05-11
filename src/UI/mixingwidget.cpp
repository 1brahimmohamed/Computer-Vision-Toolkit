/******************************************************************************
 *
 * File Name: mixingwidget.cpp
 * Description: Source file for Hybrid Image UI Widget
 * Author(s): Ibrahim Mohamed
 * Last Modified: 23 Mar 23 - 19:43
 *
 *******************************************************************************/


#include "mixingwidget.h"
#include "ui_mixingwidget.h"

#include "src/Helpers/helperfunctions.h"
#include "src/Frequency/fouriermixer.h"

MixingWidget::MixingWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MixingWidget)
{
  ui->setupUi(this);

  this->image1.dNote = 30.0;
  this->image2.dNote = 30.0;
}

MixingWidget::~MixingWidget()
{
  delete ui;
}

// Upload
void MixingWidget::uploadImage(MixingImage &ImageStruct, QLabel * Label){
  Mat Image = HelperFunctions::readImage_Mat();

  if (Image.cols != 1 && Image.rows != 1){
      ImageStruct.Image = Image;
      HelperFunctions::viewImageOnLabel(Image, Label);
    }
}
void MixingWidget::on_mixImage1Btn_clicked()
{
  uploadImage(this->image1, ui->picture1);
}
void MixingWidget::on_mixImage2Btn_clicked()
{
  uploadImage(this->image2, ui->picture2);
}


// Mixing
void MixingWidget::mixImages(){
  Mat outputImageHigh = FourierMix::apply_filter(this->image1.Image, "Ideal High Pass", this->image1.dNote);
  Mat outputImageLow = FourierMix::apply_filter(this->image2.Image, "Ideal Low Pass", this->image2.dNote);
  Mat mixed = FourierMix::mix_images(outputImageHigh, outputImageLow);

  HelperFunctions::viewImageOnLabel(mixed, ui->pictureMixed);
}
void MixingWidget::on_mixBtn_clicked()
{
  if(!image1.Image.empty() && !image2.Image.empty())
    mixImages();
}
void MixingWidget::on_image1D0Slider_valueChanged(int value)
{
  image1.dNote = value;
  ui->image1D0SliderValue->setText(QString::number(value));
  if(!image1.Image.empty() && !image2.Image.empty())
    mixImages();
}
void MixingWidget::on_kernelSlider_4_valueChanged(int value)
{
  image2.dNote = value;
  ui->image2D0SliderValue->setText(QString::number(value));
  if(!image1.Image.empty() && !image2.Image.empty())
    mixImages();
}

