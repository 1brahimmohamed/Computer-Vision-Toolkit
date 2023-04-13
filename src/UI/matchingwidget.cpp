#include "matchingwidget.h"
#include "ui_matchingwidget.h"
#include "src/Helpers/helperfunctions.h"
#include "src/Harris/harrisoperator.h"


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
  Mat operatingImg;

  switch (this->whatPic) {
    case 2:
      operatingImg = this->matchImage2;
      break;
    default:
      operatingImg = this->matchImage1;
      break;
    }
  Mat output = HarrisOperator::HarrisDrivingFunction(operatingImg, 50.0);
  updateLabel(output, ui->resultPicture);
}


void MatchingWidget::on_siftApllyBtn_clicked()
{

}


void MatchingWidget::on_matchApplyBtn_clicked()
{

}


void MatchingWidget::on_checkBox_stateChanged(int arg1)
{
  this->whatPic = arg1;
}

