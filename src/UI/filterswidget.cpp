/******************************************************************************
 *
 * File Name: filterswidget.cpp
 * Description: Source file for Filters UI Widget
 * Author(s): Ibrahim Mohamed
 * Last Modified: 23 Mar 23 - 14:25
 *
 *******************************************************************************/



#include "filterswidget.h"
#include "ui_filterswidget.h"
#include "src/Helpers/helperfunctions.h"

#include "src/Filters/imagesmoothers.h"
#include "src/Filters/noiseaddatives.h"
#include "src/Filters/edgedetectors.h"
#include "src/Filters/threshold.h"

#include "src/Frequency/fouriermixer.h"

#include <QDebug>

FiltersWidget::FiltersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FiltersWidget)
{
  ui->setupUi(this);

  this->filtersWidgetImage.kernelSize = 5;
  this->filtersWidgetImage.mean = 20;
  this->filtersWidgetImage.sigma = 15.0;

  this->filtersWidgetImage.originalImage = NULL;
  this->filtersWidgetImage.filteredImage =NULL;
  this->filtersWidgetImage.currentImage = NULL;

  this->filtersWidgetImage.dNote = 30.0;
}

FiltersWidget::~FiltersWidget()
{
  delete ui;
}


// ------------------------------- GENERAL FUNCTIONS ------------------------------------- //

void FiltersWidget::updateFilteredPicture(Mat updatedImage){
  this->filtersWidgetImage.filteredImage = updatedImage;
  HelperFunctions::viewImageOnLabel(updatedImage, ui->imageFiltered);
}

void FiltersWidget::updateCurrentPicture(Mat updatedImage){
  this->filtersWidgetImage.currentImage = updatedImage;
  HelperFunctions::viewImageOnLabel(updatedImage,ui->imageOriginal);
}


// ------------------------------- EVENT LISENTERS FUNCTIONS ------------------------------------- //


// Upload & Download
void FiltersWidget::on_uploadBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows >1){
      this->filtersWidgetImage.originalImage = Image;
      updateCurrentPicture(Image);
    }
}

void FiltersWidget::on_downloadBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty())
    HelperFunctions::downloadImage(this->filtersWidgetImage.filteredImage);
}

// Add Noise
void FiltersWidget::on_uniformNoiseBtn_clicked()
{

}

void FiltersWidget::on_guassianNoiseBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = NoiseAddatives::GaussianNoise(this->filtersWidgetImage.currentImage,
                                                    this->filtersWidgetImage.sigma ,
                                                    this->filtersWidgetImage.mean);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_saltNoiseBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = NoiseAddatives::SaltAndPepperNoise(this->filtersWidgetImage.currentImage);
    updateFilteredPicture(outputImage);
  }
}


// Remove Noise
void FiltersWidget::on_avgFilterBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = ImageSmoothers::applyAverageFilter(this->filtersWidgetImage.currentImage, this->filtersWidgetImage.kernelSize);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_guasssianFilterBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = ImageSmoothers::applyGaussianFilter(this->filtersWidgetImage.currentImage,
                                                          this->filtersWidgetImage.kernelSize,
                                                          this->filtersWidgetImage.sigma);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_medianFilterBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = ImageSmoothers::applyMedianFilter(this->filtersWidgetImage.currentImage, this->filtersWidgetImage.kernelSize);
    updateFilteredPicture(outputImage);
  }
}


// Edge Detection
void FiltersWidget::on_sobelBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = EdgeDetectors::SobalEdgeDetector(this->filtersWidgetImage.currentImage);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_robertsBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = EdgeDetectors::RobertEdgeDetector(filtersWidgetImage.currentImage);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_prewittBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = EdgeDetectors::PerwittEdgeDetector(filtersWidgetImage.currentImage);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_cannyBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = EdgeDetectors::CannyEdgeDetector(filtersWidgetImage.currentImage);
    updateFilteredPicture(outputImage);
  }
}



// Frequency Filters
void FiltersWidget::on_lowPassBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = FourierMix::apply_filter(filtersWidgetImage.currentImage,
                                               "Ideal Low Pass",
                                               this->filtersWidgetImage.dNote);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_highPassBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = FourierMix::apply_filter(this->filtersWidgetImage.currentImage,
                                               "Ideal High Pass",
                                               this->filtersWidgetImage.dNote);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_freqGuassianBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    Mat outputImage = FourierMix::apply_filter(this->filtersWidgetImage.currentImage, "Gaussian", this->filtersWidgetImage.dNote);
    updateFilteredPicture(outputImage);
  }
}

void FiltersWidget::on_lThresholdingBtn_clicked()
{

  if(!filtersWidgetImage.currentImage.empty()){
    // Apply local thresholding with a block size of 11 and a k value of 0.2
    Mat localThresholdedImage = THRESHOLD_H::LocalThresholdImage(this->filtersWidgetImage.currentImage, 11, 0.2);
    HelperFunctions::viewImageOnLabel(localThresholdedImage, ui->imageFiltered);
  }

}

void FiltersWidget::on_gThresholdingBtn_clicked()
{
  if(!filtersWidgetImage.currentImage.empty()){
    // Apply global thresholding with a threshold value of 128
    Mat globalThresholdedImage = THRESHOLD_H::GlobalthresholdImage(this->filtersWidgetImage.currentImage, 128);
    HelperFunctions::viewImageOnLabel(globalThresholdedImage, ui->imageFiltered);
  }
}

// Sliders Handelers
void FiltersWidget::on_kernelSlider_valueChanged(int value)
{
  int boxVal;
  switch (value) {
    case 1:{
        boxVal = value;
        break;
      }
    case 2: {
        boxVal = value+1;
        break;
      }
    case 3: {
        boxVal =value+2;
        break;
      }
    case 4: {
        boxVal = value+3;
        break;
      }
    case 5: {
        boxVal = value+4;
        break;
      }
    case 6: {
        boxVal = value+5;
        break;
      }
    }
  ;

  this->filtersWidgetImage.kernelSize = boxVal;
  ui->kernelSliderValue->setText(QString::number(boxVal));
}

void FiltersWidget::on_sigmaSlider_valueChanged(int value)
{
  this->filtersWidgetImage.sigma = value;
  ui->sigmaSliderValue->setText(QString::number(value));
}

void FiltersWidget::on_meanSlider_valueChanged(int value)
{
  this->filtersWidgetImage.mean = value;
  ui->meanSliderValue->setText(QString::number(value));
}


// Apply & Reset
void FiltersWidget::on_applyBtn_clicked()
{
  updateCurrentPicture(this->filtersWidgetImage.filteredImage);
}

void FiltersWidget::on_resetBtn_clicked()
{
  updateCurrentPicture(this->filtersWidgetImage.originalImage);
}

