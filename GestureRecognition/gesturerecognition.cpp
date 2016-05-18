#include "gesturerecognition.h"
#include "file_parsing.h"
#include "sensor_events.h"
#include "event_type_converter.h"
#include "GRT_helper.h"

GestureRecognition::GestureRecognition(QObject* parent) : QObject(parent)
{
    QObject::connect(&recognizer, SIGNAL(trainingStarted()), this, SIGNAL(trainingStarted()));
    QObject::connect(&recognizer, SIGNAL(trainingCompleted()), this, SIGNAL(trainingCompleted()));
}

void GestureRecognition::trainFromData(const QString& trainingFolder, const QStringList& filenames)
{
    vector<string> filenames_std;
    for (const QString& filename : filenames)
    {
        filenames_std.push_back(filename.toStdString());
    }
    vector<labeled_event_data> labeledData = read_labeled_training_data(trainingFolder.toStdString(), filenames_std);
    event_type_converter eventTypeConverter;
    eventTypeConverter.initialize(labeledData);
    TimeSeriesClassificationData grtData = extract_training_data(labeledData, eventTypeConverter);

    recognizer.trainFromData(grtData);
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
