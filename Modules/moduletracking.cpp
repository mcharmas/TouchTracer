#include "moduletracking.h"

ModuleTracking::ModuleTracking(QObject *parent) :
    Module(parent)
{
    init();
    settings = new ModuleTrackingSettings();
    connect(settings->thresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(setThreshold(int)));
    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
    thres = 80;
}

ModuleTracking::~ModuleTracking()
{
    delete settings;
}

void ModuleTracking::process(cv::Mat &mat)
{

    vector<vector<Point> > contours;
    if(mat.channels()!=1)
    {
        Mat m1;
        cvtColor(mat, m1, CV_RGB2GRAY);
        m1.copyTo(mat);
    }
    Mat thresholded;
    threshold(mat, thresholded, thres, 255, THRESH_BINARY);

    findContours(thresholded, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    cvtColor(thresholded, mat, CV_GRAY2BGR);
    drawContours(mat, contours, -1, Scalar(0,255,255,0), 3);

}

void ModuleTracking::setThreshold(int x)
{
    settingsLock();
    thres = x;
    settingsUnlock();
}
