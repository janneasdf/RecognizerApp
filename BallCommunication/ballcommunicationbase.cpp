#include "ballcommunicationbase.h"

BallCommunicationBase::BallCommunicationBase(QObject *parent) : QObject(parent)
{

}

void BallCommunicationBase::addProcessedData(ProcessedBallData data)
{
    QMutexLocker locker(&processedDataMutex);
    processedData.push_back(data);
}

void BallCommunicationBase::clearProcessedData()
{
    QMutexLocker locker(&processedDataMutex);
    processedData.clear();
}

BallCommunicationBase::~BallCommunicationBase()
{

}

vector<ProcessedBallData> BallCommunicationBase::getProcessedData()
{
    QMutexLocker locker(&processedDataMutex);
    vector<ProcessedBallData> copy = processedData;
    return copy;
}
