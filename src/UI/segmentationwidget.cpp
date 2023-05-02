#include "segmentationwidget.h"
#include "ui_segmentationwidget.h"
#include "src/Helpers/helperfunctions.h"
#include "src/Segmentation/meanshift.h"
#include "src/Thresholding/Thresholding.h"
#include "src/Filters/threshold.h"
#include "src/Segmentation/regiongrowing.h"
#include "src/Segmentation/agglomerative.h"

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


// Thresholding
void segmentationWidget::on_optimalThresBtn_clicked()
{
  Mat segementedImage = Thresholding::getOptimalThreshold(segmentationWidgetImage.currentImage,
                                                          segmentationWidgetImage.maxItrs,
                                                          segmentationWidgetImage.optimalThreshold);
  updateSegmentedPicture(segementedImage);
}

void segmentationWidget::on_otsuBtn_clicked()
{
  Mat segementedImage = Thresholding::Otsu(segmentationWidgetImage.currentImage);
  updateSegmentedPicture(segementedImage);
}

void segmentationWidget::on_localThresBtn_clicked()
{
  // Apply local thresholding with a block size of 11 and a k value of 0.2
  Mat localThresholdedImage = THRESHOLD_H::LocalThresholdImage(this->segmentationWidgetImage.currentImage, 11, 0.2);
  HelperFunctions::viewImageOnLabel(localThresholdedImage, ui->imageSegmented);

}

void segmentationWidget::on_globalThresBtn_clicked()
{
  // Apply global thresholding with a threshold value of 128
  Mat globalThresholdedImage = THRESHOLD_H::GlobalthresholdImage(this->segmentationWidgetImage.currentImage, 50);
  HelperFunctions::viewImageOnLabel(globalThresholdedImage, ui->imageSegmented);
}

// Segmentation
void segmentationWidget::on_meanshiftBtn_clicked()
{
  Mat segementedImage = MeanShift::MeanShiftSegmentation(segmentationWidgetImage.currentImage,
                                                         segmentationWidgetImage.distanceBandWidth,
                                                         segmentationWidgetImage.colorBandWidth);
  updateSegmentedPicture(segementedImage);
}

void segmentationWidget::on_regionGrowingBtn_clicked()
{
  Mat segementedImage = RegionGrowing::growRegion(segmentationWidgetImage.currentImage,
                                                  segmentationWidgetImage.seedX,
                                                  segmentationWidgetImage.seedY,
                                                  segmentationWidgetImage.regionGrowThreshold,
                                                  segmentationWidgetImage.imageSize);

  HelperFunctions::viewImageOnLabel(segementedImage, ui->imageSegmented);
}


void segmentationWidget::on_agglomerativeBtn_clicked()
{
  Mat segementedImage = Agglomerative::agglomarativeSegmentation(segmentationWidgetImage.currentImage,5);
  updateSegmentedPicture(segementedImage);
}

