#include "monitorview.h"
#include <QDebug>
#include <qmessagebox.h>
#include "mainwindow.h"
#include <qapplication.h>

MonitorView::MonitorView(QWidget *parent) : QWidget(parent), ui(new Ui::MonitorView)
{
    ui->setupUi(this);
}

void MonitorView::initialize(Monitor* monitor)
{
    this->monitor = monitor;
    connect(ui->clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonPressed()));
    connect(monitor, SIGNAL(connectionStarted(QString)), this, SLOT(onConnectionStarted(QString)));
    connect(monitor, SIGNAL(connectionEnded(QString)), this, SLOT(onConnectionEnded(QString)));
    connect(ui->toggleConnectionButton, SIGNAL(clicked(bool)), this, SLOT(toggleConnectionButtonPressed()));
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

void MonitorView::clearButtonPressed()
{
    ui->logBrowser->clear();
}

void MonitorView::toggleConnectionButtonPressed()
{
    if (monitor->isConnectionActive())
    {
        monitor->endConnection();
    }
    else
    {
        try {
            monitor->tryStartConnection();
        }
        catch (std::exception e)
        {
            QMessageBox errorMessageBox;
            errorMessageBox.setText(QString(e.what()));
            errorMessageBox.exec();
        }
    }
}
