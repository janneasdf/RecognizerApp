#ifndef RECOGNITIONVIEW_H
#define RECOGNITIONVIEW_H

#include <QWidget>
#include <QDateTime>
#include "Libraries/qcustomplot.h"
#include "BallCommunication/ballcommunicationbase.h"
#include "GestureRecognition/gesturerecognition.h"

namespace Ui {
class RecognitionView;
}

class RecognitionView : public QWidget
{
    Q_OBJECT

public:
    explicit RecognitionView(QWidget *parent = 0);
    ~RecognitionView();

    void initialize(GestureRecognition* gestureRecognition);
    void setDataSource(BallCommunicationBase* ballCommunication);

private:
    void resetPlot();

    GestureRecognition* gestureRecognition;
    BallCommunicationBase* ballCommunication;

    QCustomPlot* sensorPlot = 0;
    const int accelGraphIndex = 0;
    const int gyroGraphIndex = 1;
    float previousUpdateTimestamp = 0;

    Ui::RecognitionView *ui;

    qint64 previousPrediction = 0;

public slots:
    void onSignalSourceChanged(BallCommunicationBase* newSource);

private slots:
    void updateGraph(float timestamp, float acceleration, float gyro);
    void clearGraph();
    void updateLagInfo();
    void onRecognitionResult(const QString& result, UINT label, const QString& gestureName, float gestureStartTime, float gestureEndTime);
    void onRecognitionError(const QString& message);
};

#endif // RECOGNITIONVIEW_H
