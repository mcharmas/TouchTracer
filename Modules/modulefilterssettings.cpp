#include "modulefilterssettings.h"
#include "ui_modulefilterssettings.h"

ModuleFiltersSettings::ModuleFiltersSettings(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ModuleFiltersSettings)
{
    ui->setupUi(getSettingsWidget());
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBlurValue(int)));
}

ModuleFiltersSettings::~ModuleFiltersSettings()
{
    delete ui;
}

void ModuleFiltersSettings::changeBlurValue(int x)
{
    emit blurValueChanged(x);
}
