#ifndef PARAMETERVIEW_H
#define PARAMETERVIEW_H

#include <QWidget>
#include <map>
#include "GestureRecognition/gesturerecognition.h"
#include "recognitionconfig.h"

namespace Ui {
class ParameterView;
}

class ParameterView : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterView(QWidget *parent = 0);
    ~ParameterView();

    void initialize(GestureRecognition* gestureRecognition);

private slots:
    void on_applyChangesButton_clicked();

private:
    Ui::ParameterView *ui;
    GestureRecognition* gestureRecognition;
    map<string, GestureClassifierType> classifierNameTypeMap;
};

#endif // PARAMETERVIEW_H
