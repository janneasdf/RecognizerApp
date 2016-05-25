#include "monitorview.h"
#include "mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>

MonitorView::MonitorView(QWidget *parent) : QWidget(parent), ui(new Ui::MonitorView)
{
    ui->setupUi(this);
}

void MonitorView::initialize(BallCommunicationBase* ballCommunication, DataBallCommunication* dataBallCommunication)
{
    this->ballCommunication = ballCommunication;
    this->dataBallCommunication = dataBallCommunication;

    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonPressed()));

    // Using sensor for input
    connect(ui->toggleConnectionButton, SIGNAL(clicked(bool)), this, SLOT(toggleConnectionButtonPressed()));
    connect(ballCommunication, SIGNAL(connectionOpened(QString)), this, SLOT(onConnectionStarted(QString)));
    connect(ballCommunication, SIGNAL(connectionClosed(QString)), this, SLOT(onConnectionEnded(QString)));
    connect(ballCommunication, SIGNAL(dataReadError(QString)), this, SLOT(onMessage(QString)));
    connect(ballCommunication, SIGNAL(dataReceived(float,float,float)), this, SLOT(onDataReceived(float,float,float)));

    // Reading file for input
    connect(ui->fileConnectionButton, SIGNAL(clicked(bool)), this, SLOT(dataConnectionButtonPressed()));
    connect(dataBallCommunication, SIGNAL(connectionOpened(QString)), this, SLOT(onDataConnectionStarted(QString)));
    connect(dataBallCommunication, SIGNAL(connectionClosed(QString)), this, SLOT(onDataConnectionEnded(QString)));
    connect(dataBallCommunication, SIGNAL(dataReadError(QString)), this, SLOT(onMessage(QString)));
    connect(dataBallCommunication, SIGNAL(dataReceived(float,float,float)), this, SLOT(onDataReceived(float,float,float)));
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

/********* Connection with sensor ball slots *********/
void MonitorView::onConnectionStarted(const QString& message)
{
    ui->logBrowser->append(message);
    ui->toggleConnectionButton->setText("Close Connection\n(from sensor)");
    emit signalSourceChanged(ballCommunication);
}

void MonitorView::onConnectionEnded(const QString& message)
{
    ui->logBrowser->append(message);
    ui->toggleConnectionButton->setText("Open connection\n(from sensor)");
}


/********** Data connection (reading input from file) slots **********/
void MonitorView::dataConnectionButtonPressed()
{
    if (dataBallCommunication->isConnectionActive())
    {
        dataBallCommunication->closeConnection(true);
    }
    else
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Choose input data"), ".", "*.dat");
        // Check if user canceled
        if (filename.isNull())
            return;

        // Initialize with data from selected file
        try
        {
            dataBallCommunication->initializeFromFile(filename);
            dataBallCommunication->openConnection();
        }
        catch (std::exception e)
        {
            QMessageBox errorMessageBox;
            errorMessageBox.setText(e.what());
            errorMessageBox.exec();
            return;
        }
    }
}

void MonitorView::onDataConnectionStarted(const QString &message)
{
    ui->logBrowser->append(message);
    ui->fileConnectionButton->setText("Close connection\n to file");
    emit signalSourceChanged(dataBallCommunication);
}

void MonitorView::onDataConnectionEnded(const QString &message)
{
    ui->logBrowser->append(message);
    ui->fileConnectionButton->setText("Open Connection\n(from file)");
}
