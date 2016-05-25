#ifndef DATABALLCOMMUNICATION_H
#define DATABALLCOMMUNICATION_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <vector>
#include "ballcommunicationbase.h"
#include "sensordataframe.h"

using std::vector;

/* This class reads a previously recorded sensor data file and
 * communicates that data as events (faking a real-time case)
 *
 */
class DataBallCommunication : public BallCommunicationBase
{
    Q_OBJECT
public:
    DataBallCommunication(QObject* parent = 0);
    ~DataBallCommunication();

    void initializeFromFile(QString filepath);

    void openConnection() override;
    void closeConnection(bool clearData) override;

private:
    QTimer updateTimer;
    QString currentFile;
    bool initialized = false;
    // Used for not sending same data twice and for seeking to beginning
    uint lastReadDataIndex = 0;

    vector<SensorDataFrame> data;

private slots:
    void receiveData();
};

#endif // DATABALLCOMMUNICATION_H
