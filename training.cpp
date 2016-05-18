#include "training.h"
#include <qthread.h>
#include <QtConcurrent/QtConcurrent>

Training::Training(QObject *parent) : QObject(parent)
{
    gestureRecognition = new GestureRecognition(this);
    QObject::connect(gestureRecognition, SIGNAL(trainingStarted()), this, SIGNAL(trainingStarted()));
    QObject::connect(gestureRecognition, SIGNAL(trainingCompleted()), this, SIGNAL(trainingCompleted()));

    trainingWatcher = new QFutureWatcher<void>(this);
}

Training::~Training()
{
    trainingWatcher->cancel();
    trainingWatcher->waitForFinished();
}

void Training::trainWithData(const QString& trainingFolder, const QStringList& trainingFilePaths)
{
    // todo
    QtConcurrent::run(
                [this](const QString& trainingFolder, const QStringList& trainingFilePaths) -> void
    {
        gestureRecognition->trainFromData(trainingFolder, trainingFilePaths);
    }, trainingFolder, trainingFilePaths);

}

