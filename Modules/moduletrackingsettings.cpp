#include "moduletrackingsettings.h"
#include "ui_moduletrackingsettings.h"


ModuleTrackingSettings::ModuleTrackingSettings(QWidget *parent) :
    AbstractSettingsWidget("ModuleTracking", parent),
    ui(new Ui::ModuleTrackingSettings),
    PROP_THRESH("threshold"),
    PROP_MINBLOB("minBlob"),
    PROP_MAXBLOB("maxBlob"),
    PROP_MOV("movement")
{
    ui->setupUi(getSettingsWidget());
    thresholdSlider = ui->thresSilder;
    minBlobSizeSlider = ui->minBlobSizeSlider;
    maxBlobSizeSlider = ui->maxBlobSizeSlider;
    movementFilterSlider = ui->movementSlider;

    connect(thresholdSlider, SIGNAL(valueChanged(int)), SLOT(setThresholdInfo(int)));
    connect(minBlobSizeSlider, SIGNAL(valueChanged(int)), SLOT(setMinBlobInfo(int)));
    connect(maxBlobSizeSlider, SIGNAL(valueChanged(int)), SLOT(setMaxBlobInfo(int)));
    connect(movementFilterSlider, SIGNAL(valueChanged(int)), SLOT(setMovementInfo(int)));
    connect(ui->calibrateButton, SIGNAL(clicked()), SLOT(openCalibration()));

    thresholdSlider->setValue(getProperty(PROP_THRESH, 83).toInt());
    minBlobSizeSlider->setValue(getProperty(PROP_MINBLOB, 200).toInt());
    maxBlobSizeSlider->setValue(getProperty(PROP_MAXBLOB, 300).toInt());
    movementFilterSlider->setValue(getProperty(PROP_MOV, 5).toInt());
}

ModuleTrackingSettings::~ModuleTrackingSettings()
{
    delete ui;
}

void ModuleTrackingSettings::setThresholdInfo(int x)
{
    storeProperty(PROP_THRESH, x);
    ui->thresInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMinBlobInfo(int x)
{
    storeProperty(PROP_MINBLOB, x);
    ui->minBlobInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMaxBlobInfo(int x)
{
    storeProperty(PROP_MAXBLOB, x);
    ui->maxBlobInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMovementInfo(int x)
{
    storeProperty(PROP_MOV, x);
    ui->movementInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::openCalibration()
{
    qDebug() << "asdf";
    new CalibrationWidget();
    //c->show();
}
