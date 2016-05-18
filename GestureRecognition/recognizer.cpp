#include "recognizer.h"

Recognizer::Recognizer(QObject *parent) : QObject(parent)
{

}

void Recognizer::trainFromData(const TimeSeriesClassificationData& trainingData)
{
    emit trainingStarted();
    try
    {
    DTW dtw = setup_DTW();
    dtw.train(trainingData);
    }
    catch (const std::exception& e)
    {
        emit trainingError(e.what());
        return;
    }
    emit trainingCompleted();
}
