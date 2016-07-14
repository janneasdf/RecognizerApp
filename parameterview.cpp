#include "parameterview.h"
#include "ui_parameterview.h"

ParameterView::ParameterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterView)
{
    ui->setupUi(this);
}

ParameterView::~ParameterView()
{
    delete ui;
}
