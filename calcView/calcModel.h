#ifndef CALCMODEL_H
#define CALCMODEL_H
#include <QChar>
#include <QDebug>
#include <QSet>
#include <Qqueue>
#include <Qstack>
#include <algorithm>

class CalcModel {
 public:
  CalcModel() = default;
  ~CalcModel() = default;
  void setXvalue(QString input);
  void setInput(QString input);
  void toPostfix();
  void solution();
  QString getResult();
  void makeGraph(QVector<double>& x, QVector<double>& y, double x_start,
                 double x_end, double y_start, double y_end, QString input);

 private:
  QString input_;
  QStack<QString> stack_;
  QQueue<QString> output_;
  QString result_ = "";
  double x_value_ = 0;
  QMap<QString, int> priority_ = {
      {"+", 1},   {"-", 1},    {"*", 2},    {"/", 2},    {"mod", 2},
      {"#", 3},   {"~", 3},    {"^", 4},    {"sin", 5},  {"cos", 5},
      {"tan", 5}, {"atan", 5}, {"asin", 5}, {"acos", 5}, {"ln", 5},
      {"log", 5}, {"sqrt", 5},
  };

  bool isDigit(QChar input);
  bool isDigit(QString input);
  size_t readFunction(size_t index);
  size_t readOperator(size_t index);
  void readBrackets(size_t index);
  void solutionFunction();
  void solutionOperator();
};

#endif  // CALCMODEL_H
