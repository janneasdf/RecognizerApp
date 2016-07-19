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

float RecognitionConfig::getTargetRecognitionInterval()
{
    QMutexLocker locker(&parameterMutex);
    return targetRecognitionInterval;
}

GestureClassifierType RecognitionConfig::getClassifier()
{
    QMutexLocker locker(&parameterMutex);
    return classifierType;
}

void RecognitionConfig::setGestureWindow(float seconds)
{
    parameterMutex.lock();
    gestureWindow = seconds;
    parameterMutex.unlock();
    emit parametersChanged();
}

void RecognitionConfig::setRecognitionWindow(float seconds)
{
    parameterMutex.lock();
    recognitionWindow = seconds;
    parameterMutex.unlock();
    emit parametersChanged();
}

void RecognitionConfig::setTargetRecognitionInterval(float seconds)
{
    parameterMutex.lock();
    targetRecognitionInterval = seconds;
    parameterMutex.unlock();
    emit parametersChanged();
}

void RecognitionConfig::setClassifier(GestureClassifierType classifier)
{
    parameterMutex.lock();
    classifierType = classifier;
    parameterMutex.unlock();
    emit parametersChanged();
}

