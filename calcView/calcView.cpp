#include "calcView.h"

#include "ui_calcView.h"

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalcView) {
  ui->setupUi(this);
  QVector<QPushButton *> buttonValue{
      ui->zero,  ui->one,  ui->two,         ui->three,
      ui->four,  ui->five, ui->six,         ui->seven,
      ui->eight, ui->nine, ui->openBracket, ui->closingBracket};
  QVector<QPushButton *> buttonFunctions{ui->sin,  ui->asin, ui->cos,
                                         ui->acos, ui->tan,  ui->atan,
                                         ui->ln,   ui->log,  ui->sqrt};
  QVector<QPushButton *> buttonOperator{ui->plus,   ui->minus, ui->multiply,
                                        ui->divide, ui->mod,   ui->power,
                                        ui->dot};

  for (int i = 0; i < buttonValue.size(); i++) {
    connect(buttonValue[i], SIGNAL(clicked()), this, SLOT(printButtonValue()));
  }
  for (int i = 0; i < buttonFunctions.size(); i++) {
    connect(buttonFunctions[i], SIGNAL(clicked()), this, SLOT(printFunction()));
  }
  for (int i = 0; i < buttonOperator.size(); i++) {
    connect(buttonOperator[i], SIGNAL(clicked()), this, SLOT(printOperator()));
  }
  connect(ui->X, SIGNAL(clicked()), this, SLOT(printX()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(on_dot_clicked()));
}

CalcView::~CalcView() { delete ui; }

void CalcView::printButtonValue() {
  QPushButton *button = (QPushButton *)sender();
  QString inputStr = ui->input->text();
  int len = inputStr.length();
  int countOpenBracker = std::count(inputStr.begin(), inputStr.end(), '(');
  int countClosingBracker = std::count(inputStr.begin(), inputStr.end(), ')');

  if (len < 256) {
    if (button->text() == '(') {
      if (len == 0 || inputStr[len - 1] == '+' || inputStr[len - 1] == '-' ||
          inputStr[len - 1] == '*' || inputStr[len - 1] == '/' ||
          inputStr[len - 1] == '^' || inputStr[len - 1] == 'd' ||
          inputStr[len - 1] == '(') {
        inputStr = (ui->input->text() + button->text());
        ui->input->setText(inputStr);
      }
    } else if (button->text() == ')') {
      if (len > 0 && (countOpenBracker > countClosingBracker) &&
          (inputStr[len - 1].isDigit() || inputStr[len - 1] == 'X' ||
           inputStr[len - 1] == ')')) {
        inputStr = (ui->input->text() + button->text());
        ui->input->setText(inputStr);
      }
    } else if (len == 0 ||
               (inputStr[len - 1] != 'X' && inputStr[len - 1] != ')')) {
      inputStr = (ui->input->text() + button->text());
      ui->input->setText(inputStr);
    }
  } else {
    ui->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::printX() {
  QPushButton *button = (QPushButton *)sender();
  QString inputStr = ui->input->text();
  int len = inputStr.length();
  if (len < 256) {
    if (len == 0) {
      inputStr = (ui->input->text() + button->text());
      ui->input->setText(inputStr);
    } else {
      if (inputStr[len - 1] == '(' || inputStr[len - 1] == '+' ||
          inputStr[len - 1] == '-' || inputStr[len - 1] == '*' ||
          inputStr[len - 1] == '/' || inputStr[len - 1] == 'd' ||
          inputStr[len - 1] == '^') {
        inputStr = (ui->input->text() + button->text());
        ui->input->setText(inputStr);
      }
    }
  } else {
    ui->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::printUnary() {
  QPushButton *button = (QPushButton *)sender();
  QString inputStr = ui->input->text();
  int len = inputStr.length();

  if (len == 0) {
    if (button->text() == "+" || button->text() == "-") {
      inputStr = (ui->input->text() + button->text());
      ui->input->setText(inputStr);
    }
  } else if (len == 1 &&
             (inputStr[len - 1] == '+' || inputStr[len - 1] == '-')) {
    if (button->text() == "+" || button->text() == "-") {
      inputStr.chop(1);
      ui->input->setText(inputStr);
      inputStr = (ui->input->text() + button->text());
      ui->input->setText(inputStr);
    }
  } else if (len > 1 &&
             (inputStr[len - 1] == '+' || inputStr[len - 1] == '-') &&
             (inputStr[len - 2] == '(') &&
             (button->text() == "+" || button->text() == "-")) {
    inputStr.chop(1);
    ui->input->setText(inputStr);
    inputStr = (ui->input->text() + button->text());
    ui->input->setText(inputStr);
  } else if (len > 0 && inputStr[len - 1] == '(' &&
             (button->text() == "+" || button->text() == "-")) {
    inputStr = (ui->input->text() + button->text());
    ui->input->setText(inputStr);
  }
}

void CalcView::printOperator() {
  QPushButton *button = (QPushButton *)sender();
  QString inputStr = ui->input->text();
  int len = inputStr.length();

  printUnary();
  if (len > 0 && len < 256) {
    if (inputStr[len - 1].isDigit() || inputStr[len - 1] == ')' ||
        inputStr[len - 1] == 'X') {
      inputStr = (ui->input->text() + button->text());
      ui->input->setText(inputStr);
    } else {
      printUnary();
      if (inputStr[len - 1] == 'd') {
        inputStr.chop(3);
        ui->input->setText(inputStr);
        inputStr = (ui->input->text() + button->text());
        ui->input->setText(inputStr);
      } else if (len > 1 &&
                 (inputStr[len - 2].isDigit() || inputStr[len - 2] == ')' ||
                  inputStr[len - 2] == 'X')) {
        inputStr.chop(1);
        ui->input->setText(inputStr);
        inputStr = (ui->input->text() + button->text());
        ui->input->setText(inputStr);
      }
    }
  } else if (len >= 256) {
    ui->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::printFunction() {
  QPushButton *button = (QPushButton *)sender();
  QString inputStr = ui->input->text();
  inputStr = ui->input->text();
  int len = inputStr.size();
  if (len == 0) {
    ui->input->setText(inputStr + button->text() + "(");
  } else if (len < 256 &&
             (inputStr[len - 1] == '(' || inputStr[len - 1] == '+' ||
              inputStr[len - 1] == '-' || inputStr[len - 1] == '*' ||
              inputStr[len - 1] == '/' || inputStr[len - 1] == '^')) {
    ui->input->setText(inputStr + button->text() + "(");
  }
  if (len >= 256) {
    ui->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::on_dot_clicked() {
  QString inputStr = ui->input->text();
  int len = inputStr.length();
  int status = 0;

  if (len < 256) {
    if (len != 0 && inputStr[len - 1].isDigit()) {
      int index = 1;
      while (inputStr[len - index].isDigit() && len != index) {
        if (inputStr[len - index - 1] == '.') {
          status = 1;
        }
        index++;
      }
      if (status == 0) {
        inputStr = (ui->input->text() + '.');
        ui->input->setText(inputStr);
      }
    }
  } else {
    ui->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::on_AC_clicked() {
  ui->input->setText("");
  ui->output->setText("");
}

void CalcView::on_CE_clicked() {
  QString inputStr = ui->input->text();
  int len = inputStr.length();
  if (len > 0) {
    if (inputStr[len - 1] == 'd') {
      inputStr.chop(3);
    } else if (inputStr.isEmpty()) {
      ui->output->setText("");
    } else if (len > 2 && inputStr[len - 1] == '(' &&
               inputStr[len - 2] >= 'a' && inputStr[len - 2] <= 'z') {
      int count = 0;
      while (len > 0 &&
             ((inputStr[len - 1] >= 'a' && inputStr[len - 1] <= 'z') ||
              inputStr[len - 1] == '(')) {
        len--;
        count++;
      }
      inputStr.chop(count);
    } else {
      inputStr.chop(1);
    }
    ui->input->setText(inputStr);
  }
}

bool CalcView::validX(QString input) {
  bool result = true;
  int countDot = 0;
  if (input.isEmpty()) {
    result = false;
  } else {
    for (int i = 0; i < input.length() && result; i++) {
      if (input[i] == '.') {
        countDot++;
      }
      if (!((input[i] == '.' || input[i].isDigit()) && countDot < 2) ||
          input[0] == '0') {
        result = false;
      }
      if ((input.length() > 1) && (i == 0) &&
          (input[i] == '+' || input[i] == '-') && (input[1] != '0')) {
        result = true;
      }
    }
  }
  return result;
}

bool CalcView::check_last_element(QString input) {
  bool result = true;
  QString x = ui->xValue->text();

  int countOpenBracker = std::count(input.begin(), input.end(), '(');
  int countClosingBracker = std::count(input.begin(), input.end(), ')');
  int len = input.length();

  if (len > 256) {
    result = false;
    ui->output->setText("Длинное выражение");
  } else if (countOpenBracker != countClosingBracker) {
    result = false;
    ui->output->setText("Проблема со скобками");
  } else if (input.isEmpty()) {
    result = false;
    ui->output->setText("Пустая строка");
  } else if ((input[len - 1] != ')' && input[len - 1] != 'X') &&
             !input[len - 1].isDigit()) {
    result = false;
    ui->output->setText("Неверное выражение");
  }
  return result;
}

void CalcView::on_equals_clicked() {
  QString input = ui->input->text();
  QString x = ui->xValue->text();
  if (input.isEmpty()) {
    ui->output->setText("Пустая строка");
  }
  if ((input.contains('X') != 0) && ui->xValue->text().isEmpty()) {
    ui->output->setText("Напиши значение Х");
  } else if (input.contains('X') != 0 && !validX(ui->xValue->text())) {
    ui->xValue->setText("что-то не так");
  } else if (check_last_element(ui->input->text())) {
    QString result = controller_.calc(input, x);
    ui->output->setText(result);
  }
}

void CalcView::on_graph_clicked() {
  if (check_last_element(ui->input->text())) {
    ui->widget->clearGraphs();
    ui->widget->replot();

    double xStart = ui->xStart->text().toDouble();
    double xEnd = ui->xEnd->text().toDouble();
    double yStart = ui->yStart->text().toDouble();
    double yEnd = ui->yEnd->text().toDouble();

    if (xStart > xEnd) {
        std::swap(xStart, xEnd);
    } else if (yStart > yEnd) {
        std::swap(yStart, yEnd);
    }
    ui->widget->xAxis->setRange(xStart, xEnd);
    ui->widget->yAxis->setRange(yStart, yEnd);
    QVector<double> x, y;

    controller_.makeGraph(x, y, xStart, xEnd, yStart, yEnd, ui->input->text());

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setPen(QColor(84, 84, 84));
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui->widget->replot();
  }
}
