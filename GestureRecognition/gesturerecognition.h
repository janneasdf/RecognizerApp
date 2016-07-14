#ifndef GESTURERECOGNITION_H
#define GESTURERECOGNITION_H

#include <string>
#include <vector>
#include <iostream>
#include <QObject>
#include <QTimer>
#include <QFutureWatcher>
#include "recognizer.h"
#include "BallCommunication/ballcommunicationbase.h"

// todo: maybe don't use types from BallCommunication
#include "BallCommunication/declaration.h"

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
    QTimer gestureRecognitionTimer;
    QFutureWatcher<void>* recognitionWatcher;

    BallCommunicationBase* ballCommunication = 0;
    MatrixDouble getReceivedData(vector<float>& timestamps);

public slots:
    void trainFromData(const QString& dataFolder, const QStringList& filenames);
    void onDataSourceChanged(BallCommunicationBase* ballCommunication);

private slots:
    void runRecognition();

signals:
    void gestureRecognitionResult(const QString& result, UINT gesture, const QString& gestureName, float gestureStartTime, float gestureEndTime);
    void trainingStarted();
    void trainingCompleted();
    void trainingError(const QString& error);

};

#endif // GESTURERECOGNITION_H
