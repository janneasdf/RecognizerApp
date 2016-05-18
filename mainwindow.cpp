#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitor.h"
#include "monitorview.h"
#include "training.h"
#include "trainingview.h"
#include <memory>

using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Monitor* monitor = new Monitor(this);
    MonitorView* monitorView = new MonitorView(this);
    monitorView->initialize(monitor);

    Training* training = new Training(this);
    TrainingView* trainingView = new TrainingView(this);
    trainingView->initialize(training);

    ui->monitorLayout->addWidget(monitorView);
    ui->trainingLayout->addWidget(trainingView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
