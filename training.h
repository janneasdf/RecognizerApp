#ifndef TRAINING_H
#define TRAINING_H

#include <QObject>
#include <qfuturewatcher.h>
#include "GestureRecognition/gesturerecognition.h"

class Training : public QObject
{
    Q_OBJECT
public:
    explicit Training(QObject *parent = 0);
    ~Training();

    void trainWithData(const QString& dataFolder, const QStringList& trainingFilePaths);

private:
    GestureRecognition* gestureRecognition;
    QFutureWatcher<void>* trainingWatcher;

signals:
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

public slots:
};

#endif // TRAINING_H
