#ifndef BALLCOMMUNICATIONBASE_H
#define BALLCOMMUNICATIONBASE_H

#include "Networking/BallCommunicator/BallCommunicator.h"
#include "Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"
#include "Utilities/GyroCalibrator/GyroCalibrator.h"
#include <iostream>
#include <qtimer.h>
#include <vector>
#include <string>
#include <qobject.h>
#include <qdatetime.h>

using std::vector;
using std::string;

class BallCommunicationBase : public QObject
{
    Q_OBJECT
public:
    ~BallCommunicationBase();
    virtual void openConnection() = 0;
    virtual void closeConnection(bool clearData) = 0;
    bool isConnectionActive() { return connectionActive; }
    qint64 getConnectionStartedTime() { return connectionStartedTime; }
    string getName() { return name; }

protected:
    explicit BallCommunicationBase(QObject *parent = 0);
    bool connectionActive = false;
    qint64 connectionStartedTime = 0;
    string name = "Unintialized name";  // Set in deriving classes

signals:
    void connectionOpened(const QString& message);
    void connectionClosed(const QString& message);
    void dataReceived(float timestamp, float acceleration, float gyro); // todo decide if parameters or not, also where is "all data" kept
    void dataReadError(const QString& message);


};

#endif // BALLCOMMUNICATIONBASE_H
