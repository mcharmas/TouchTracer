#include "modulevideo.h"

ModuleVideo::ModuleVideo(QObject *parent) :
    Module(parent)
{
    init();
    settings = new ModuleVideoSettigns(NULL);
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
}

ModuleVideo::~ModuleVideo()
{
    delete settings;
}

void ModuleVideo::process(Mat&)
{
}


