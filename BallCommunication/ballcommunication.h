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
#include "ballcommunicationbase.h"

using std::vector;
using std::string;

class BallCommunication : public BallCommunicationBase
{
    Q_OBJECT
public:
    explicit BallCommunication(QObject* parent = 0);
    ~BallCommunication();

    void openConnection() override;
    void closeConnection(bool clearData) override;

private:
    const int dataReadInterval = 60; // milliseconds

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

private slots:
    void readData();
};

#endif // BALLCOMMUNICATION_H
