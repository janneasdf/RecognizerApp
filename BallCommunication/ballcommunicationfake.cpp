#include "ballcommunicationfake.h"
#include <qdatetime.h>

BallCommunicationFake::BallCommunicationFake(QObject* parent) : BallCommunicationBase(parent)
{

}

BallCommunicationFake::~BallCommunicationFake()
{
    closeConnection(true);
}

void BallCommunicationFake::openConnection()
{
    if (connectionActive)
    {
        return;
    }
    emit connectionOpened(QString("Opened fake connection"));
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(receiveData()));
    updateTimer.start(60);
    connectionStartedTime = QDateTime::currentMSecsSinceEpoch();
    connectionActive = true;
}

void BallCommunicationFake::closeConnection(bool clearData)
{
    if (!connectionActive)
    {
        return;
    }
    (void*)clearData;
    emit connectionClosed(QString("Closed fake connection"));
    disconnect(&updateTimer, SIGNAL(timeout()), this, SLOT(receiveData()));
    updateTimer.stop();
    connectionActive = false;
}

void BallCommunicationFake::receiveData()
{
    qint64 msecsFromStart = QDateTime::currentMSecsSinceEpoch() - connectionStartedTime;
    emit dataReceived(msecsFromStart, 10 * sin(msecsFromStart * 0.001), 10 * cos(msecsFromStart * 0.001));
}
