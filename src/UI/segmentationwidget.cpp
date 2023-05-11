#include "segmentationwidget.h"
#include "ui_segmentationwidget.h"
#include "src/Helpers/helperfunctions.h"

#include "src/Filters/threshold.h"
#include "src/Thresholding/Thresholding.h"
#include "src/Segmentation/regiongrowing.h"
#include "src/Segmentation/agglomerative.h"
#include "src/Segmentation/meanshift.h"
#include "src/Segmentation/kmeanssegmentation.h"


segmentationWidget::segmentationWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::segmentationWidget)
{
  ui->setupUi(this);
  this->segmentationWidgetImage.currentImage = NULL;
  this->segmentationWidgetImage.originalImage = NULL;
  this->segmentationWidgetImage.segmentedImage = NULL;
  this->segmentationWidgetImage.distanceBandWidth = 8;
  this->segmentationWidgetImage.colorBandWidth = 16;
  this->segmentationWidgetImage.maxItrs = 50;
  this->segmentationWidgetImage.optimalThreshold = 100;
  this->segmentationWidgetImage.regionGrowThreshold = 15;
  this->segmentationWidgetImage.seedX = 200;
  this->segmentationWidgetImage.seedY = 400;
  this->segmentationWidgetImage.imageSize = cv::Size(800,800);
  this->segmentationWidgetImage.numberOfClusters = 5;

}

segmentationWidget::~segmentationWidget()
{
  delete ui;
}


// ------------------------------- GENERAL FUNCTIONS ------------------------------------- //

void segmentationWidget::updateSegmentedPicture(Mat updatedImage){
  this->segmentationWidgetImage.segmentedImage = updatedImage;
  HelperFunctions::viewImageOnLabel(updatedImage, ui->imageSegmented);
}

void segmentationWidget::updateCurrentPicture(Mat updatedImage){
  this->segmentationWidgetImage.currentImage = updatedImage;
  HelperFunctions::viewImageOnLabel(updatedImage,ui->imageOriginalSeg);
}

void segmentationWidget::on_segUploadBtn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows >1){
      this->segmentationWidgetImage.originalImage = Image;
      updateCurrentPicture(Image);
    }
}

void segmentationWidget::on_segDownloadBtn_clicked()
{

  if(!segmentationWidgetImage.currentImage.empty())
    HelperFunctions::downloadImage(this->segmentationWidgetImage.segmentedImage);

}


// Thresholding
void segmentationWidget::applyOptimalThreshold(){

  if(!segmentationWidgetImage.currentImage.empty())
    {
      Mat segementedImage = Thresholding::getOptimalThreshold(segmentationWidgetImage.currentImage,
                                                              segmentationWidgetImage.maxItrs,
                                                              segmentationWidgetImage.optimalThreshold);
      updateSegmentedPicture(segementedImage);
    }
}

void segmentationWidget::on_optimalThresBtn_clicked()
{
  ui->optionsWidget->setCurrentIndex(0);

  if(!segmentationWidgetImage.currentImage.empty())
    {
      applyOptimalThreshold();
    }
}

void segmentationWidget::on_otsuBtn_clicked()
{
  if(!segmentationWidgetImage.currentImage.empty())
    {
      Mat segementedImage = Thresholding::Otsu(segmentationWidgetImage.currentImage);
      updateSegmentedPicture(segementedImage);
    }
}

void segmentationWidget::on_localThresBtn_clicked()
{
  if(!segmentationWidgetImage.currentImage.empty())
    {
      // Apply local thresholding with a block size of 11 and a k value of 0.2
      Mat localThresholdedImage = THRESHOLD_H::LocalThresholdImage(this->segmentationWidgetImage.currentImage, 11, 0.2);
      HelperFunctions::viewImageOnLabel(localThresholdedImage, ui->imageSegmented);
    }

}

void segmentationWidget::on_globalThresBtn_clicked()
{
  if(!segmentationWidgetImage.currentImage.empty())
    {
      // Apply global thresholding with a threshold value of 128
      Mat globalThresholdedImage = THRESHOLD_H::GlobalthresholdImage(this->segmentationWidgetImage.currentImage, 50);
      HelperFunctions::viewImageOnLabel(globalThresholdedImage, ui->imageSegmented);
    }
}

// Segmentation
void segmentationWidget::applyMeanShift(){
  if(!segmentationWidgetImage.currentImage.empty())
    {
      Mat segementedImage = MeanShift::MeanShiftSegmentation(segmentationWidgetImage.currentImage,
                                                             segmentationWidgetImage.distanceBandWidth,
                                                             segmentationWidgetImage.colorBandWidth);
      updateSegmentedPicture(segementedImage);
    }
}
void segmentationWidget::applyRegionGrowing(){
  if(!segmentationWidgetImage.currentImage.empty())
    {
      Mat segementedImage = RegionGrowing::growRegion(segmentationWidgetImage.currentImage,
                                                      segmentationWidgetImage.seedX,
                                                      segmentationWidgetImage.seedY,
                                                      segmentationWidgetImage.regionGrowThreshold,
                                                      segmentationWidgetImage.imageSize);
      updateSegmentedPicture(segementedImage);
    }
}
void segmentationWidget::applyAgglomerative(){
  if(!segmentationWidgetImage.currentImage.empty())
    {
      Mat segementedImage = Agglomerative::agglomarativeSegmentation(segmentationWidgetImage.currentImage,
                                                                     segmentationWidgetImage.numberOfClusters);
      updateSegmentedPicture(segementedImage);
    }
}
void segmentationWidget::applyKMeans(){
  if(!segmentationWidgetImage.currentImage.empty())
    {
      Mat segementedImage = KmeansSegmentation::KmeansDrivingFunction(segmentationWidgetImage.currentImage,
                                                                      segmentationWidgetImage.numberOfClusters);
      updateSegmentedPicture(segementedImage);
    }
}


void segmentationWidget::on_meanshiftBtn_clicked()
{
  ui->optionsWidget->setCurrentIndex(1);

  if(!segmentationWidgetImage.currentImage.empty())
    applyMeanShift();

}

void segmentationWidget::on_regionGrowingBtn_clicked()
{
  ui->optionsWidget->setCurrentIndex(2);

  if(!segmentationWidgetImage.currentImage.empty())
    applyRegionGrowing();
}

void segmentationWidget::on_agglomerativeBtn_clicked()
{
  ui->optionsWidget->setCurrentIndex(3);

  if(!segmentationWidgetImage.currentImage.empty())
    applyAgglomerative();
}

void segmentationWidget::on_kmeanBtn_clicked()
{
  ui->optionsWidget->setCurrentIndex(3);
  if(!segmentationWidgetImage.currentImage.empty())
    applyKMeans();
}

// Optimal Thrshold
void segmentationWidget::on_maxItrSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyOptimalThreshold();
}

void segmentationWidget::on_maxItrSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.maxItrs = value;
  ui->maxItrVal->setText(QString::number(value));
}

void segmentationWidget::on_optThresSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyOptimalThreshold();
}

void segmentationWidget::on_optThresSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.optimalThreshold = value;
  ui->optThresSliderValue->setText(QString::number(value));
}



// Mean Shift
void segmentationWidget::on_colorBandSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyMeanShift();
}

void segmentationWidget::on_colorBandSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.colorBandWidth = value;
  ui->colorBandVal->setText(QString::number(value));
}

void segmentationWidget::on_distanceBandSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyMeanShift();
}

void segmentationWidget::on_distanceBandSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.distanceBandWidth = value;
  ui->distanceBandSliderValue->setText(QString::number(value));
}


// Kmeans & Agglomerative
void segmentationWidget::on_nClustersSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyAgglomerative();
}


void segmentationWidget::on_nClustersSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.numberOfClusters = value;
  ui->nClustersSliderValue->setText(QString::number(value));
}


void segmentationWidget::on_seedXSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyRegionGrowing();
}


void segmentationWidget::on_seedXSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.seedX = value;
  ui->seedXSliderValue->setText(QString::number(value));
}


void segmentationWidget::on_seedYSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyRegionGrowing();
}


void segmentationWidget::on_seedYSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.seedY = value;
  ui->seedYSliderValue->setText(QString::number(value));
}


void segmentationWidget::on_rGrowThresholdSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyRegionGrowing();

}


void segmentationWidget::on_rGrowThresholdSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.regionGrowThreshold = value;
  ui->rGrowThresholdSliderValue->setText(QString::number(value));
}


void segmentationWidget::on_kClustersSlider_sliderReleased()
{
  if(!segmentationWidgetImage.currentImage.empty())
    applyKMeans();
}

void segmentationWidget::on_kClustersSlider_valueChanged(int value)
{
  this->segmentationWidgetImage.numberOfClusters = value;
  ui->kClustersSliderValue->setText(QString::number(value));
}




