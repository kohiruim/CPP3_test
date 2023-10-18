#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QMainWindow>
#include <QVector>
#include <limits>

#include "calcController.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

class CalcView : public QMainWindow {
  Q_OBJECT

 public:
  CalcView(QWidget *parent = nullptr);
  ~CalcView();
 private slots:
  void printButtonValue();
  void printX();
  void printOperator();
  void printFunction();
  void on_dot_clicked();
  void on_AC_clicked();
  void on_CE_clicked();
  void on_equals_clicked();
  bool validX(QString input);
  void on_graph_clicked();
  bool check_last_element(QString input);
  void printUnary();

 private:
  Ui::CalcView *ui;
  CalcController controller_;
};
#endif  // CALCVIEW_H
