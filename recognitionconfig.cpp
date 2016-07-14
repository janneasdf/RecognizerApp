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

void RecognitionConfig::setGestureWindow(float seconds)
{
    QMutexLocker locker(&parameterMutex);
    gestureWindow = seconds;
}

void RecognitionConfig::setRecognitionWindow(float seconds)
{
    QMutexLocker locker(&parameterMutex);
    recognitionWindow = seconds;
}
