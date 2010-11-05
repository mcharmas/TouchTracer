#include "modulefilters.h"

ModuleFilters::ModuleFilters(QObject *parent) :
    Module(parent), settings(NULL)
{        
    init();
    settings = new ModuleFiltersSettings();
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
    connect(settings, SIGNAL(blurValueChanged(int)), this, SLOT(changeBlur(int)));
    blurValue = 0;
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
}

void ModuleFilters::changeBlur(int x)
{
    settingsLock();
    blurValue = x;
    settingsUnlock();
}
