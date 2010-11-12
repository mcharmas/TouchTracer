#include "moduletrackingsettings.h"
#include "ui_moduletrackingsettings.h"


ModuleTrackingSettings::ModuleTrackingSettings(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ModuleTrackingSettings)
{
    ui->setupUi(getSettingsWidget());
    thresholdSlider = ui->thresSilder;
    minBlobSizeSlider = ui->minBlobSizeSlider;
    maxBlobSizeSlider = ui->maxBlobSizeSlider;
    movementFilterSlider = ui->movementSlider;
}

ModuleTrackingSettings::~ModuleTrackingSettings()
{
    delete ui;
}

void ModuleTrackingSettings::setThresholdInfo(int x)
{
    if(thresholdSlider->value()!=x)
    {
        thresholdSlider->setValue(x);
    }
    ui->thresInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMinBlobInfo(int x)
{
    if(minBlobSizeSlider->value()!=x)
    {
        minBlobSizeSlider->setValue(x);
    }
    ui->minBlobInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMaxBlobInfo(int x)
{
    if(maxBlobSizeSlider->value()!=x)
    {
        maxBlobSizeSlider->setValue(x);
    }
    ui->maxBlobInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMovementInfo(int x)
{
    if(movementFilterSlider->value()!=x)
    {
        movementFilterSlider->setValue(x);
    }
    ui->movementInfo->setText(QString::number(x));
}
