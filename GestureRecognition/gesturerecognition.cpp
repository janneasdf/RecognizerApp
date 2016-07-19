#include "gesturerecognition.h"
#include "file_parsing.h"
#include "sensor_events.h"
#include "event_type_converter.h"
#include "GRT_helper.h"
#include <QtConcurrent/QtConcurrent>
#include "recognitionconfig.h"

GestureRecognition::GestureRecognition(QObject* parent) : QObject(parent)
{
    connect(&recognizer, SIGNAL(trainingStarted()), this, SIGNAL(trainingStarted()));
    connect(&recognizer, SIGNAL(trainingCompleted()), this, SIGNAL(trainingCompleted()));
    connect(&recognizer, SIGNAL(recognitionResult(QString, UINT, QString, float, float)),
            this, SIGNAL(gestureRecognitionResult(QString, UINT, QString, float, float)));

    gestureRecognitionTimer.start(100);
    connect(&gestureRecognitionTimer, SIGNAL(timeout()), this, SLOT(runRecognition()));

    // For concurrent (asynchronous) gesture recognition
    recognitionWatcher = new QFutureWatcher<void>(this);

    // Listen to parameter changes and apply them to the recognizer
    connect(&RecognitionConfigFactory::getInstance(), SIGNAL(parametersChanged()), this,
            SLOT(updateRecognizerParameters()));
    // Initialize recognition parameters
    updateRecognizerParameters();
}

void GestureRecognition::trainFromData(const QString& trainingFolder, const QStringList& filenames)
{
    // Convert Qt types to standard library types
    vector<string> filenames_std;
    for (const QString& filename : filenames)
    {
        filenames_std.push_back(filename.toStdString());
    }
//    vector<labeled_event_data> labeledData = read_labeled_training_data(trainingFolder.toStdString(), filenames_std);
    float gestureWindowSize = RecognitionConfigFactory::getInstance().getGestureWindow();
    vector<labeled_event_data> labeledData =
            parse_helpers::read_labeled_training_data_separate(trainingFolder.toStdString(),
                                                               filenames_std, gestureWindowSize);
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
        vector<float> timestamps;
        MatrixDouble data = getReceivedData(timestamps);
        recognizer.runRecognition(data, timestamps);
                                                    }));
}

void GestureRecognition::updateRecognizerParameters()
{
    auto& config = RecognitionConfigFactory::getInstance();
    GestureClassifierType classifierType = config.getClassifier();
    recognitionWatcher->cancel();
    recognizer.updateParameters(classifierType, 10); // todo maybe have to make sure recognition doesn't start right before (with a mutex)
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

MatrixDouble GestureRecognition::getReceivedData(vector<float>& timestamps)
{
    MatrixDouble dataMatrix;
    if (!ballCommunication)
        return dataMatrix;

    auto data = ballCommunication->getProcessedData();
    timestamps.clear();
    for (auto& ballData : data)
    {
        VectorDouble row;
        row.push_back(ballData.accelerationXYZNoG);
        row.push_back(ballData.gyroXYZ);
        dataMatrix.push_back(row);
        timestamps.push_back(ballData.t);
    }
    return dataMatrix;
}

