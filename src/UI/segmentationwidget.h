#ifndef SEGMENTATIONWIDGET_H
#define SEGMENTATIONWIDGET_H

#include <QWidget>

namespace Ui {
  class segmentationWidget;
}

class segmentationWidget : public QWidget
{
  Q_OBJECT

public:
  explicit segmentationWidget(QWidget *parent = nullptr);
  ~segmentationWidget();

private:
  Ui::segmentationWidget *ui;
};

#endif // SEGMENTATIONWIDGET_H
