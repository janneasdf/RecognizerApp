#include "trainingview.h"
#include "ui_trainingview.h"
#include <qdir.h>
#include <qstringlistmodel.h>

TrainingView::TrainingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trainingView)
{
    ui->setupUi(this);
}

void TrainingView::initialize(Training *training)
{
    this->training = training;

    // Read training data filenames and populate listview
    // Note: training data has x.dat and x_events.dat files
    QDir trainingDataDir(QString(trainingFilesFolder.c_str()));
    QStringList trainingFiles = trainingDataDir.entryList(QDir::Files);
    QStringList dataFiles;
    for (const QString& trainingFile : trainingFiles)
    {
        if (!trainingFile.endsWith("_events.dat") && trainingFile.endsWith(".dat"))
        {
            QString matchingEventsFile = trainingFile.split('.')[0] + "_events.dat";
            for (const QString& file : trainingFiles)
            {
                if (file.endsWith("_events.dat") && file.compare(matchingEventsFile) == 0)
                {
                    dataFiles.append(trainingFile);
                    break;
                }
            }
        }
    }
    QStringListModel* trainingFilesModel = new QStringListModel(dataFiles);
    ui->trainingFilesList->setModel(trainingFilesModel);

    // Read trained model filenames and populate listview
    QDir trainedModelsDir(QString(trainedModelsFolder.c_str()));
    QStringList trainedModels = trainedModelsDir.entryList(QDir::Files);
    QStringListModel* trainedModelsModel = new QStringListModel(trainedModels);
    ui->trainedModelsList->setModel(trainedModelsModel);
}

TrainingView::~TrainingView()
{
    delete ui;
}
