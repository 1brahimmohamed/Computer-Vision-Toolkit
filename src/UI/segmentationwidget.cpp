#include "segmentationwidget.h"
#include "ui_segmentationwidget.h"

segmentationWidget::segmentationWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::segmentationWidget)
{
  ui->setupUi(this);
}

segmentationWidget::~segmentationWidget()
{
  delete ui;
}
