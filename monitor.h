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

    void tryStartConnection();
    void endConnection();
    bool IsConnectionActive() { return ballCommunication->IsConnectionActive(); }

private:
    BallCommunication* ballCommunication;

signals:
    void connectionStarted(const QString& connectionInfo);
    void connectionEnded(const QString& connectionEndedInfo);

private slots:
    void receiveData(const QString& data); // todo not qstring but some packet thing
};

#endif // MONITOR_H
