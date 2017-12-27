#include "daqform.h"
#include "ui_daqform.h"
#include "siprint.h"
#include "desktop_settings.h"

daqForm::daqForm(QWidget *parent, int initialAverage, qulonglong initialMaxFileSize) :
    QDialog(parent),
    ui(new Ui::daqForm)
{
    ui->setupUi(this);

    //Set the Initial Average settings
    if(initialAverage != 1){
        ui->sampleAveragingGroup->setChecked(true);
        ui->numberOfPointsSpinBox->setValue(initialAverage);
    }

    //Initialise the file size box
    if(initialMaxFileSize == 0){
        ui->limitFileSizeGroupBox->setChecked(false);
    } else {
        ui->limitFileSizeGroupBox->setChecked(true);
        ui->fileSizeSpinBox->setValue(initialMaxFileSize/1000000);
    }

    updateLabels();
    //Internal Signal Connect
    //Changed values
    connect(ui->fileSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
    connect(ui->numberOfPointsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
    connect(ui->limitFileSizeGroupBox, SIGNAL(toggled(bool)), this, SLOT(updateValues()));
    connect(ui->sampleAveragingGroup, SIGNAL(toggled(bool)), this, SLOT(updateValues()));

    //Label
    connect(ui->numberOfPointsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateLabels()));
    connect(ui->fileSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateLabels()));

    //Save Button
    connect(ui->saveAsDefaultsButton, SIGNAL(clicked(bool)), this, SLOT(trigger_saveButtonPressed()));

}

daqForm::~daqForm()
{
    delete ui;
}

void daqForm::updateLabels(){
    double effective_sample_rate_single = 375000/((double)ui->numberOfPointsSpinBox->value());
    double effective_sample_rate_double = 750000/((double)ui->numberOfPointsSpinBox->value());
    int num_samples_stored = (ui->fileSizeSpinBox->value() * 1000000) / NUM_BYTES_STORED_PER_DAQ_SAMPLE;

    //Print in SI units
    siprint label_single_siprint("Hz", effective_sample_rate_single);
    siprint label_double_siprint("Hz", effective_sample_rate_double);

    //Shove commas in there, or decimal points if you're European!
    QString label_numSamples = QLocale().toString(num_samples_stored);

    ui->sampleRateLabel_val->setText(label_single_siprint.printVal());
    ui->sampleRateLabel_Double_val->setText(label_double_siprint.printVal());
    ui->numSamplesStoredLabel_Value->setText(label_numSamples);
}

void daqForm::updateValues(){
    qDebug() << "daqForm::updateValues()";

    //Averaging
    if(ui->sampleAveragingGroup->isChecked()){
        updatedAveraging(ui->numberOfPointsSpinBox->value());
    } else updatedAveraging(1);

    //File Size
    if(ui->limitFileSizeGroupBox->isChecked()){
        updatedMaxFileSize(ui->fileSizeSpinBox->value() * 1000000);
    } else updatedMaxFileSize(0);

}

void daqForm::trigger_saveButtonPressed(){
    saveButtonPressed();
}

