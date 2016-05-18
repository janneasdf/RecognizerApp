#ifndef TRAININGVIEW_H
#define TRAININGVIEW_H

#include "training.h"
#include <QWidget>
#include <qstringlistmodel.h>

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
    void initializeListViews();

    Training* training;
    Ui::trainingView *ui;

    QStringListModel* trainingFilesModel = NULL;
    QStringListModel* trainedModelsModel = NULL;

    // Folder path for training data files
    const QString trainingFilesFolder = "./data/training_files/";
    // Folder path for trained gesture recognition models (HMM)
    const QString trainedModelsFolder = "./data/trained_models/";

public slots:
    void onTrainingStarted();
    void onTrainingCompleted();

private slots:
    void startTraining();
};

#endif // TRAININGVIEW_H
