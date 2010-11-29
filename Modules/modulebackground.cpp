#include "modulebackground.h"

ModuleBackground::ModuleBackground(QObject *parent) :
    Module(parent), frameToStore(true)
{
    settings = new ModuleBackgroundSettings(NULL);
    init();

    connect(settings, SIGNAL(storeFrameButtonClicked()), this, SLOT(storeFrame()));
    connect(this, SIGNAL(frameStored(QImage)), settings, SLOT(showStoredBackground(QImage)), Qt::QueuedConnection);
}

ModuleBackground::~ModuleBackground()
{
    delete settings;
}

void ModuleBackground::process(Mat& mat)
{
    if(mat.channels()!=1)
    {
        Mat m1;
        cvtColor(mat, m1, CV_RGB2GRAY);
        m1.copyTo(mat);
    }

    if(frameToStore)
    {
        mat.copyTo(storedFrame);
        frameToStore = false;
        QImage img = matToQImage(storedFrame);
        emit frameStored(img);
    }

    mat = mat-storedFrame;
}

void ModuleBackground::storeFrame()
{
    settingsLock();
    frameToStore = true;
    settingsUnlock();
}
