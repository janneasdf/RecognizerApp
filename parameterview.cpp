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
}

ParameterView::~ParameterView()
{
    delete ui;
}

void ParameterView::initialize(GestureRecognition *gestureRecognition)
{
    this->gestureRecognition = gestureRecognition;
}

void ParameterView::on_applyChangesButton_clicked()
{
    float recognitionWindow = ui->samplingWindowSpinBox->value();
    auto& config = RecognitionConfigFactory::getInstance();
    config.setRecognitionWindow(recognitionWindow);
    config.setClassifier(classifierNameTypeMap[ui->classifierTypeComboBox->currentText().toStdString()]);
}
