#include "recognitionconfig.h"

float RecognitionConfig::getGestureWindow()
{
    QMutexLocker locker(&parameterMutex);
    return gestureWindow;
}

float RecognitionConfig::getRecognitionWindow()
{
    QMutexLocker locker(&parameterMutex);
    return recognitionWindow;
}

GestureClassifierType RecognitionConfig::getClassifier()
{
    QMutexLocker locker(&parameterMutex);
    return classifierType;
}

void RecognitionConfig::setGestureWindow(float seconds)
{
    QMutexLocker locker(&parameterMutex);
    gestureWindow = seconds;
    emit parametersChanged();
}

void RecognitionConfig::setRecognitionWindow(float seconds)
{
    QMutexLocker locker(&parameterMutex);
    recognitionWindow = seconds;
    emit parametersChanged();
}

void RecognitionConfig::setClassifier(GestureClassifierType classifier)
{
    QMutexLocker locker(&parameterMutex);
    classifierType = classifier;
    emit parametersChanged();
}

