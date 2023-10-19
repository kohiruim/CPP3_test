#ifndef CREDITVIEW_H
#define CREDITVIEW_H

#include <QWidget>

namespace Ui {
class CreditView;
}

class CreditView : public QWidget
{
    Q_OBJECT

public:
    explicit CreditView(QWidget *parent = nullptr);
    ~CreditView();

private:
    Ui::CreditView *ui;
};

#endif // CREDITVIEW_H
