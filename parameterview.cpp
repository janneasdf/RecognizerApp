#include "parameterview.h"
#include "ui_parameterview.h"

ParameterView::ParameterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterView)
{
    ui->setupUi(this);
    const char* dtwChoice = "Dynamic time warping (DTW)";
    const char* dhmmChoice = "Discrete Hidden Markov Model (DHMM)";
    const char* chmmChoice = "Continuous Hidden Markov Model (CHMM)";

    classifierNameTypeMap.insert(std::make_pair(dtwChoice, GestureClassifierType::DTW));
    classifierNameTypeMap.insert(std::make_pair(dhmmChoice, GestureClassifierType::DHMM));
    classifierNameTypeMap.insert(std::make_pair(chmmChoice, GestureClassifierType::CHMM));

    ui->classifierTypeComboBox->addItem(dtwChoice);
    ui->classifierTypeComboBox->addItem(dhmmChoice);
    ui->classifierTypeComboBox->addItem(chmmChoice);
}

ParameterView::~ParameterView()
{
    delete ui;
}

void ParameterView::initialize(GestureRecognition *gestureRecognition)
{
    this->gestureRecognition = gestureRecognition;
    auto& config = RecognitionConfigFactory::getInstance();
    ui->samplingWindowSpinBox->setValue(config.getRecognitionWindow());
    ui->recognitionIntervalSpinbox->setValue(config.getTargetRecognitionInterval());
}

void ParameterView::on_applyChangesButton_clicked()
{
    auto& config = RecognitionConfigFactory::getInstance();
    config.setRecognitionWindow(ui->samplingWindowSpinBox->value());
    config.setTargetRecognitionInterval(ui->recognitionIntervalSpinbox->value());
    config.setClassifier(classifierNameTypeMap[ui->classifierTypeComboBox->currentText().toStdString()]);
}
