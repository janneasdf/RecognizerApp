#include "monitor.h"
#include "BallCommunication/declaration.h"
#include "BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"

Monitor::Monitor(QObject *parent) : QObject(parent)
{
    ballCommunication = BallCommunication::getInstance();
    connect(ballCommunication, SIGNAL(ConnectionOpened(QString)),
                     this, SIGNAL(connectionStarted(QString)));
    connect(ballCommunication, SIGNAL(ConnectionClosed(QString)),
                     this, SIGNAL(connectionEnded(QString)));
    connect(ballCommunication, SIGNAL(DataReceived(float,float,float)), this, SLOT(receiveData(float,float,float)));
}

void Monitor::tryStartConnection()
{
    ballCommunication->OpenConnection();
}

void Monitor::endConnection()
{
    ballCommunication->CloseConnection(true);
}

void Monitor::receiveData(float timestamp, float acceleration, float gyro)
{
    emit dataReceived(timestamp, acceleration, gyro);
}
