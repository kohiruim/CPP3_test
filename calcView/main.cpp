#include <QApplication>

#include "calcView.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CalcView w;
  w.show();
  return a.exec();
}
