#ifndef TRACKER_H
#define TRACKER_H

#include <QObject>
#include <set>
#include <QMap>
#include <QPair>
#include <QList>
#include <QVector>
#include <QDebug>
#include <cv.h>
#include <highgui.h>

#include "touch.h"

using namespace std;
using namespace cv;

class Tracker : public QObject
{
    Q_OBJECT
public:
    explicit Tracker(QObject *parent = 0);
    ~Tracker();
    void pushNewTouches(vector<vector<Point> >& touches, Mat& mat);


signals:

public slots:

private:
    QList<QVector<Touch>*> *frameTouches;
    void destroyFrameTouches(QVector<Touch>* touches);
    void destroyAllFrames();
    int framesToStore;
    int usedIds;

    void identifyFingers(QVector<Touch> *touches);
    long findId(const Touch& t, QList<QVector<Touch>*> list, QMap<int, bool>& takenIds);

    double maxTravelDistance;

};

#endif // TRACKER_H
