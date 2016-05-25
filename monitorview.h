#ifndef MONITORVIEW_H
#define MONITORVIEW_H

#include "BallCommunication/ballcommunicationbase.h"
#include "BallCommunication/databallcommunication.h"
#include "ui_monitorview.h"
#include <QObject>
#include <qtextbrowser.h>
#include <qpushbutton.h>
#include <memory>

using std::shared_ptr;

class MonitorView : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorView(QWidget* parent = 0);
    void initialize(BallCommunicationBase* ballCommunication, DataBallCommunication* dataBallCommunication);

private:
    BallCommunicationBase* ballCommunication;
    DataBallCommunication* dataBallCommunication;
    Ui::MonitorView* ui;

signals:
    void signalSourceChanged(BallCommunicationBase* newSource);

public slots:

private slots:
    void clearButtonPressed();
    void toggleConnectionButtonPressed();
    void onConnectionStarted(const QString& message);
    void onConnectionEnded(const QString& message);
    void onMessage(const QString& message);
    void onDataReceived(float timestamp, float acceleration, float gyro);

    // When reading data from file
    void dataConnectionButtonPressed();
    void onDataConnectionStarted(const QString& message);
    void onDataConnectionEnded(const QString& message);
};

#endif // MONITORVIEW_H
