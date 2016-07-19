#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitorview.h"
#include "training.h"
#include "trainingview.h"
#include "recognitionview.h"
#include "parameterview.h"
#include "BallCommunication/ballcommunicationreal.h"
#include "BallCommunication/ballcommunicationfake.h"
#include "BallCommunication/databallcommunication.h"
#include "GestureRecognition/gesturerecognition.h"
#include <memory>
#include <stdio.h>
#include "recognitionconfig.h"

using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<UINT>("UINT");

#if FAKE_COMMUNICATION
    BallCommunicationBase* ballCommunication = new BallCommunicationFake(this);
#else
    BallCommunicationBase* ballCommunication = new BallCommunicationReal(this);
#endif
    DataBallCommunication* dataBallCommunication = new DataBallCommunication(this);

    GestureRecognition* gestureRecognition = new GestureRecognition();

    Training* training = new Training(this);
    training->initialize(gestureRecognition);
    TrainingView* trainingView = new TrainingView(this);
    trainingView->initialize(training);

    MonitorView* monitorView = new MonitorView(this);
    monitorView->initialize(ballCommunication, dataBallCommunication);

    RecognitionView* recognitionView = new RecognitionView(this);
    recognitionView->initialize(gestureRecognition);
    recognitionView->setDataSource(ballCommunication);

    ParameterView* parameterView = new ParameterView(this);
    parameterView->initialize(gestureRecognition);

    ui->trainingLayout->addWidget(trainingView);
    ui->monitorLayout->addWidget(monitorView);
    ui->recognitionLayout->addWidget(recognitionView);
    ui->parameterLayout->addWidget(parameterView);

    connect(monitorView, SIGNAL(signalSourceChanged(BallCommunicationBase*)), recognitionView, SLOT(onSignalSourceChanged(BallCommunicationBase*)));
    connect(monitorView, SIGNAL(signalSourceChanged(BallCommunicationBase*)), gestureRecognition, SLOT(onDataSourceChanged(BallCommunicationBase*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
