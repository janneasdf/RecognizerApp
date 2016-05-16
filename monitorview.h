#ifndef MONITORVIEW_H
#define MONITORVIEW_H

#include "monitor.h"

#include <QObject>
#include <qtextbrowser.h>
#include <qpushbutton.h>
#include <memory>

using std::shared_ptr;

class MonitorView : public QObject
{
    Q_OBJECT
public:
    explicit MonitorView(QObject* parent = 0);
    void initialize(Monitor* const monitor,
                    QTextBrowser* const messageBrowser,
                    QPushButton* const clearButton,
                    QPushButton* const toggleConnectionButton);

private:
    Monitor* monitor;
    QTextBrowser* messageBrowser;
    const QPushButton* clearButton;
    QPushButton* toggleConnectionButton;

signals:

public slots:

private slots:
    void clearButtonPressed();
    void toggleConnectionButtonPressed();
    void onConnectionStarted(const QString& message);
    void onConnectionEnded(const QString& message);
};

#endif // MONITORVIEW_H
