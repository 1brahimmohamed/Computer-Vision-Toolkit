#include "mainwindow.h"
#include "filterswidget.h"
#include "mixingwidget.h"
#include "histogramswidget.h"
#include "houghwidget.h"

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
  HoughWidget * muHoughWidget = new HoughWidget();


  ui->stackedWidget->addWidget(myFilterWidget);
  ui->stackedWidget->addWidget(myMixingWidget);
  ui->stackedWidget->addWidget(myHistogramWidget);
  ui->stackedWidget->addWidget(muHoughWidget);

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

