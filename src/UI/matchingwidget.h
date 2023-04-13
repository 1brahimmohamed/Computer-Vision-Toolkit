#ifndef MATCHINGWIDGET_H
#define MATCHINGWIDGET_H

#include <QWidget>

namespace Ui {
  class MatchingWidget;
}

class MatchingWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MatchingWidget(QWidget *parent = nullptr);
  ~MatchingWidget();

private:
  Ui::MatchingWidget *ui;
};

#endif // MATCHINGWIDGET_H
