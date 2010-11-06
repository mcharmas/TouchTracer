#include "moduletracking.h"

ModuleTracking::ModuleTracking(QObject *parent) :
    Module(parent)
{
    init();
    settings = new ModuleTrackingSettings();
    connect(settings->thresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(setThreshold(int)));    
    connect(settings->minBlobSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setMinBlob(int)));
    connect(settings->maxBlobSizeSlider, SIGNAL(valueChanged(int)), this, SLOT(setMaxBlob(int)));

    connect(settings, SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));

    connect(this, SIGNAL(thresholdChanged(int)), settings, SLOT(setThresholdInfo(int)));
    connect(this, SIGNAL(minBlobChanged(int)), settings, SLOT(setMinBlobInfo(int)));
    connect(this, SIGNAL(maxBlobChanged(int)), settings, SLOT(setMaxBlobInfo(int)));

    setThreshold(80);
    setMinBlob(200);
    setMaxBlob(300);
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

    findContours(thresholded, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    cvtColor(thresholded, mat, CV_GRAY2BGR);
    drawContours(mat, contours, -1, Scalar(0,255,255,0), 2);

    vector<vector<Point> > contoursToDraw;
    for(vector<vector<Point> >::iterator it=contours.begin(); it!=contours.end(); it++)
    {
        Touch t(*it);
        if(t.getArea() >= minBlob && t.getArea() <= maxBlob)
        {
            Point up(t.getCoordinates().x, t.getCoordinates().y+2);
            Point down(t.getCoordinates().x, t.getCoordinates().y-2);
            Point left(t.getCoordinates().x-2, t.getCoordinates().y);
            Point right(t.getCoordinates().x+2, t.getCoordinates().y);
            //line(mat, up, down, Scalar(0,255,255,0), 2);
            //line(mat, left, right, Scalar(0,255,255,0), 2);
            contoursToDraw.push_back(t.getCvContour());
        }
    }
    //drawContours(mat, contoursToDraw, -1, Scalar(0,255,255,0), 2);

}

void ModuleTracking::setThreshold(int x)
{
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
