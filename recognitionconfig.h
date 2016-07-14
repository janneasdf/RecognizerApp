#ifndef RECOGNITIONCONFIG_H
#define RECOGNITIONCONFIG_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

/* QThread-safe class for setting and updating
 * parameters for gesture recognition.
 */
class RecognitionConfig : QObject
{
    Q_OBJECT
public:
    RecognitionConfig()
    {
        gestureWindow = 0.5;
        recognitionWindow = 1.0;
    }

    // Amount of data (in milliseconds) to take around
    // event markers for gesture data
    float getGestureWindow();

    // Amount of most recent data (in milliseconds) to
    // consider for trying to detect a gesture
    float getRecognitionWindow();

    void setGestureWindow(float seconds);
    void setRecognitionWindow(float seconds);

private:
    float gestureWindow;
    float recognitionWindow;

    QMutex parameterMutex;
};

// Factory class for creating and accessing an instance of
// RecognitionConfig.
class RecognitionConfigFactory
{
public:
    static RecognitionConfig& getInstance()
    {
        static RecognitionConfig instance;
        return instance;
    }
};

#endif // RECOGNITIONCONFIG_H
