#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <vector>
#include <memory>
#include <QObject>
#include <QFutureWatcher>
#include "GRT_helper.h"
#include <string>

using std::string;
using std::vector;

class Recognizer : public QObject
{
    Q_OBJECT
public:
    explicit Recognizer(QObject *parent = 0);

    // Clears earlier training and trains the model on given data
    void trainFromData(const TimeSeriesClassificationData& trainingData, event_type_converter eventNames);

    void Recognizer::runRecognition(MatrixDouble dataCopy, vector<float> timestamps);

private:
    GestureRecognitionPipeline pipeline;
    std::unique_ptr<HMM> hmm;

    event_type_converter gestureNames;

    /* Recognition parameters */
    size_t windowSize;

signals:
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

    void recognitionResult(const QString& result, UINT gesture, const QString& gestureName, float gestureStartTime, float gestureEndTime);

public slots:

};

#endif // RECOGNIZER_H
