#ifndef MAINLOGIC_H
#define MAINLOGIC_H

#include <qobject.h>

class MainLogic : public QObject
{
    Q_OBJECT
public:
    explicit MainLogic(QObject *parent = 0);

signals:

public slots:
};

#endif // MAINLOGIC_H
