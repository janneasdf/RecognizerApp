#include "recognizer.h"
#include "recognitionconfig.h"

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{
    pipeline.addPreProcessingModule(MovingAverageFilter(5, 2));
}

void Recognizer::trainFromData(const TimeSeriesClassificationData& trainingData, event_type_converter gestureNames)
{
    emit trainingStarted();
    try
    {
        hmm = std::make_unique<HMM>(setup_HMM(5));
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

void Recognizer::runRecognition(MatrixDouble dataCopy, vector<float> timestamps)
{
    windowSize = RecognitionConfigFactory::getInstance().getRecognitionWindow();

    if (!pipeline.getTrained())
    {
        emit recognitionResult(QString("Gesture recognition model hasn't been trained"), 0, "", 0, 0);
        return;
    }
    if (dataCopy.getNumRows() < windowSize)
    {
        emit recognitionResult(QString("Not enough data for gesture prediction"), 0, "", 0, 0);
        return;
    }

    /* Take windowSize amount of latest samples */
    MatrixDouble dataInWindow;
    size_t rows = dataCopy.getNumRows();
    for (int i = 0; i < windowSize; ++i)
    {
        dataInWindow.push_back(dataCopy.getRowVector(rows - windowSize + i)); // col or row?
    }
    float firstGestureTime = timestamps[timestamps.size() - 1 - windowSize];
    float lastGestureTime = timestamps[timestamps.size() - 1];

    pipeline.predict(dataInWindow);

    UINT label = pipeline.getPredictedClassLabel();

    if (label)
        int x = 1;

    QString gesture = QString::fromStdString(gestureNames.int_to_event_type(label));

    emit recognitionResult(gesture, label, gesture, firstGestureTime, lastGestureTime);
}
