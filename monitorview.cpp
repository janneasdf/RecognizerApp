#include "monitorview.h"
#include <QDebug>
#include <qmessagebox.h>

MonitorView::MonitorView(QObject *parent) : QObject(parent)
{

}

void MonitorView::initialize(Monitor* const monitor,
                             QTextBrowser* const messageBrowser,
                             QPushButton* const clearButton,
                             QPushButton* const toggleConnectionButton)
{
    this->monitor = monitor;
    this->messageBrowser = messageBrowser;
    this->clearButton = clearButton;

    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clearButtonPressed()));
    connect(monitor, SIGNAL(connectionStarted(QString)), this, SLOT(onConnectionStarted(QString)));
    connect(monitor, SIGNAL(connectionEnded(QString)), this, SLOT(onConnectionEnded(QString)));
    connect(toggleConnectionButton, SIGNAL(clicked(bool)), this, SLOT(toggleConnectionButtonPressed()));
}

void MonitorView::onConnectionStarted(const QString& message)
{
    messageBrowser->append(message);
}

void MonitorView::onConnectionEnded(const QString& message)
{
    messageBrowser->append(message);
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
