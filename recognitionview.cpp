#include "recognitionview.h"
#include "ui_recognitionview.h"

RecognitionView::RecognitionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecognitionView)
{
    ui->setupUi(this);
}

void RecognitionView::initialize(Monitor *monitor)
{
    this->monitor = monitor;

    // Create plot that shows sensor values in real time
    sensorPlot = new QCustomPlot();
    ui->verticalLayout->addWidget(sensorPlot);
    sensorPlot->addGraph(); // Accelerometer graph (acceleration)
    sensorPlot->graph(accelGraphIndex)->setPen(QPen(Qt::blue));
    sensorPlot->graph(accelGraphIndex)->setBrush(QBrush(QColor(240, 255, 200)));
    sensorPlot->graph(accelGraphIndex)->setAntialiasedFill(false);
    sensorPlot->addGraph(); // Gyroscope graph (angular velocity)
    sensorPlot->graph(gyroGraphIndex)->setPen(QPen(Qt::red));
    sensorPlot->graph(gyroGraphIndex)->setBrush(QBrush(QColor(240, 255, 200)));
    sensorPlot->graph(gyroGraphIndex)->setAntialiasedFill(false);

    // Setup axes
    sensorPlot->xAxis->setTickLabelType(QCPAxis::ltNumber);
    sensorPlot->xAxis->setAutoTickStep(false);
    sensorPlot->xAxis->setTickStep(2);
    sensorPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(sensorPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), sensorPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(sensorPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), sensorPlot->yAxis2, SLOT(setRange(QCPRange)));

    // Update plot when there's new data (todo: maybe not one per signal emission?)
    connect(monitor, SIGNAL(dataReceived(float,float,float)), this, SLOT(updateGraph(float,float,float)));
}

void RecognitionView::updateGraph(float timestamp, float acceleration, float gyro)
{
    // calculate two new data points:
    double key = timestamp;
    static double lastPointKey = 0;
    if (key-lastPointKey > 10) // at most add point every 10 ms
    {
      double value0 = acceleration;
      double value1 = gyro;
      // add data to lines:
      sensorPlot->graph(0)->addData(key, value0);
      sensorPlot->graph(1)->addData(key, value1);
      // remove data of lines that's outside visible range:
      sensorPlot->graph(0)->removeDataBefore(key-8);
      sensorPlot->graph(1)->removeDataBefore(key-8);
      // rescale value (vertical) axis to fit the current data:
      sensorPlot->graph(0)->rescaleValueAxis();
      sensorPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    sensorPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    sensorPlot->replot();
}

RecognitionView::~RecognitionView()
{
    delete ui;
}
