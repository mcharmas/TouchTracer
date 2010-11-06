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
}

ModuleTrackingSettings::~ModuleTrackingSettings()
{
    delete ui;
}

void ModuleTrackingSettings::setThresholdInfo(int x)
{
    ui->thresInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMinBlobInfo(int x)
{
    ui->minBlobInfo->setText(QString::number(x));
}

void ModuleTrackingSettings::setMaxBlobInfo(int x)
{
    ui->maxBlobInfo->setText(QString::number(x));
}
