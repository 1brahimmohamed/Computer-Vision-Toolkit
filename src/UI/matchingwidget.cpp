#include "matchingwidget.h"
#include "ui_matchingwidget.h"

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
