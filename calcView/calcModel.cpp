#include "calcModel.h"

void CalcModel::setInput(QString input) { input_ = input; }

void CalcModel::setXvalue(QString input) { x_value_ = input.toDouble(); }

QString CalcModel::getResult() { return result_; }

void CalcModel::toPostfix() {
  QString str = "";
  for (size_t i = 0; i < (size_t)input_.length(); i++) {
    if (isDigit(input_[i])) {
      str += input_[i];
      if (((i + 1) == input_.length()) ||
          (!isDigit(input_[i + 1]) && input_[i] != '.')) {
        output_.push_back(str);
        str = "";
      }
    }
    readBrackets(i);
    i = readOperator(i);
    i = readFunction(i);
  }
  while (!stack_.isEmpty()) {
    output_.push_back(stack_.top());
    stack_.pop();
  }
}

size_t CalcModel::readOperator(size_t index) {
  QString str = "";
  if ((input_[index] == '+' || input_[index] == '-') &&
      ((index == 0) || (input_[index - 1] == '('))) {
    while (!stack_.isEmpty() && priority_[stack_.top()] >= 3) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    if (input_[index] == '+') {
      stack_.push_back("#");
    } else {
      stack_.push_back("~");
    }
  } else if ((priority_[input_[index]] <= 2 && priority_[input_[index]] != 0) ||
             input_[index] == 'm') {
    if (input_[index] == 'm') {
      str += "mo";
      index += 2;
    }
    while (!stack_.isEmpty() && priority_[stack_.top()] >= 2) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    str += input_[index];
    stack_.push_back(str);
    str = "";
  }
  return index;
}

size_t CalcModel::readFunction(size_t index) {
  QString str;
  if ((input_[index].isLetter() && input_[index] != 'X' &&
       input_[index] != 'd') ||
      input_[index] == '^') {
    while (!stack_.isEmpty() && priority_[stack_.top()] == 5) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    while (input_[index].isLetter() || input_[index] == '^') {
      str += input_[index];
      index++;
    }
    stack_.push(str);
    index--;
  }
  return index;
}

void CalcModel::readBrackets(size_t index) {
  if (input_[index] == '(') {
    stack_.push_back("(");
  }
  if (input_[index] == ')') {
    while (!stack_.isEmpty() && priority_[stack_.top()] > 0) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    if (stack_.top() == "(") {
      stack_.pop();
    }
  }
}

bool CalcModel::isDigit(QChar input) {
  bool res = false;
  if ((input >= '0' && input <= '9') || (input == 'X') || (input == '.')) {
    res = true;
  }
  return res;
}

bool CalcModel::isDigit(QString input) {
  bool res = true;
  for (int i = 0; i < input.length() && res; i++) {
    if (!(input[i] >= '0' && input[i] <= '9') && !(input[i] == 'X') &&
        !(input[i] == '.')) {
      res = false;
    }
  }
  return res;
}

void CalcModel::solutionFunction() {
  if (priority_[output_.front()] == 5) {
    double num = stack_.top().toDouble();

    if (output_.front() == "sin") {
      stack_.top() = QString::number(std::sin(num));
    } else if (output_.front() == "cos") {
      stack_.top() = QString::number(std::cos(num));
    } else if (output_.front() == "tan") {
      stack_.top() = QString::number(std::tan(num));
    } else if (output_.front() == "asin") {
      stack_.top() = QString::number(std::asin(num));
    } else if (output_.front() == "acos") {
      stack_.top() = QString::number(std::acos(num));
    } else if (output_.front() == "atan") {
      stack_.top() = QString::number(std::atan(num));
    } else if (output_.front() == "sqrt") {
      stack_.top() = QString::number(pow(num, 0.5));
    } else if (output_.front() == "ln") {
      stack_.top() = QString::number(std::log(num));
    } else if (output_.front() == "log") {
      stack_.top() = QString::number(std::log10(num));
    }
  }
}

void CalcModel::solutionOperator() {
  if (output_.front() == '~') {
    double num = stack_.top().toDouble();
    stack_.top() = QString::number(num * (-1));
  }
  if (priority_[output_.front()] == 1 || priority_[output_.front()] == 2 ||
      priority_[output_.front()] == 4) {
    double num2 = stack_.top().toDouble();
    stack_.pop();
    double num1 = stack_.top().toDouble();

    if (output_.front() == '+') {
      stack_.top() = QString::number(num1 + num2);
    } else if (output_.front() == '-') {
      stack_.top() = QString::number(num1 - num2);
    } else if (output_.front() == '*') {
      stack_.top() = QString::number(num1 * num2);
    } else if (output_.front() == '/') {
      stack_.top() = QString::number(num1 / num2);
    } else if (output_.front() == "mod") {
      stack_.top() = QString::number(std::fmod(num1, num2));
    } else if (output_.front() == '^') {
      stack_.top() = QString::number(pow(num1, num2));
    }
  }
}

void CalcModel::solution() {
  while (!output_.isEmpty()) {
    if (isDigit(output_.front())) {
      if (output_.front() == "X") {
        stack_.push(QString::number(x_value_));
      } else {
        stack_.push(output_.front());
      }
    }
    solutionOperator();
    solutionFunction();
    output_.pop_front();
  }
  result_ = stack_.top();
  stack_.pop();
}

void CalcModel::makeGraph(QVector<double>& x, QVector<double>& y, double x_start,
                          double x_end, double y_start, double y_end,
                          QString input) {
  x.clear();
  y.clear();
  input_ = input;
  double h = (x_end - x_start) / 20000;

  for (double X = x_start; X <= x_end; X += h) {
    x_value_ = X;
    toPostfix();
    solution();

    double yValue = result_.toDouble();

    if (!std::isnan(yValue)) {
      if (yValue >= y_start && yValue <= y_end) {
        x.push_back(X);
        y.push_back(yValue);
      }
    } else if (std::isnan(yValue) || std::isinf(yValue)) {
      x.push_back(X);
      y.push_back(std::numeric_limits<double>::quiet_NaN());
    }
  }
}
