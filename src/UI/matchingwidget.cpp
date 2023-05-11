#include "matchingwidget.h"
#include "ui_matchingwidget.h"
#include "src/Helpers/helperfunctions.h"
#include "src/Harris/harrisoperator.h"
#include "src/SSD_NCC/ssd_ncc.h"


MatchingWidget::MatchingWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MatchingWidget)
{
  ui->setupUi(this);
}

MatchingWidget::~MatchingWidget()
{
  delete ui;
}


void MatchingWidget::updateLabel(Mat updatedImage, QLabel *pictureLable){
  HelperFunctions::viewImageOnLabel(updatedImage, pictureLable);
}

Mat MatchingWidget::operatingImage(){
  switch (this->whatPic) {
    case 2:
      return this->matchImage2;
    default:
      return this->matchImage1;
    }
}

void MatchingWidget::on_matchImage1Btn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows >1){
      this->matchImage1 = Image;
      updateLabel(Image, ui->picture1);
    }
}


void MatchingWidget::on_matchImage2Btn_clicked()
{
  Mat Image = HelperFunctions::readImage_Mat();
  if (Image.cols > 1 && Image.rows >1){
      this->matchImage2 = Image;
      updateLabel(Image, ui->picture2);
    }
}


void MatchingWidget::on_harrisApplyBtn_clicked()
{

  Mat operatingImg = operatingImage();
  if(!operatingImg.empty()){
      Mat output = HarrisOperator::HarrisDrivingFunction(operatingImg, 0.02);
      updateLabel(output, ui->resultPicture);
    }
}


void MatchingWidget::on_siftApllyBtn_clicked()
{

}


void MatchingWidget::on_matchApplyBtn_clicked()
{
  if(!matchImage1.empty() && !matchImage2.empty()){
    Mat output = SSD_NCC::matchImagesDriver(this->matchImage1, this->matchImage2);
    updateLabel(output, ui->matchingPicture);
  }
}


void MatchingWidget::on_checkBox_stateChanged(int arg1)
{
  this->whatPic = arg1;
}

