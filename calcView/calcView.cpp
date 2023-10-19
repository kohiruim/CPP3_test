#include "calcView.h"
#include "ui_calcView.h"

CalcView::CalcView(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::CalcView) {
  ui_->setupUi(this);

  QVector<QPushButton *> button_value{
      ui_->zero,  ui_->one,  ui_->two,         ui_->three,
      ui_->four,  ui_->five, ui_->six,         ui_->seven,
      ui_->eight, ui_->nine, ui_->openBracket, ui_->closingBracket};
  QVector<QPushButton *> button_functions{ui_->sin,  ui_->asin, ui_->cos,
                                         ui_->acos, ui_->tan,  ui_->atan,
                                         ui_->ln,   ui_->log,  ui_->sqrt};
  QVector<QPushButton *> button_operator{ui_->plus,   ui_->minus, ui_->multiply,
                                        ui_->divide, ui_->mod,   ui_->power,
                                        ui_->dot};

  for (int i = 0; i < button_value.size(); i++) {
    connect(button_value[i], SIGNAL(clicked()), this, SLOT(printButtonValue()));
  }
  for (int i = 0; i < button_functions.size(); i++) {
    connect(button_functions[i], SIGNAL(clicked()), this, SLOT(onFunctionClicked()));
  }
  for (int i = 0; i < button_operator.size(); i++) {
    connect(button_operator[i], SIGNAL(clicked()), this, SLOT(onOperatorClicked()));
  }
  connect(ui_->X, SIGNAL(clicked()), this, SLOT(onXClicked()));
  connect(ui_->dot, SIGNAL(clicked()), this, SLOT(onDotClicked()));
  connect(ui_->AC, SIGNAL(clicked()), this, SLOT(onACClicked()));
  connect(ui_->CE, SIGNAL(clicked()), this, SLOT(onCEClicked()));

  connect(ui_->equals, SIGNAL(clicked()), this, SLOT(onEqualsClicked()));
  connect(ui_->graph, SIGNAL(clicked()), this, SLOT(onGraphClicked()));
}

CalcView::~CalcView() { delete ui_; }

void CalcView::printButtonValue() {
  QPushButton *button = (QPushButton *)sender();
  QString input_str = ui_->input->text();
  int len = input_str.length();
  int count_open_bracker = std::count(input_str.begin(), input_str.end(), '(');
  int count_closing_bracker = std::count(input_str.begin(), input_str.end(), ')');

  if (len < 256) {
    if (button->text() == '(') {
      if (len == 0 || input_str[len - 1] == '+' || input_str[len - 1] == '-' ||
          input_str[len - 1] == '*' || input_str[len - 1] == '/' ||
          input_str[len - 1] == '^' || input_str[len - 1] == 'd' ||
          input_str[len - 1] == '(') {
        input_str = (ui_->input->text() + button->text());
        ui_->input->setText(input_str);
      }
    } else if (button->text() == ')') {
      if (len > 0 && (count_open_bracker > count_closing_bracker) &&
          (input_str[len - 1].isDigit() || input_str[len - 1] == 'X' ||
           input_str[len - 1] == ')')) {
        input_str = (ui_->input->text() + button->text());
        ui_->input->setText(input_str);
      }
    } else if (len == 0 ||
               (input_str[len - 1] != 'X' && input_str[len - 1] != ')')) {
      input_str = (ui_->input->text() + button->text());
      ui_->input->setText(input_str);
    }
  } else {
    ui_->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::onXClicked() {
  QPushButton *button = (QPushButton *)sender();
  QString input_str = ui_->input->text();
  int len = input_str.length();
  if (len < 256) {
    if (len == 0) {
      input_str = (ui_->input->text() + button->text());
      ui_->input->setText(input_str);
    } else {
      if (input_str[len - 1] == '(' || input_str[len - 1] == '+' ||
          input_str[len - 1] == '-' || input_str[len - 1] == '*' ||
          input_str[len - 1] == '/' || input_str[len - 1] == 'd' ||
          input_str[len - 1] == '^') {
        input_str = (ui_->input->text() + button->text());
        ui_->input->setText(input_str);
      }
    }
  } else {
    ui_->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::printUnary() {
  QPushButton *button = (QPushButton *)sender();
  QString input_str = ui_->input->text();
  int len = input_str.length();

  if (len == 0) {
    if (button->text() == "+" || button->text() == "-") {
      input_str = (ui_->input->text() + button->text());
      ui_->input->setText(input_str);
    }
  } else if (len == 1 &&
             (input_str[len - 1] == '+' || input_str[len - 1] == '-')) {
    if (button->text() == "+" || button->text() == "-") {
      input_str.chop(1);
      ui_->input->setText(input_str);
      input_str = (ui_->input->text() + button->text());
      ui_->input->setText(input_str);
    }
  } else if (len > 1 &&
             (input_str[len - 1] == '+' || input_str[len - 1] == '-') &&
             (input_str[len - 2] == '(') &&
             (button->text() == "+" || button->text() == "-")) {
    input_str.chop(1);
    ui_->input->setText(input_str);
    input_str = (ui_->input->text() + button->text());
    ui_->input->setText(input_str);
  } else if (len > 0 && input_str[len - 1] == '(' &&
             (button->text() == "+" || button->text() == "-")) {
    input_str = (ui_->input->text() + button->text());
    ui_->input->setText(input_str);
  }
}

void CalcView::onOperatorClicked() {
  QPushButton *button = (QPushButton *)sender();
  QString input_str = ui_->input->text();
  int len = input_str.length();

  printUnary();
  if (len > 0 && len < 256) {
    if (input_str[len - 1].isDigit() || input_str[len - 1] == ')' ||
        input_str[len - 1] == 'X') {
      input_str = (ui_->input->text() + button->text());
      ui_->input->setText(input_str);
    } else {
      printUnary();
      if (input_str[len - 1] == 'd') {
        input_str.chop(3);
        ui_->input->setText(input_str);
        input_str = (ui_->input->text() + button->text());
        ui_->input->setText(input_str);
      } else if (len > 1 &&
                 (input_str[len - 2].isDigit() || input_str[len - 2] == ')' ||
                  input_str[len - 2] == 'X')) {
        input_str.chop(1);
        ui_->input->setText(input_str);
        input_str = (ui_->input->text() + button->text());
        ui_->input->setText(input_str);
      }
    }
  } else if (len >= 256) {
    ui_->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::onFunctionClicked() {
  QPushButton *button = (QPushButton *)sender();
  QString input_str = ui_->input->text();
  input_str = ui_->input->text();
  int len = input_str.size();
  if (len == 0) {
    ui_->input->setText(input_str + button->text() + "(");
  } else if (len < 256 &&
             (input_str[len - 1] == '(' || input_str[len - 1] == '+' ||
              input_str[len - 1] == '-' || input_str[len - 1] == '*' ||
              input_str[len - 1] == '/' || input_str[len - 1] == '^')) {
    ui_->input->setText(input_str + button->text() + "(");
  }
  if (len >= 256) {
    ui_->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::onDotClicked() {
  QString input_str = ui_->input->text();
  int len = input_str.length();
  int status = 0;

  if (len < 256) {
    if (len != 0 && input_str[len - 1].isDigit()) {
      int index = 1;
      while (input_str[len - index].isDigit() && len != index) {
        if (input_str[len - index - 1] == '.') {
          status = 1;
        }
        index++;
      }
      if (status == 0) {
        input_str = (ui_->input->text() + '.');
        ui_->input->setText(input_str);
      }
    }
  } else {
    ui_->output->setText("Длинное выражение, надо короче");
  }
}

void CalcView::onACClicked() {
  ui_->input->setText("");
  ui_->output->setText("");
}

void CalcView::onCEClicked() {
  QString input_str = ui_->input->text();
  int len = input_str.length();
  if (len > 0) {
    if (input_str[len - 1] == 'd') {
      input_str.chop(3);
    } else if (input_str.isEmpty()) {
      ui_->output->setText("");
    } else if (len > 2 && input_str[len - 1] == '(' &&
               input_str[len - 2] >= 'a' && input_str[len - 2] <= 'z') {
      int count = 0;
      while (len > 0 &&
             ((input_str[len - 1] >= 'a' && input_str[len - 1] <= 'z') ||
              input_str[len - 1] == '(')) {
        len--;
        count++;
      }
      input_str.chop(count);
    } else {
      input_str.chop(1);
    }
    ui_->input->setText(input_str);
  }
}

bool CalcView::validNum(QString input) {
  bool result = true;
  int count_dot = 0;
  if (input.isEmpty()) {
    result = false;
  } else {
    for (int i = 0; i < input.length() && result; i++) {
      if (input[i] == '.') {
        count_dot++;
      }
      if (!((input[i] == '.' || input[i].isDigit()) && count_dot < 2) ||
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

bool CalcView::checkLastElement(QString input) {
  bool result = true;
  QString x = ui_->xValue->text();

  int countOpenBracker = std::count(input.begin(), input.end(), '(');
  int countClosingBracker = std::count(input.begin(), input.end(), ')');
  int len = input.length();

  if (len > 256) {
    result = false;
    ui_->output->setText("Длинное выражение");
  } else if (countOpenBracker != countClosingBracker) {
    result = false;
    ui_->output->setText("Проблема со скобками");
  } else if (input.isEmpty()) {
    result = false;
    ui_->output->setText("Пустая строка");
  } else if ((input[len - 1] != ')' && input[len - 1] != 'X') &&
             !input[len - 1].isDigit()) {
    result = false;
    ui_->output->setText("Неверное выражение");
  }
  return result;
}

void CalcView::onEqualsClicked() {
  QString input = ui_->input->text();
  QString x = ui_->xValue->text();
  if (input.isEmpty()) {
    ui_->output->setText("Пустая строка");
  }
  if ((input.contains('X') != 0) && ui_->xValue->text().isEmpty()) {
    ui_->output->setText("Напиши значение Х");
  } else if (input.contains('X') != 0 && !validNum(ui_->xValue->text())) {
    ui_->xValue->setText("что-то не так");
  } else if (checkLastElement(ui_->input->text())) {
    QString result = controller_.calc(input, x);
    ui_->output->setText(result);
  }
}

bool CalcView::checkGraphInput(QVector<QString> values) {
    bool result = true;

    for (int i=0; i<values.size() && result; i++) {
        if (!validNum(values[i]) || abs(values[i].toDouble())>1000000) {
            result = false;
        }
    }
    return result;
}

void CalcView::onGraphClicked() {
  if (checkLastElement(ui_->input->text())) {
    QMessageBox msgBox;
    QVector<QString> values = {ui_->x_start->text(), ui_->x_end->text(), ui_->y_start->text(), ui_->y_end->text()};
    QVector<double> x, y;
    ui_->widget->clearGraphs();
    ui_->widget->replot();

    if (!checkGraphInput(values)) {
        msgBox.setText("Область определения и значения дб числами до +-1000000");
        msgBox.exec();
    }

    double x_start = values[0].toDouble();
    double x_end = values[1].toDouble();
    double y_start = values[2].toDouble();
    double y_end = values[3].toDouble();

    if (x_start > x_end) {
        std::swap(x_start, x_end);
    } else if (y_start > y_end) {
        std::swap(y_start, y_end);
    }

    ui_->widget->xAxis->setRange(x_start, x_end);
    ui_->widget->yAxis->setRange(y_start, y_end);

    controller_.makeGraph(x, y, x_start, x_end, y_start, y_end, ui_->input->text());

    ui_->widget->addGraph();
    ui_->widget->graph(0)->addData(x, y);
    ui_->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui_->widget->graph(0)->setPen(QColor(84, 84, 84));
    ui_->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui_->widget->replot();
  }
}
