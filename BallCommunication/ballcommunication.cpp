#include "ballcommunication.h"
#include "declaration.h"
#include <stdexcept>
#include "Libraries/SDL/include/SDL.h"
#include "Libraries/SDL/include/SDL_net.h"
#include "Networking/Network/Network.h"
#include "Networking/BallCommunicator/BallCommunicator_UDP.h"

// TODO: separate config reading and raw data processing to another class

//BallCommunication::BallCommunication(QObject* parent) : QObject(parent)
//{
//    communicationTimer = Timer::getInstance();
//}


void BallCommunication::receiveData()
{
    // Get newly received data, apply calibration, store it
    processRawBallData();
}

/* ボールデータの処理 */
void BallCommunication::processRawBallData(){
    /* グラフ用にセンサデータを記録する */
    RawBallData receivedRawBallData = ballCommunicator.getRawBallData();
    ProcessedBallData processedBallData = ballCommunicator.getProcessedBallData();
    int currentBallID = 0;

    /* センサグラフデータ追加 */
    float tmpX, tmpY, tmpZ;
    tmpX = receivedRawBallData.acceleration.x - sensorOffsetData[currentBallID].accelerationOffset.x;
    tmpY = receivedRawBallData.acceleration.y - sensorOffsetData[currentBallID].accelerationOffset.y;
    tmpZ = receivedRawBallData.acceleration.z - sensorOffsetData[currentBallID].accelerationOffset.z;
    processedBallData.accelerationXYZ = sqrtf(tmpX * tmpX + tmpY * tmpY + tmpZ * tmpZ);

    tmpX = receivedRawBallData.gyro.x - sensorOffsetData[currentBallID].gyroOffset.x;
    tmpY = receivedRawBallData.gyro.y - sensorOffsetData[currentBallID].gyroOffset.y;
    tmpZ = receivedRawBallData.gyro.z - sensorOffsetData[currentBallID].gyroOffset.z;
    processedBallData.gyroXYZ = sqrtf(tmpX * tmpX + tmpY * tmpY + tmpZ * tmpZ);

    /* 加速度 */
//    graphAccelerationXYZ.addData(processedBallData.accelerationXYZ, currentSensorValueIndex);
//    graphAccelerationX.addData(receivedRawBallData.acceleration.x, currentSensorValueIndex);
//    graphAccelerationY.addData(receivedRawBallData.acceleration.y, currentSensorValueIndex);
//    graphAccelerationZ.addData(receivedRawBallData.acceleration.z, currentSensorValueIndex);

    /* 加速度 */
//    compassXYZ.addData(processedBallData.compassXYZ, currentSensorValueIndex);
//    compassX.addData(receivedRawBallData.compass.x, currentSensorValueIndex);
//    compassY.addData(receivedRawBallData.compass.y, currentSensorValueIndex);
//    compassZ.addData(receivedRawBallData.compass.z, currentSensorValueIndex);

    /* ジャイロ */
//    graphGyroX.addData(receivedRawBallData.gyro.x, currentSensorValueIndex);
//    graphGyroY.addData(receivedRawBallData.gyro.y, currentSensorValueIndex);
//    graphGyroZ.addData(receivedRawBallData.gyro.z, currentSensorValueIndex);

    /* アナログセンサ */
    //graphMic.addData(receivedRawBallData.micValue, currentSensorValueIndex);
    //graphPressure.addData(receivedRawBallData.pressure - GRAPH_OFFSET_PRESSURE_SENSOR, currentSensorValueIndex);
    //graphPhotoSensor1.addData(receivedRawBallData.photoSensor1, currentSensorValueIndex);

    // Store received data
    RawBallData newRawData = receivedRawBallData;
    newRawData.t = communicationTimer->systemTime - connectionStartedTime;
    rawData.push_back(newRawData);
    ProcessedBallData newProcessedBallData = processedBallData;
    newProcessedBallData.t = communicationTimer->systemTime - connectionStartedTime;
    processedData.push_back(newProcessedBallData);

    /* グラフの現在位置をずらす */
//    currentSensorValueIndex++;
//    if (currentSensorValueIndex >= WINDOW_WIDTH){
//        currentSensorValueIndex = 0;
//    }

    // Send signal about receiving data
    emit DataReceived();
}
#include <QDir>
#include <QDebug>
void BallCommunication::OpenConnection()
{
    qDebug() << QDir::currentPath();
    /* Initialize SDL_net */
    if ( SDLNet_Init() < 0 ){
        printf("SDL_netの初期化に失敗しました: %s\n", SDLNet_GetError());
        SDL_Quit();
        throw std::exception("Failed to initialize SDL_net");
    }

    /* 通信方法初期化 */
    char lineBuffer[128];
    char portName[32];
    int udpPortNo;
    int baudRate;
    int writeTimeOut = 0, readTimeOut = 0;
    fstream communicatorConfig(configFilepath, ios::in);
    if ( communicatorConfig.fail() ){
        printf("通信設定ファイルが読み込めませんでした: %s", configFilepath.c_str());
        throw std::exception("Failed to load communicatorConfig.conf");
    }
    communicatorConfig.getline(lineBuffer, 128);
    _snscanf(lineBuffer, 128, "%d", &flagNetworkFromUDP);
    communicatorConfig.getline(lineBuffer, 128);
    _snscanf(lineBuffer, 128, "%d", &udpPortNo);
    communicatorConfig.getline(lineBuffer, 128);
    _snscanf(lineBuffer, 128, "%s %d %d %d", portName, &baudRate, &writeTimeOut, &readTimeOut);
    communicatorConfig.close();

    /* UDPを使う場合 */
    if ( flagNetworkFromUDP ){
        Network::initialize();
        ballCommunicator = (BallCommunicator)BallCommunicatorUDP();
        BallCommunicatorUDP* ballCommunicatorUDP = (BallCommunicatorUDP*)&ballCommunicator;
        if ( ballCommunicatorUDP->initialize(udpPortNo) ){
            printf("UDP通信クラスが初期化できませんでした: %d\n", udpPortNo);
            throw std::exception("Failed to initialize ball communicator (UDP)");
        }else{
            printf("UDP通信を初期化しました: Port: %d\n", udpPortNo);
        }
    /* RS232Cを使う場合 */
    }else{

        /* シリアル通信初期化 */
        communicatorConfig.close();
        ballCommunicator = BallCommunicator();
        if ( ballCommunicator.initialize(portName, baudRate, readTimeOut, writeTimeOut) < 0 ){
            printf("シリアル通信の初期化に失敗しました: Port: %s", portName);
            throw std::exception("Failed to initialize ball communicator (RS232C)");
        }else{
            printf("シリアル通信を初期化しました: %s@%dbps\n", portName, baudRate);
        }
    }

    /* 加速度センサキャリブレーションデータを読み込む */
    for (int i = 0; i < MAX_BALLS; i++){
        char filename[128];
        _snprintf(filename, 128, accelOffsetFilepathFormat.c_str(), i);
        if ( accelerometerCalibrator[i].createCalibrationDataFromFile(filename, &sensorOffsetData[i]) < 0 ){
            printf("加速度センサ(%d)のオフセットデータの初期化に失敗しました。\n", i);
            throw std::exception("Failed to calibrate accelerometer from config file");
        }
        /* ジャイロセンサキャリブレーションデータを読み込む */
        _snprintf(filename, 128, gyroOffsetFilepathFormat.c_str(), i);
        if ( gyroCalibrator[i].createCalibrationDataFromFile(filename, &sensorOffsetData[i]) < 0 ){
            printf("ジャイロ(%d)のオフセットデータの初期化に失敗しました。\n", i);
            throw std::exception("Failed to calibrate gyroscope from config file");
        }
    }

    QObject::connect(&dataReadTimer, SIGNAL(timeout()), this, SLOT(receiveData()));
    dataReadTimer.start(30);

    connectionActive = true;

    // Emit signal about opened connection
    emit ConnectionOpened(QString("Opened connection"));
}

void BallCommunication::CloseConnection(bool clearData)
{
//    for (int i = 0; i < MAX_ELECTRODES; i++) {
//        touchedSE[i].releaseSE();
//    }

    if (!flagNetworkFromUDP){
        ballCommunicator.finalize();
    }else{
        Network::finalize();
    }
//    delete ballCommunicator;

    /* SDLの解放処理 */
    SDLNet_Quit();
    SDL_Quit();

    QObject::disconnect(&dataReadTimer, SIGNAL(timeout()), this, SLOT(receiveData()));
    dataReadTimer.stop();

    if (clearData)
    {
        rawData.clear();
        processedData.clear();
    }

    connectionActive = false;

    // Emit signal about connection closing
    emit ConnectionClosed(QString("Closed connection"));
}

BallCommunication::BallCommunication(QObject *parent) : QObject(parent)
{
    communicationTimer = Timer::getInstance();
}

BallCommunication::~BallCommunication()
{
    CloseConnection(true);
}
