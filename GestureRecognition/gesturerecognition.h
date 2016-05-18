#ifndef GESTURERECOGNITION_H
#define GESTURERECOGNITION_H

#include <string>
#include <vector>
#include <iostream>
#include <QObject>
#include "recognizer.h"

using std::string;
using std::vector;

/* This class is an easy interface between GUI and logic for gesture recognition.
 * The logic for training and recognition is handled by the Recognizer class.
 *
 */
class GestureRecognition : public QObject
{
    Q_OBJECT
public:
    explicit GestureRecognition(QObject* parent = 0);

    // Training related functions
    void setParameters();

    // Real-time recognition related functions
    void startRecognition();
    void stopRecognition();
    void restartGestureRecognition();

private:
    Recognizer recognizer;

public slots:
    void trainFromData(const QString& dataFolder, const QStringList& filenames);

signals:
    void gestureRecognitionResult(string result);
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

};

#endif // GESTURERECOGNITION_H
