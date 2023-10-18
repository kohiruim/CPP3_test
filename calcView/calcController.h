#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H
#include "calcModel.h"

class CalcController {
 public:
  CalcController() = default;
  ~CalcController() = default;
  QString calc(QString input, QString x);
  void makeGraph(QVector<double>& x, QVector<double>& y, double xStart,
                 double xEnd, double yStart, double yEnd, QString input);

 private:
  CalcModel model_;
};

#endif  // CALCCONTROLLER_H
