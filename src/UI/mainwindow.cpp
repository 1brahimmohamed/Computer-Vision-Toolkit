/******************************************************************************
 *
 * File Name: mainwindow.cpp
 * Description: Source file for Main Window UI Widget
 * Author(s): Ibrahim Mohamed
 * Last Modified: 24 Mar 23 - 14:01
 *
 *******************************************************************************/


#include "mainwindow.h"
#include "filterswidget.h"
#include "mixingwidget.h"
#include "histogramswidget.h"
#include "houghwidget.h"
#include "matchingwidget.h"
#include "segmentationwidget.h"
#include "facerecognitionwidget.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  index = 0;

  FiltersWidget *myFilterWidget = new FiltersWidget();
  MixingWidget *myMixingWidget = new MixingWidget();
  HistogramsWidget *myHistogramWidget = new HistogramsWidget();
  HoughWidget *myHoughWidget = new HoughWidget();
  MatchingWidget *myMatchingWidget = new MatchingWidget();
  segmentationWidget *mySegmentationWidget = new segmentationWidget();
  FaceRecognitionWidget *myFaceRecognitionWidget = new FaceRecognitionWidget();

  ui->stackedWidget->addWidget(myFilterWidget);
  ui->stackedWidget->addWidget(myMixingWidget);
  ui->stackedWidget->addWidget(myHistogramWidget);
  ui->stackedWidget->addWidget(myHoughWidget);
  ui->stackedWidget->addWidget(myMatchingWidget);
  ui->stackedWidget->addWidget(mySegmentationWidget);
  ui->stackedWidget->addWidget(myFaceRecognitionWidget);

  ui->stackedWidget->setCurrentIndex(index);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_btnPlus_clicked() {
  if(index < ui->stackedWidget->count() - 1){
      ui->stackedWidget->setCurrentIndex(++index);
      ui->pageIndex->setText(QString::number(index + 1));
    }
}


void MainWindow::on_btnMinus_clicked()
{
  if (index > 0){
      ui->stackedWidget->setCurrentIndex(--index);
      ui->pageIndex->setText(QString::number(index + 1));
    }
}

