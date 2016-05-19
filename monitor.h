#ifndef MONITOR_H
#define MONITOR_H

#include "BallCommunication/ballcommunication.h"
#include <QObject>
#include <memory>

class Monitor : public QObject
{
    Q_OBJECT
public:
    explicit Monitor(QObject *parent = 0);

    void initialize(BallCommunicationBase* ballCommunication);

    void tryStartConnection();
    void endConnection();
    bool isConnectionActive();

private:
    BallCommunicationBase* ballCommunication;

signals:
    void connectionStarted(const QString& connectionInfo);
    void connectionEnded(const QString& connectionEndedInfo);
    void dataReceived(float timestamp, float acceleration, float gyro);

private slots:
    void receiveData(float timestamp, float acceleration, float gyro); // todo not qstring but some packet thing
};

#endif // MONITOR_H
