#include "modulefilters.h"

ModuleFilters::ModuleFilters(QObject *parent) :
    Module(parent), settings(NULL)
{        
    init();
    settings = new ModuleFiltersSettings();
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
    connect(settings->blurSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBlur(int)));
    connect(settings->gainSlider, SIGNAL(valueChanged(int)), this, SLOT(changeGain(int)));
    blurValue = 0;
    gain = 1;
}

ModuleFilters::~ModuleFilters()
{
    delete settings;
}

void ModuleFilters::process(Mat &mat)
{
    if(blurValue) {
        Mat x;
        mat.copyTo(x);
        blur(mat, x, Size(blurValue,blurValue));
        x.copyTo(mat);
    }

    if(gain!=1) {
        mat *= gain;
    }

}

void ModuleFilters::changeBlur(int x)
{
    settingsLock();
    blurValue = x;
    settingsUnlock();
}

void ModuleFilters::changeGain(int x)
{
    if(x >= 100) {
        settingsLock();
        gain = (double)x/100;
        settingsUnlock();
    }
}
