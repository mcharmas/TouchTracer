#ifndef TRACKER_H
#define TRACKER_H

#include <QObject>
#include <QList>
#include <QVector>

#include "touch.h"

class Tracker : public QObject
{
    Q_OBJECT
public:
    explicit Tracker(QObject *parent = 0);
    ~Tracker();
    void pushNewTouches(vector<vector<Point> >& touches);


signals:

public slots:

private:
    QList<QVector<Touch>*> *frameTouches;
    void destroyFrameTouches(QVector<Touch>* touches);
    int framesToStore;

};

#endif // TRACKER_H
