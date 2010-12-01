#include "modulefilters.h"

ModuleFilters::ModuleFilters(QObject *parent) :
    Module(parent), settings(NULL)
{        
    settings = new ModuleFiltersSettings();
    init();
    connect(settings->blurSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBlur(int)));
    connect(settings->sharpSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSharp(int)));
    connect(settings->gainSlider, SIGNAL(valueChanged(int)), this, SLOT(changeGain(int)));
    connect(settings->vFlip,SIGNAL(stateChanged(int)), this, SLOT(changeFlip(int)));
    connect(settings->hFlip, SIGNAL(stateChanged(int)), this, SLOT(changeFlip(int)));

    changeBlur(settings->blurSlider->value());
    changeGain(settings->gainSlider->value());
    changeSharp(settings->sharpSlider->value());
    changeFlip(0);
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

    if(sharpValue) {
        Mat blured, subst, unsharped;
        blur(mat, blured, Size(sharpValue, sharpValue));
        subst = mat - blured;
        unsharped = mat + subst;
        unsharped.copyTo(mat);
    }

    if(gain!=1) {
        mat *= gain;
    }

    if(vFlip || hFlip)
    {
        Mat flipped;
        int param=1;
        if(vFlip && hFlip)
            param = -1;
        else if(vFlip)
            param = 0;
        flip(mat, flipped, param);
        flipped.copyTo(mat);
    }
}

void ModuleFilters::changeBlur(int x)
{
    settingsLock();
    blurValue = x;
    settingsUnlock();
}

void ModuleFilters::changeSharp(int x)
{
    settingsLock();
    sharpValue = x;
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

void ModuleFilters::changeFlip(int)
{
    settingsLock();
    vFlip = settings->vFlip->isChecked();
    hFlip = settings->hFlip->isChecked();
    settingsUnlock();
}
