#ifndef MONITORVIEW_H
#define MONITORVIEW_H

#include "monitor.h"
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
    void initialize(Monitor* monitor);

private:
    Monitor* monitor;
    Ui::MonitorView* ui;
signals:

public slots:

private slots:
    void clearButtonPressed();
    void toggleConnectionButtonPressed();
    void onConnectionStarted(const QString& message);
    void onConnectionEnded(const QString& message);
    void onMessage(const QString& message);
    void onDataReceived(float timestamp, float acceleration, float gyro);
};

#endif // MONITORVIEW_H
