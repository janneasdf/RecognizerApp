#ifndef PARAMETERVIEW_H
#define PARAMETERVIEW_H

#include <QWidget>

namespace Ui {
class ParameterView;
}

class ParameterView : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterView(QWidget *parent = 0);
    ~ParameterView();

private:
    Ui::ParameterView *ui;
};

#endif // PARAMETERVIEW_H
