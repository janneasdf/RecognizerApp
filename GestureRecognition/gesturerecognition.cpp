#include "gesturerecognition.h"
#include "file_parsing.h"
#include "sensor_events.h"
#include "event_type_converter.h"
#include "GRT_helper.h"
#include <QtConcurrent/QtConcurrent>

GestureRecognition::GestureRecognition(QObject* parent) : QObject(parent)
{
    connect(&recognizer, SIGNAL(trainingStarted()), this, SIGNAL(trainingStarted()));
    connect(&recognizer, SIGNAL(trainingCompleted()), this, SIGNAL(trainingCompleted()));
    connect(&recognizer, SIGNAL(recognitionResult(QString)), this, SIGNAL(gestureRecognitionResult(QString)));

    gestureRecognitionTimer.start(100);
    connect(&gestureRecognitionTimer, SIGNAL(timeout()), this, SLOT(runRecognition()));

    // For concurrent (asynchronous) gesture recognition
    recognitionWatcher = new QFutureWatcher<void>(this);
}

void GestureRecognition::trainFromData(const QString& trainingFolder, const QStringList& filenames)
{
    // Convert Qt types to standard library types
    vector<string> filenames_std;
    for (const QString& filename : filenames)
    {
        filenames_std.push_back(filename.toStdString());
    }
    vector<labeled_event_data> labeledData = read_labeled_training_data(trainingFolder.toStdString(), filenames_std);
    event_type_converter eventTypeConverter;
    eventTypeConverter.initialize(labeledData);
    TimeSeriesClassificationData grtData = extract_training_data(labeledData, eventTypeConverter);

    recognizer.trainFromData(grtData, eventTypeConverter);
}

void GestureRecognition::onDataSourceChanged(BallCommunicationBase *ballCommunication)
{
    this->ballCommunication = ballCommunication;
}

void GestureRecognition::runRecognition()
{
    if (recognitionWatcher->isRunning())
        return;
    recognitionWatcher->setFuture(QtConcurrent::run([this]() -> void
    {
        recognizer.runRecognition(getReceivedData());
    }));
}

void GestureRecognition::setParameters()
{

}

void GestureRecognition::startRecognition()
{

}

void GestureRecognition::stopRecognition()
{

}

void GestureRecognition::restartGestureRecognition()
{

}

MatrixDouble GestureRecognition::getReceivedData()
{
    MatrixDouble dataMatrix;
    if (!ballCommunication)
        return dataMatrix;

    auto data = ballCommunication->getProcessedData();
    for (auto& ballData : data)
    {
        VectorDouble row;
        row.push_back(ballData.accelerationXYZNoG);
        row.push_back(ballData.gyroXYZ);
        dataMatrix.push_back(row);
    }
    return dataMatrix;
}

