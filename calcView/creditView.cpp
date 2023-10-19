#include "creditView.h"
#include "ui_creditView.h"

CreditView::CreditView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreditView)
{
    ui->setupUi(this);
}

CreditView::~CreditView()
{
    delete ui;
}
