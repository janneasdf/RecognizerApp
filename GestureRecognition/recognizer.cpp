#include "recognizer.h"

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{
    pipeline.addPreProcessingModule(MovingAverageFilter(5, 1));
}

void Recognizer::trainFromData(const TimeSeriesClassificationData& trainingData, event_type_converter gestureNames)
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
    this->gestureNames = gestureNames;
    emit trainingCompleted();
}

void Recognizer::runRecognition(MatrixDouble dataCopy)
{
    windowSize = 100;

    if (dataCopy.getSize() < windowSize)
    {
        emit recognitionResult(QString("Not enough data for gesture prediction"));
        return;
    }
    if (!pipeline.getTrained())
    {
        emit recognitionResult(QString("Gesture recognition model hasn't been trained"));
        return;
    }

    pipeline.predict(dataCopy);

    UINT label = pipeline.getPredictedClassLabel();
    QString gesture = QString::fromStdString(gestureNames.int_to_event_type(label));

    emit recognitionResult(gesture);
//    emit recognitionResult(QString("Fake recognition result"));
}
