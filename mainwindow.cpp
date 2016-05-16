#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitorview.h"
#include "monitor.h"
#include <memory>
#include "form.h"

using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Monitor* monitor = new Monitor(this);
    MonitorView* monitorView = new MonitorView(this);
    monitorView->initialize(monitor);

    Form* form = new Form();
    ui->gridLayout->addWidget(form, 0,0,1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
