#ifndef TRAININGVIEW_H
#define TRAININGVIEW_H

#include "training.h"
#include <QWidget>

namespace Ui {
class trainingView;
}

using std::string;

class TrainingView : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingView(QWidget *parent = 0);
    ~TrainingView();

    void initialize(Training* training);

private:
    Training* training;
    Ui::trainingView *ui;

    // Folder path for training data files
    const string trainingFilesFolder = "./data/training_files";
    // Folder path for trained gesture recognition models (HMM)
    const string trainedModelsFolder = "./data/trained_models";
};

#endif // TRAININGVIEW_H
