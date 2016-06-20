#include "recognitionview.h"
#include "ui_recognitionview.h"

RecognitionView::RecognitionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecognitionView)
{
    ui->setupUi(this);
}

void RecognitionView::initialize(GestureRecognition* gestureRecognition)
{
    resetPlot();

    this->gestureRecognition = gestureRecognition;

    // Setup lag info updating (showing latency for receiving data)
    QTimer* lagInfoUpdateTimer = new QTimer();
    connect(lagInfoUpdateTimer, SIGNAL(timeout()), this, SLOT(updateLagInfo()));
    lagInfoUpdateTimer->start(1000);

    // Update gesture recognition result (predicted gesture)
    connect(gestureRecognition, SIGNAL(gestureRecognitionResult(QString)), this, SLOT(onRecognitionResult(QString)));

    previousPrediction = QDateTime::currentMSecsSinceEpoch();
}

void RecognitionView::setDataSource(BallCommunicationBase* ballCommunication)
{
    if (this->ballCommunication)
    {
        // Disconnect from earlier source
        disconnect(ballCommunication, SIGNAL(dataReceived(float,float,float)), this, SLOT(updateGraph(float,float,float)));
        // Clear graph when re-opening connection
        disconnect(ballCommunication, SIGNAL(connectionOpened(QString)), this, SLOT(clearGraph()));
    }

    this->ballCommunication = ballCommunication;

    // Update plot when there's new data (todo: maybe not one per signal emission?)
    connect(ballCommunication, SIGNAL(dataReceived(float,float,float)), this, SLOT(updateGraph(float,float,float)));
    // Clear graph when re-opening connection
    connect(ballCommunication, SIGNAL(connectionOpened(QString)), this, SLOT(clearGraph()));
    clearGraph();
}

void RecognitionView::resetPlot()
{
    if (sensorPlot)
    {
        // Clear old plot
        disconnect(sensorPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), sensorPlot->xAxis2, SLOT(setRange(QCPRange)));
        disconnect(sensorPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), sensorPlot->yAxis2, SLOT(setRange(QCPRange)));
        delete sensorPlot;
    }

    // Create plot that shows sensor values in real time
    sensorPlot = new QCustomPlot();
    ui->verticalLayout->addWidget(sensorPlot);
    sensorPlot->addGraph(); // Accelerometer graph (acceleration)
    sensorPlot->graph(accelGraphIndex)->setPen(QPen(Qt::blue));
//    sensorPlot->graph(accelGraphIndex)->setBrush(QBrush(QColor(240, 255, 200)));
    sensorPlot->graph(accelGraphIndex)->setAntialiasedFill(false);
    sensorPlot->addGraph(); // Gyroscope graph (angular velocity)
    sensorPlot->graph(gyroGraphIndex)->setPen(QPen(Qt::red));
//    sensorPlot->graph(gyroGraphIndex)->setBrush(QBrush(QColor(240, 255, 200)));
    sensorPlot->graph(gyroGraphIndex)->setAntialiasedFill(false);

    // Setup axes
    sensorPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
    sensorPlot->xAxis->setAutoTickStep(false);
    sensorPlot->xAxis->setTickStep(2);
    sensorPlot->axisRect()->setupFullAxesBox();

    // Make left and bottom axes transfer their ranges to right and top axes:
    connect(sensorPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), sensorPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(sensorPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), sensorPlot->yAxis2, SLOT(setRange(QCPRange)));
}

void RecognitionView::onSignalSourceChanged(BallCommunicationBase *newSource)
{
    setDataSource(newSource);
}

void RecognitionView::updateGraph(float timestamp, float acceleration, float gyro)
{
    // calculate two new data points:
    double time = 0.001 * timestamp;
    if (time - previousUpdateTimestamp * 0.001 > 0.1)
    {
      double value0 = acceleration;
      double value1 = gyro;
      // add data to lines:
      sensorPlot->graph(0)->addData(time, value0);
      sensorPlot->graph(1)->addData(time, value1);
      // remove data of lines that's outside visible range:
//      sensorPlot->graph(0)->removeDataBefore(time-8);
//      sensorPlot->graph(1)->removeDataBefore(time-8);
      // rescale value (vertical) axis to fit the current data:
      sensorPlot->graph(0)->rescaleValueAxis();
      sensorPlot->graph(1)->rescaleValueAxis(true);
      previousUpdateTimestamp = timestamp;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    sensorPlot->xAxis->setRange(time+0.25, 8, Qt::AlignRight);
    sensorPlot->replot();
}

void RecognitionView::clearGraph()
{
    resetPlot();
    previousUpdateTimestamp = 0;
}

void RecognitionView::updateLagInfo()
{
    qint64 lag = (QDateTime::currentMSecsSinceEpoch() - ballCommunication->getConnectionStartedTime()) - previousUpdateTimestamp;
    QString lagText = QString("Signal lag: ") + QString::number(lag) + QString(" milliseconds. ");
    ui->currentLagLabel->setText(lagText);
}

void RecognitionView::onRecognitionResult(const QString &label)
{
    qint64 timeSinceLastPrediction = previousPrediction - QDateTime::currentMSecsSinceEpoch();
    ui->predictionLabel->setText(QString("Predicted Gesture: ") + label);
    ui->predictionLagLabel->setText(QString("Prediction lag: ") + QString::number(timeSinceLastPrediction) + "ms");
    previousPrediction = QDateTime::currentMSecsSinceEpoch();
}

RecognitionView::~RecognitionView()
{
    delete ui;
}
