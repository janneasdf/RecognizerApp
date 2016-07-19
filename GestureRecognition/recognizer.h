#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <vector>
#include <memory>
#include <string>
#include <QObject>
#include <QFutureWatcher>
#include "GRT_helper.h"
#include "recognitionconfig.h"

using std::string;
using std::vector;

/* This class contains the logic for setting up a gesture classifier
 * using it.
 */
class Recognizer : public QObject
{
    Q_OBJECT
public:
    explicit Recognizer(QObject *parent = 0);

    // Clears earlier training and trains the model on given data
    void trainFromData(const TimeSeriesClassificationData& trainingData, event_type_converter eventNames);

    void Recognizer::runRecognition(MatrixDouble dataCopy, vector<float> timestamps);

    void updateParameters(GestureClassifierType classifierType, int downsampleFactor);

private:
    GestureRecognitionPipeline pipeline;
    std::unique_ptr<Classifier> classifier;

    event_type_converter gestureNames;

    /* Recognition parameters */
    size_t windowSize;

signals:
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

    void recognitionResult(const QString& result, UINT gesture, const QString& gestureName, float gestureStartTime, float gestureEndTime);

};

#endif // RECOGNIZER_H
