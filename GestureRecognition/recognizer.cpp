#include "recognizer.h"

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{
    pipeline.addPreProcessingModule(MovingAverageFilter(5, 2));
}

void Recognizer::trainFromData(const TimeSeriesClassificationData& trainingData,
                               event_type_converter gestureNames)
{
    emit trainingStarted();
    try
    {
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
    if (dataCopy.getNumRows() != timestamps.size())
    {
        throw std::invalid_argument("Gesture data and timestamp data must be same length. ");
    }

    windowSize = RecognitionConfigFactory::getInstance().getRecognitionWindow();

    if (!pipeline.getTrained())
    {
        emit recognitionError(QString("Gesture recognition model hasn't been trained"));
        return;
    }
    if (dataCopy.getNumRows() < windowSize)
    {
        emit recognitionError(QString("Not enough data for gesture prediction"));
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
    //todo try fake results to test graph vertical line thing
}

void Recognizer::updateParameters(GestureClassifierType classifierType, int downsampleFactor)
{
    static QMutex paramMutex;
    QMutexLocker locker(&paramMutex);

    switch (classifierType)
    {
    case GestureClassifierType::DTW:
        pipeline.setClassifier(setup_DTW());
        break;
    case GestureClassifierType::DHMM:
    case GestureClassifierType::CHMM:
        pipeline.setClassifier(setup_HMM(downsampleFactor, classifierType == GestureClassifierType::CHMM));
    }
    // Note: pipeline needs to be re-trained (by user)

}
