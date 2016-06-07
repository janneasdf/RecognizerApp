#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <vector>
#include <memory>
#include <QObject>
#include <QFutureWatcher>
#include "GRT_helper.h"

class Recognizer : public QObject
{
    Q_OBJECT
public:
    explicit Recognizer(QObject *parent = 0);

    // Clears earlier training and trains the model on given data
    void trainFromData(const TimeSeriesClassificationData& trainingData);

    // Try to recognize gesture (parameter is copied in case the original is changed in another thread)
    void Recognizer::runRecognition(MatrixDouble& dataCopy);

private:
    GestureRecognitionPipeline pipeline;
    std::unique_ptr<HMM> hmm;

    /* Recognition parameters */
    int windowSize;

signals:
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

    void recognitionResult(const QString& label);

public slots:

};

#endif // RECOGNIZER_H
