#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <qobject.h>
#include <vector>
#include "GRT_helper.h"

class Recognizer : public QObject
{
    Q_OBJECT
public:
    explicit Recognizer(QObject *parent = 0);

    // Clears earlier training and trains the model on given data
    void trainFromData(const TimeSeriesClassificationData& trainingData);

signals:
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

public slots:

};

#endif // RECOGNIZER_H
