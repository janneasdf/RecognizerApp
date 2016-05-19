#ifndef BALLCOMMUNICATIONFAKE_H
#define BALLCOMMUNICATIONFAKE_H

#include "ballcommunicationbase.h"

class BallCommunicationFake : public BallCommunicationBase
{
    Q_OBJECT
public:
    explicit BallCommunicationFake(QObject* parent = 0);
    ~BallCommunicationFake();

    void openConnection() override;
    void closeConnection(bool clearData) override;

private:
    QTimer updateTimer;
    qint64 startTime;

private slots:
    void receiveData();
};

#endif // BALLCOMMUNICATIONFAKE_H
