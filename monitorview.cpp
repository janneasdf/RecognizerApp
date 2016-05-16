#include "monitorview.h"
#include <QDebug>
#include <qmessagebox.h>
#include "mainwindow.h"
#include <qapplication.h>

MonitorView::MonitorView(QObject *parent) : QObject(parent)
{

}

void MonitorView::initialize(Monitor* monitor)
{
//    MainWindow& mw = (MainWindow)parent;
//    this->monitor = qApp::activeWindow();
//    this->messageBrowser = messageBrowser;
//    this->clearButton = clearButton;

//    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonPressed()));
//    connect(monitor, SIGNAL(connectionStarted(QString)), this, SLOT(onConnectionStarted(QString)));
//    connect(monitor, SIGNAL(connectionEnded(QString)), this, SLOT(onConnectionEnded(QString)));
//    connect(toggleConnectionButton, SIGNAL(clicked(bool)), this, SLOT(toggleConnectionButtonPressed()));
}
#include <qthread.h>
#include <qapplication.h>
void MonitorView::onConnectionStarted(const QString& message)
{
    qDebug() << QThread::currentThread();
    qDebug() << QApplication::instance()->thread();
    messageBrowser->append(message);
    toggleConnectionButton->setText("Close connection");
}

void MonitorView::onConnectionEnded(const QString& message)
{
    messageBrowser->append(message);
    toggleConnectionButton->setText("Open connection");
}

void MonitorView::clearButtonPressed()
{
    messageBrowser->clear();
}

void MonitorView::toggleConnectionButtonPressed()
{
    if (monitor->IsConnectionActive())
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
