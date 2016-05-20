#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitor.h"
#include "monitorview.h"
#include "training.h"
#include "trainingview.h"
#include "recognitionview.h"
#include "BallCommunication/ballcommunication.h"
#include "BallCommunication/ballcommunicationfake.h"
#include <memory>

using std::shared_ptr;

#define FAKE_COMMUNICATION 0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Training* training = new Training(this);
    TrainingView* trainingView = new TrainingView(this);
    trainingView->initialize(training);

#if FAKE_COMMUNICATION
    BallCommunicationBase* ballCommunication = new BallCommunicationFake(this);
#else
    BallCommunicationBase* ballCommunication = new BallCommunication(this);
#endif
    Monitor* monitor = new Monitor(this);
    monitor->initialize(ballCommunication);

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
