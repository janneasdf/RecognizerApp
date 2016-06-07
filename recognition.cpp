//#include "recognition.h"
//#include <QtConcurrent/QtConcurrent>

//Recognition::Recognition(QObject *parent) : QObject(parent)
//{
//    futureWatcher = new QFutureWatcher<void>(this);
//}

//void Recognition::initialize(GestureRecognition* gestureRecognition)
//{
//    this->gestureRecognition = gestureRecognition;

//    connect(&recognitionTimer, SIGNAL(timeout()), this, SLOT(runRecognition()));
//    connect(gestureRecognition, SIGNAL(gestureRecognitionResult(string)), this, SIGNAL(gestureRecognitionResult(QString)));
//    recognitionTimer.start(300);
//}

//void Recognition::runRecognition()
//{
//    if (futureWatcher->isRunning())
//        return;
//    futureWatcher->setFuture(QtConcurrent::run([this]() -> void
//    {
//        gestureRecognition->runRecognition();
//    }));
//}
