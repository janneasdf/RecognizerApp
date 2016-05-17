#ifndef BALLCOMMUNICATION_H
#define BALLCOMMUNICATION_H

#include "Networking/BallCommunicator/BallCommunicator.h"
#include "Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"
#include "Utilities/GyroCalibrator/GyroCalibrator.h"
#include <iostream>
#include <qtimer.h>
#include <vector>
#include <string>
#include <qobject.h>

using std::vector;
using std::string;

class BallCommunication : public QObject
{
    Q_OBJECT

public:
    static BallCommunication* getInstance();

    void OpenConnection();
    void CloseConnection(bool clearData);
    bool IsConnectionActive() { return connectionActive; }

    // Delete possibility of accidental copies
    BallCommunication(const BallCommunication&) = delete;
    void operator=(const BallCommunication&) = delete;

private:
    explicit BallCommunication(QObject* parent = 0);
    ~BallCommunication();

    bool connectionActive = false;

    //
    void processRawBallData();

    // Communicator for communicating with ball and receiving data
    BallCommunicator ballCommunicator;

    // For storing all previous data
    vector<RawBallData> rawData;
    vector<ProcessedBallData> processedData;

    // Timer for deciding when to read received data
    QTimer dataReadTimer;

    // Ball communication related timer
    const Timer* communicationTimer;

    // Time when connection was started
    Uint32 connectionStartedTime;

    int flagNetworkFromUDP = 0;
    static const int MAX_BALLS = 1;
    SensorOffsetData sensorOffsetData[MAX_BALLS];
    AccelerometerCalibrator accelerometerCalibrator[MAX_BALLS];
    GyroCalibrator gyroCalibrator[MAX_BALLS];

    // Config and calibration file paths
    const string configFilepath = "./data/conf/communicator.conf";
    const string accelOffsetFilepathFormat = "./data/conf/accelerationOffset%d.dat";
    const string gyroOffsetFilepathFormat = "./data/conf/gyroOffset%d.dat";

signals:
    void DataReceived();
    void ConnectionOpened(const QString& message);
    void ConnectionClosed(const QString& message);

private slots:
    void receiveData();
};

#endif // BALLCOMMUNICATION_H
