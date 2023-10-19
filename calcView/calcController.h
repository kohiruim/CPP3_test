#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H
#include "calcModel.h"

class CalcController {
 public:
  CalcController() = default;
  ~CalcController() = default;
  QString calc(QString input, QString x);
  void makeGraph(QVector<double>& x, QVector<double>& y, double x_start,
                 double x_end, double y_start, double y_end, QString input);

 private:
  CalcModel model_;
};

#endif  // CALCCONTROLLER_H
