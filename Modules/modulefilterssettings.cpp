#include "modulefilterssettings.h"
#include "ui_modulefilterssettings.h"

ModuleFiltersSettings::ModuleFiltersSettings(QWidget *parent) :
    AbstractSettingsWidget("ModuleFilter", parent),
    ui(new Ui::ModuleFiltersSettings),
    PROP_GAIN("gain"),
    PROP_BLUR("blur"),
    PROP_VFLIP("vflip"),
    PROP_HFLIP("hflip")
{
    ui->setupUi(getSettingsWidget());

    gainSlider = ui->gainSlider;
    blurSlider = ui->horizontalSlider;
    vFlip = ui->verticalFlipCheck;
    hFlip = ui->horizontalFlipCheck;

    gainSlider->setValue(getProperty(PROP_GAIN, 0).toInt());
    blurSlider->setValue(getProperty(PROP_BLUR, 100).toInt());
    vFlip->setChecked(getProperty(PROP_VFLIP, false).toBool());
    hFlip->setChecked(getProperty(PROP_HFLIP, false).toBool());

    connect(this->blurSlider, SIGNAL(sliderMoved(int)), this, SLOT(storeBlur(int)));
    connect(this->gainSlider, SIGNAL(sliderMoved(int)), this, SLOT(storeGain(int)));

    connect(this->vFlip, SIGNAL(stateChanged(int)), this, SLOT(storeFlips(int)));
    connect(this->hFlip, SIGNAL(stateChanged(int)), this, SLOT(storeFlips(int)));
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

void ModuleFiltersSettings::storeFlips(int)
{
    storeProperty(PROP_VFLIP, vFlip->isChecked());
    storeProperty(PROP_HFLIP, hFlip->isChecked());
}

