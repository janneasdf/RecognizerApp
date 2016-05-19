#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitor.h"
#include "monitorview.h"
#include "training.h"
#include "trainingview.h"
#include "recognitionview.h"
#include <memory>

using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Training* training = new Training(this);
    TrainingView* trainingView = new TrainingView(this);
    trainingView->initialize(training);

    Monitor* monitor = new Monitor(this);
    MonitorView* monitorView = new MonitorView(this);
    monitorView->initialize(monitor);

    RecognitionView* recognitionView = new RecognitionView(this);
    recognitionView->initialize(monitor);

    ui->trainingLayout->addWidget(trainingView);
    ui->monitorLayout->addWidget(monitorView);
    ui->recognitionLayout->addWidget(recognitionView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
