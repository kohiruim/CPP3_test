#include <QApplication>

#include "calcView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::CalcView w;
  w.show();
  return a.exec();
}
