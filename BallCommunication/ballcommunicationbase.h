#ifndef BALLCOMMUNICATIONBASE_H
#define BALLCOMMUNICATIONBASE_H

#include "Networking/BallCommunicator/BallCommunicator.h"
#include "Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"
#include "Utilities/GyroCalibrator/GyroCalibrator.h"
#include <iostream>
#include <vector>
#include <string>
#include <QDateTime>
#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

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
    vector<ProcessedBallData> getProcessedData();

protected:
    explicit BallCommunicationBase(QObject *parent = 0);
    bool connectionActive = false;
    qint64 connectionStartedTime = 0;
    string name = "Unintialized name";  // Set in deriving classes

    void addProcessedData(ProcessedBallData data);
    void clearProcessedData();

private:
    // For storing all previous data
    vector<ProcessedBallData> processedData;
    QMutex processedDataMutex;

signals:
    void connectionOpened(const QString& message);
    void connectionClosed(const QString& message);
    void dataReceived(float timestamp, float acceleration, float gyro); // todo decide if parameters or not, also where is "all data" kept
    void dataReadError(const QString& message);


};

#endif // BALLCOMMUNICATIONBASE_H
