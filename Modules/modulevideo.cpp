#include "modulevideo.h"

ModuleVideo::ModuleVideo(QObject *parent) :
    Module(parent)
{
    settings = new ModuleVideoSettigns(NULL);
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
    init();
}

ModuleVideo::~ModuleVideo()
{
    delete settings;
}

void ModuleVideo::process(Mat &mat)
{
}


