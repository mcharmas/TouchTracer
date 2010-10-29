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

void ModuleBackground::process(Mat& mat)
{
    if(mat.channels()!=1)
    {
        Mat m1;
        cvtColor(mat, m1, CV_RGB2GRAY);
        mat = m1;
    }

    if(frameToStore)
    {
        mat.copyTo(storedFrame);
        frameToStore = false;
        QImage img = matToQImage(storedFrame);
        emit frameStored(img);
    }

    substractBackground(mat);

}

void ModuleBackground::substractBackground(Mat &mat)
{
    MatIterator_<uchar> org_it = mat.begin<uchar>();
    MatIterator_<uchar> org_end = mat.end<uchar>();
    MatConstIterator_<uchar> bg_it = storedFrame.begin<uchar>();

    for( ; org_it != org_end; org_it++, bg_it++)
    {
        uchar a1 = *org_it;
        uchar a2 = *bg_it;
        uchar c=0;
        if(a2 < a1) {
            c = a1 - a2;
        }
        *org_it = c;
    }
}

void ModuleBackground::storeFrame()
{
    settingsLock();
    frameToStore = true;
    settingsUnlock();
}
