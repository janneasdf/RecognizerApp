#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitorview.h"
#include "training.h"
#include "trainingview.h"
#include "recognitionview.h"
#include "BallCommunication/ballcommunication.h"
#include "BallCommunication/ballcommunicationfake.h"
#include "BallCommunication/databallcommunication.h"
#include <memory>
#include <stdio.h>

using std::shared_ptr;

// Define this as 1 if you don't have the ball ready
#define FAKE_COMMUNICATION 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    fclose(stdout);
//    std::cout.setstate(std::ios_base::failbit); // turn off cout

    Training* training = new Training(this);
    TrainingView* trainingView = new TrainingView(this);
    trainingView->initialize(training);

#if FAKE_COMMUNICATION
    BallCommunicationBase* ballCommunication = new BallCommunicationFake(this);
#else
    BallCommunicationBase* ballCommunication = new BallCommunication(this);
#endif
    DataBallCommunication* dataBallCommunication = new DataBallCommunication(this);

    MonitorView* monitorView = new MonitorView(this);
    monitorView->initialize(ballCommunication, dataBallCommunication);

    RecognitionView* recognitionView = new RecognitionView(this);
    recognitionView->initialize();
    recognitionView->setDataSource(ballCommunication);

    ui->trainingLayout->addWidget(trainingView);
    ui->monitorLayout->addWidget(monitorView);
    ui->recognitionLayout->addWidget(recognitionView);

    connect(monitorView, SIGNAL(signalSourceChanged(BallCommunicationBase*)), recognitionView, SLOT(onSignalSourceChanged(BallCommunicationBase*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
