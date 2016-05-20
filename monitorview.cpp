#include "monitorview.h"
#include <QDebug>
#include <qmessagebox.h>
#include "mainwindow.h"
#include <qapplication.h>

MonitorView::MonitorView(QWidget *parent) : QWidget(parent), ui(new Ui::MonitorView)
{
    ui->setupUi(this);
}

void MonitorView::initialize(BallCommunicationBase* ballCommunication)
{
    this->ballCommunication = ballCommunication;

    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonPressed()));
    connect(ui->toggleConnectionButton, SIGNAL(clicked(bool)), this, SLOT(toggleConnectionButtonPressed()));

    connect(ballCommunication, SIGNAL(connectionOpened(QString)), this, SLOT(onConnectionStarted(QString)));
    connect(ballCommunication, SIGNAL(connectionClosed(QString)), this, SLOT(onConnectionEnded(QString)));
    connect(ballCommunication, SIGNAL(dataReadError(QString)), this, SLOT(onMessage(QString)));
    connect(ballCommunication, SIGNAL(dataReceived(float,float,float)), this, SLOT(onDataReceived(float,float,float)));
}
void MonitorView::onConnectionStarted(const QString& message)
{
    ui->logBrowser->append(message);
    ui->toggleConnectionButton->setText("Close connection");
}

void MonitorView::onConnectionEnded(const QString& message)
{
    ui->logBrowser->append(message);
    ui->toggleConnectionButton->setText("Open connection");
}

void MonitorView::onMessage(const QString &message)
{
    ui->logBrowser->append(message);
}

void MonitorView::onDataReceived(float timestamp, float acceleration, float gyro)
{
    (void)timestamp;
    ui->logBrowser->append(QString("Received data: ") + QString::number(acceleration) + QString::number(gyro));
}

void MonitorView::clearButtonPressed()
{
    ui->logBrowser->clear();
}

void MonitorView::toggleConnectionButtonPressed()
{
    if (ballCommunication->isConnectionActive())
    {
        ballCommunication->closeConnection(true);
    }
    else
    {
        try
        {
            ballCommunication->openConnection();
        }
        catch (std::exception e)
        {
            QMessageBox errorMessageBox;
            errorMessageBox.setText(QString(e.what()));
            errorMessageBox.exec();
        }
    }
}
