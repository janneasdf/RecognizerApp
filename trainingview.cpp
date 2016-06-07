#include "trainingview.h"
#include "ui_trainingview.h"
#include <qdir.h>

TrainingView::TrainingView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trainingView)
{
    ui->setupUi(this);
}

void TrainingView::initialize(Training *training)
{
    this->training = training;
    connect(training, SIGNAL(trainingStarted()), this, SLOT(onTrainingStarted()), Qt::UniqueConnection);
    connect(training, SIGNAL(trainingCompleted()), this, SLOT(onTrainingCompleted()), Qt::UniqueConnection);
    connect(ui->trainButton, SIGNAL(clicked(bool)), this, SLOT(startTraining()), Qt::UniqueConnection);
    initializeListViews();
}

void TrainingView::initializeListViews()
{
    // Read training data filenames and populate listview
    // Note: training data has x.dat and x_events.dat files, we search for "x"
    QDir trainingDataDir(trainingFilesFolder);
    QStringList trainingFiles = trainingDataDir.entryList(QDir::Files);
    QStringList dataFileBaseNames;
    for (const QString& trainingFile : trainingFiles)
    {
        if (!trainingFile.endsWith("_events.dat") && trainingFile.endsWith(".dat"))
        {
            // Filename without ".dat"
            QString trainingFileBaseName = trainingFile.split('.')[0];
            QString matchingEventsFile = trainingFileBaseName + "_events.dat";
            for (const QString& file : trainingFiles)
            {
                if (file.endsWith("_events.dat") && file.compare(matchingEventsFile) == 0)
                {
                    dataFileBaseNames.append(trainingFileBaseName);
                    break;
                }
            }
        }
    }
    if (trainingFilesModel)
        delete trainingFilesModel;
    trainingFilesModel = new QStringListModel(dataFileBaseNames);
    ui->trainingFilesList->setModel(trainingFilesModel);

    // Read trained model filenames and populate listview
    QDir trainedModelsDir(trainedModelsFolder);
    QStringList trainedModels = trainedModelsDir.entryList(QDir::Files);
    trainedModelsModel = new QStringListModel(trainedModels);
    ui->trainedModelsList->setModel(trainedModelsModel);
}

void TrainingView::onTrainingStarted()
{
    ui->trainButton->setDisabled(true);
    ui->trainButton->setText("Training...");
}

void TrainingView::onTrainingCompleted()
{
    ui->trainButton->setDisabled(false);
    ui->trainButton->setText("Train model \non selected");
}

void TrainingView::startTraining()
{
    QStringList selectedTrainingFiles;
    for (const QModelIndex& index : ui->trainingFilesList->selectionModel()->selectedIndexes())
    {
        selectedTrainingFiles.append(index.data().toString());
    }
    training->trainWithData(trainingFilesFolder, selectedTrainingFiles);
}

TrainingView::~TrainingView()
{
    delete ui;
}
