#ifndef CALCVIEW_H
#define CALCVIEW_H

#include <QMainWindow>
#include <QVector>
#include <limits>
#include <QMessageBox>
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
  void onDotClicked();
  void onACClicked();
  void onCEClicked();
  void onXClicked();
  void printButtonValue();
  void printUnary();
  void onOperatorClicked();
  void onFunctionClicked();
  void onEqualsClicked();
  void onGraphClicked();

 private:
  Ui::CalcView *ui_;
  CalcController controller_;

  bool validNum(QString input);
  bool checkLastElement(QString input);
  bool checkGraphInput(QVector<QString> values);
};
#endif  // CALCVIEW_H
