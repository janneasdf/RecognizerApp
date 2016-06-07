#include "recognizer.h"

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{
    pipeline.addPreProcessingModule(MovingAverageFilter(5, 1));
}

void Recognizer::trainFromData(const TimeSeriesClassificationData& trainingData)
{
    emit trainingStarted();
    try
    {
        hmm = std::make_unique<HMM>(setup_HMM(10));
        pipeline.setClassifier(*hmm.get());
        pipeline.train(trainingData);
    }
    catch (const std::exception& e)
    {
        emit trainingError(e.what());
        return;
    }
    emit trainingCompleted();
}

void Recognizer::runRecognition(MatrixDouble& dataCopy)
{
    windowSize = 100;

    //if (dataCopy.getSize() < windowSize || !pipeline.getTrained())
    //    return;

    //pipeline.predict(dataCopy);

    emit recognitionResult(QString("Fake recognition result"));
}
