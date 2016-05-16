#ifndef GESTURERECOGNITION_H
#define GESTURERECOGNITION_H

#include <string>
#include <iostream>
#include <QObject>

using std::string;

class GestureRecognition : QObject
{
    Q_OBJECT
public:
    GestureRecognition();

    void TrainFromData(const string& filename);
    void SetParameters();

    void StartRecognition();
    void StopRecognition();
    void RestartGestureRecognition();

signals:
    void GestureRecognitionResult(string result);


};

#endif // GESTURERECOGNITION_H
