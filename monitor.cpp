#include "monitor.h"
#include "BallCommunication/declaration.h"
#include "BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"

Monitor::Monitor(QObject *parent) : QObject(parent)
{
    ballCommunication = BallCommunication::getInstance();
    QObject::connect(ballCommunication, SIGNAL(ConnectionOpened(QString)),
                     this, SIGNAL(connectionStarted(QString)));
    QObject::connect(ballCommunication, SIGNAL(ConnectionClosed(QString)),
                     this, SIGNAL(connectionEnded(QString)));
}

void Monitor::tryStartConnection()
{
    ballCommunication->OpenConnection();
}

void Monitor::endConnection()
{
    ballCommunication->CloseConnection(true);
}

void Monitor::receiveData(const QString& data)
{

}
