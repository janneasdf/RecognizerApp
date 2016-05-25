#include "databallcommunication.h"
#include "sensordataframe.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>

DataBallCommunication::DataBallCommunication(QObject* parent) : BallCommunicationBase(parent)
{

}

DataBallCommunication::~DataBallCommunication()
{

}

void DataBallCommunication::initializeFromFile(QString filepath)
{
    // Read in all data from the file
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::exception((QString("Couldn't read file: ") + filepath).toStdString().c_str());

    data.clear();
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList values = line.split(",");
        if (values.size() != 4)
            throw std::exception((QString("Wrong amount of values in a line in the file: ") + filepath).toStdString().c_str());
        float timestamp, acceleration, gyro;
        try
        {
            timestamp = values[0].toFloat();
            acceleration = values[1].toFloat();
            gyro = values[3].toFloat();
        }
        catch (std::exception)
        {
            throw std::exception((QString("Could not read parse value into float from line: ") + line).toStdString().c_str());
        }
        data.push_back(SensorDataFrame{timestamp, acceleration, gyro});
    }

    initialized = true;
}

void DataBallCommunication::openConnection()
{
    if (connectionActive) return;
    if (!initialized) throw std::exception("Cannot open data connection; \
connection not initialized from a file.");

    emit connectionOpened(QString("Opened data reading connection from file: ") + currentFile);
    connect(&updateTimer, SIGNAL(timeout()), this, SLOT(receiveData()));
    updateTimer.start(60);
    connectionStartedTime = QDateTime::currentMSecsSinceEpoch();
    connectionActive = true;
}

void DataBallCommunication::closeConnection(bool clearData)
{
    if (!connectionActive) return;
    if (!initialized) throw std::exception("Cannot close data connection; \
connection not initialized from a file.");

    (void)clearData;
    emit connectionClosed(QString("Closed data reading connection from file: ") + currentFile);
    disconnect(&updateTimer, SIGNAL(timeout()), this, SLOT(receiveData()));
    updateTimer.stop();
    connectionActive = false;
}

void DataBallCommunication::receiveData()
{
    // Try to find next data to send (no signal sent if there's no new data)
    qint64 msecsFromStart = QDateTime::currentMSecsSinceEpoch() - connectionStartedTime;
    for (; lastReadDataIndex < data.size(); ++lastReadDataIndex)
    {
        SensorDataFrame& frame = data[lastReadDataIndex];
        if (frame.timestamp >= msecsFromStart)
        {
            emit dataReceived(frame.timestamp, frame.acceleration, frame.gyro);
            lastReadDataIndex++;    // so that we don't emit this same data frame again later
            break;
        }
    }
}
