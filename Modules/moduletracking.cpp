#include "moduletracking.h"

ModuleTracking::ModuleTracking(QObject *parent) :
    Module(parent)
{
    init();
    settings = new ModuleTrackingSettings();
    connect(settings->thresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(setThreshold(int)));    
    connect(settings->minBlobSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setMinBlob(int)));
    connect(settings->maxBlobSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setMaxBlob(int)));
    connect(settings->movementFilterSlider, SIGNAL(valueChanged(int)), this, SLOT(setMovementFilterValue(int)));

    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));

    connect(this, SIGNAL(thresholdChanged(int)), settings, SLOT(setThresholdInfo(int)));
    connect(this, SIGNAL(minBlobChanged(int)), settings, SLOT(setMinBlobInfo(int)));
    connect(this, SIGNAL(maxBlobChanged(int)), settings, SLOT(setMaxBlobInfo(int)));
    connect(this, SIGNAL(movementFilterValueChanged(int)), settings, SLOT(setMovementInfo(int)));

    setThreshold(80);
    setMinBlob(200);
    setMaxBlob(300);
    setMovementFilterValue(5);
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
    cvtColor(thresholded, mat, CV_GRAY2BGR);

    findContours(thresholded, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);        

    vector<vector<Point> > contoursToDraw;
    filterContours(contours, contoursToDraw);
    //drawMiddles(mat, touches);
    tracker.pushNewTouches(contoursToDraw, mat);

    drawContours(mat, contoursToDraw, -1, Scalar(0,0,255,0), 2);
}

void ModuleTracking::filterContours(vector<vector<Point> > &contours, vector<vector<Point> >& filtered)
{
    for(vector<vector<Point> >::iterator it=contours.begin(); it!=contours.end(); it++)
    {
        Touch t(*it);
        if(t.getArea() >= minBlob && t.getArea() <= maxBlob)
        {
            filtered.push_back(t.getCvContour());
        }
    }
 }

void ModuleTracking::setThreshold(int x)
{
    if(x<0 || x>255)
    {
        return;
    }

    settingsLock();
    thres = x;
    settingsUnlock();
    emit thresholdChanged(x);
}

void ModuleTracking::setMinBlob(int x)
{
    settingsLock();
    minBlob = x;
    settingsUnlock();
    emit minBlobChanged(x);
}

void ModuleTracking::setMaxBlob(int x)
{
    settingsLock();
    maxBlob = x;
    settingsUnlock();
    emit maxBlobChanged(x);
}

void ModuleTracking::setMovementFilterValue(int x)
{
    settingsLock();
    movementFilterValue = x;
    tracker.setMovementFilter(x);
    settingsUnlock();
    emit movementFilterValueChanged(x);
}
