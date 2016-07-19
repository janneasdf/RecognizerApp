#ifndef RECOGNITIONCONFIG_H
#define RECOGNITIONCONFIG_H

#include <QObject>
#include <QMutex>
#include <QMutexLocker>

/* Enumeration for the different available classifiers
 * (Dynamic time warp, Discrete Hidden Markov Model,
 * Continuous HMM).
 */
enum GestureClassifierType
{
    DTW,
    DHMM,
    CHMM
};

/* QThread-safe class for setting and updating
 * parameters for gesture recognition.
 */
class RecognitionConfig : public QObject
{
    Q_OBJECT
public:
    explicit RecognitionConfig(QObject* parent = 0) : gestureWindow(0.5), recognitionWindow(1.0),
        classifierType(GestureClassifierType::DTW)
    {
    }

    // Amount of data (in seconds) to take around
    // event markers for gesture data
    float getGestureWindow();

    // Amount of most recent data (in seconds) to
    // consider for trying to detect a gesture.
    float getRecognitionWindow();

    // Currently used classifying algorithm (DTW, DHMM or CHMM).
    GestureClassifierType getClassifier();

    void setGestureWindow(float seconds);
    void setRecognitionWindow(float seconds);
    void setClassifier(GestureClassifierType classifier);

private:
    float gestureWindow;
    float recognitionWindow;
    GestureClassifierType classifierType;

    QMutex parameterMutex;

signals:
    // Used for notifying when any parameters have been changed.
    void parametersChanged();
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
