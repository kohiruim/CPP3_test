#include "calcController.h"

QString CalcController::calc(QString input, QString x) {
  if (!x.isEmpty()) {
    model_.setXvalue(x);
  }
  model_.setInput(input);
  model_.toPostfix();
  model_.solution();

  return model_.getResult();
}

void CalcController::makeGraph(QVector<double>& x, QVector<double>& y,
                               double xStart, double xEnd, double yStart,
                               double yEnd, QString input) {
  model_.makeGraph(x, y, xStart, xEnd, yStart, yEnd, input);
}
