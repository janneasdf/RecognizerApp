#ifndef RECOGNITIONVIEW_H
#define RECOGNITIONVIEW_H

#include <QWidget>
#include "Libraries/qcustomplot.h"
#include "monitor.h"
#include <qdatetime.h>

namespace Ui {
class RecognitionView;
}

class RecognitionView : public QWidget
{
    Q_OBJECT

public:
    explicit RecognitionView(QWidget *parent = 0);
    ~RecognitionView();

    void initialize(Monitor* monitor);

private:
    Monitor* monitor;
    QCustomPlot* sensorPlot;
    const int accelGraphIndex = 0;
    const int gyroGraphIndex = 1;
    float previousUpdateTimestamp = 0;

    Ui::RecognitionView *ui;

private slots:
    void updateGraph(float timestamp, float acceleration, float gyro);
    void clearGraph();
    void updateLagInfo();
};

#endif // RECOGNITIONVIEW_H
