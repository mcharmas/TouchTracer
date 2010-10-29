#include "modulebackground.h"

ModuleBackground::ModuleBackground(QObject *parent) :
    Module(parent), frameToStore(true)
{
    init();
    settings = new ModuleBackgroundSettings(NULL);
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
    connect(settings, SIGNAL(storeFrameButtonClicked()), this, SLOT(storeFrame()));
    connect(this, SIGNAL(frameStored(QImage)), settings, SLOT(showStoredBackground(QImage)), Qt::QueuedConnection);
}

ModuleBackground::~ModuleBackground()
{
    delete settings;
}

void ModuleBackground::process(Mat& m)
{
    if(frameToStore)
    {
        storedFrame = m;
        frameToStore = false;
        QImage img = matToQImage(storedFrame);
        emit frameStored(img);
    }


}

void ModuleBackground::storeFrame()
{
    settingsLock();
    frameToStore = true;
    settingsUnlock();
}
