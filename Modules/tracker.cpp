#include "tracker.h"

Tracker::Tracker(QObject *parent) :
    QObject(parent)
{
    frameTouches = new QList<QVector<Touch>*>();
    framesToStore = 3;
}

Tracker::~Tracker()
{
    for(QList<QVector<Touch>*>::iterator it = frameTouches->begin(); it!=frameTouches->end(); it++)
    {
        destroyFrameTouches((*it));
    }
    delete frameTouches;
}

void Tracker::pushNewTouches(vector<vector<Point> >& touches)
{
    if(!touches.size())
        return;

    if(frameTouches->size() == framesToStore)
    {
        QVector<Touch> *t = frameTouches->last();
        frameTouches->removeLast();
        destroyFrameTouches(t);
    }

    QVector<Touch> *t = new QVector<Touch>();
    for(vector<vector<Point> >::iterator it=touches.begin(); it!=touches.end(); it++)
    {
        t->append(Touch(*it));
    }
    frameTouches->append(t);
}

void Tracker::destroyFrameTouches(QVector<Touch> *touches)
{
    delete touches;
}
