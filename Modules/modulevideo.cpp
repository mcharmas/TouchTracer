#include "modulevideo.h"

ModuleVideo::ModuleVideo(QObject *parent) :
    Module(parent)
{
    settings = new ModuleVideoSettigns("ModuleVideo", NULL);
    init();
}

ModuleVideo::~ModuleVideo()
{
    delete settings;
}

void ModuleVideo::process(Mat&)
{
}


