#include "training.h"
#include <qthread.h>
#include <QtConcurrent/QtConcurrent>

Training::Training(QObject *parent) : QObject(parent)
{
    trainingWatcher = new QFutureWatcher<void>(this);
}

Training::~Training()
{
    trainingWatcher->cancel();
    trainingWatcher->waitForFinished();
}

void Training::initialize(GestureRecognition *gestureRecognition)
{
    this->gestureRecognition = gestureRecognition;
    connect(gestureRecognition, SIGNAL(trainingStarted()), this, SIGNAL(trainingStarted()));
    connect(gestureRecognition, SIGNAL(trainingCompleted()), this, SIGNAL(trainingCompleted()));
}

void Training::trainWithData(const QString& trainingFolder, const QStringList& trainingFilePaths)
{
    trainingWatcher->cancel();
    trainingWatcher->waitForFinished();

    QtConcurrent::run([this](const QString& trainingFolder, const QStringList& trainingFilePaths) -> void
    {
        gestureRecognition->trainFromData(trainingFolder, trainingFilePaths);
    }, trainingFolder, trainingFilePaths);

}

