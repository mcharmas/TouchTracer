#include "moduletrackingsettings.h"
#include "ui_moduletrackingsettings.h"


ModuleTrackingSettings::ModuleTrackingSettings(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ModuleTrackingSettings)
{
    ui->setupUi(getSettingsWidget());
    thresholdSlider = ui->thresSilder;
}

ModuleTrackingSettings::~ModuleTrackingSettings()
{
    delete ui;
}
