#ifndef GESTUREINTERPRETER_H
#define GESTUREINTERPRETER_H

#include <QObject>

/* Purpose of this class is to detect compound gestures, for example
 * "throw" + "bounce" as one gesture.
 */
class GestureInterpreter : public QObject
{
    Q_OBJECT
public:
    explicit GestureInterpreter(QObject *parent = 0);

signals:

public slots:
};

#endif // GESTUREINTERPRETER_H
