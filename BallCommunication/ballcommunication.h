#ifndef BALLCOMMUNICATION_H
#define BALLCOMMUNICATION_H

#include "Networking/BallCommunicator/BallCommunicator.h"
#include "Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h"
#include "Utilities/GyroCalibrator/GyroCalibrator.h"
#include <iostream>
#include <QTimer>
#include <QObject>
#include <QDateTime>
#include <QFutureWatcher>
#include <vector>
#include <string>
#include "ballcommunicationbase.h"

using std::vector;
using std::string;

class BallCommunicationReal : public BallCommunicationBase
{
    Q_OBJECT
public:
    explicit BallCommunicationReal(QObject* parent = 0);
    ~BallCommunicationReal();

    void openConnection() override;
    void closeConnection(bool clearData) override;

private:
    const int dataReadInterval = 1000.0 / 10.0; // milliseconds

    void getNewData();

    QFutureWatcher<void>* dataReadingWatcher;

    // Communicator for communicating with ball and receiving data
    BallCommunicator ballCommunicator;

    // For storing all previous data
    vector<RawBallData> rawData;
    vector<ProcessedBallData> processedData;

    // Timer for deciding when to read received data
    QTimer dataReadTimer;

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
    void tryReadData();
};

#endif // BALLCOMMUNICATION_H
