#include "monitor.h"
#include "BallCommunication/declaration.h"
#include "BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"

Monitor::Monitor(QObject *parent) : QObject(parent)
{

}

void Monitor::initialize(BallCommunicationBase *ballCommunication)
{
    this->ballCommunication = ballCommunication;
    connect(ballCommunication, SIGNAL(connectionOpened(QString)),
                     this, SIGNAL(connectionStarted(QString)));
    connect(ballCommunication, SIGNAL(connectionClosed(QString)),
                     this, SIGNAL(connectionEnded(QString)));
    connect(ballCommunication, SIGNAL(dataReceived(float,float,float)), this, SLOT(receiveData(float,float,float)));
    connect(ballCommunication, SIGNAL(dataReadError(QString)), this, SIGNAL(dataError(QString)));
}

void Monitor::tryStartConnection()
{
    if (!ballCommunication)
        return;
    ballCommunication->openConnection();
}

void Monitor::endConnection()
{
    if (!ballCommunication)
        return;
    ballCommunication->closeConnection(true);
}

bool Monitor::isConnectionActive()
{
    if (!ballCommunication)
        return false;
    return ballCommunication->isConnectionActive();
}

void Monitor::receiveData(float timestamp, float acceleration, float gyro)
{
    emit dataReceived(timestamp, acceleration, gyro);
}
