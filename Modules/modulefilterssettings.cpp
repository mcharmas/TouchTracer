#include "modulefilterssettings.h"
#include "ui_modulefilterssettings.h"

ModuleFiltersSettings::ModuleFiltersSettings(QWidget *parent) :
    AbstractSettingsWidget("ModuleFilter", parent),
    ui(new Ui::ModuleFiltersSettings),
    PROP_GAIN("gain"),
    PROP_BLUR("blur")
{
    ui->setupUi(getSettingsWidget());
    gainSlider = ui->gainSlider;
    blurSlider = ui->horizontalSlider;

    gainSlider->setValue(getProperty(PROP_GAIN, 0).toInt());
    blurSlider->setValue(getProperty(PROP_BLUR, 100).toInt());

    connect(this->blurSlider, SIGNAL(sliderMoved(int)), this, SLOT(storeBlur(int)));
    connect(this->gainSlider, SIGNAL(sliderMoved(int)), this, SLOT(storeGain(int)));
}

ModuleFiltersSettings::~ModuleFiltersSettings()
{
    delete ui;
}

void ModuleFiltersSettings::storeGain(int g)
{
    storeProperty(PROP_GAIN, g);
}

void ModuleFiltersSettings::storeBlur(int b)
{
    storeProperty(PROP_BLUR, b);
}

