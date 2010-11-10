#include "modulefilterssettings.h"
#include "ui_modulefilterssettings.h"

ModuleFiltersSettings::ModuleFiltersSettings(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ModuleFiltersSettings)
{
    ui->setupUi(getSettingsWidget());
    gainSlider = ui->gainSlider;
    blurSlider = ui->horizontalSlider;
}

ModuleFiltersSettings::~ModuleFiltersSettings()
{
    delete ui;
}

