#include "calcController.h"
namespace s21 {
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
                               double x_start, double x_end, double y_start,
                               double y_end, QString input) {
  model_.makeGraph(x, y, x_start, x_end, y_start, y_end, input);
}
}  // namespace s21
