#include "modulebackground.h"

ModuleBackground::ModuleBackground(QObject *parent) :
    Module(parent)
{
    init();
    settings = new ModuleBackgroundSettings(NULL);
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
}

ModuleBackground::~ModuleBackground()
{
    delete settings;
}

void ModuleBackground::process(Mat&)
{
}
