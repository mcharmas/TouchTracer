#ifndef MAPPER_H
#define MAPPER_H

#include <QObject>
#include <QDebug>
#include <cv.h>
#include <highgui.h>
#include "calibrationsquare.h"

using namespace cv;

class Mapper : public QObject
{
    Q_OBJECT
public:
    Mapper(QVector<CalibrationSquare*> *squares, QObject *parent = 0);
    ~Mapper();
    Point2f map(Point2f &point);

private:
    QVector<CalibrationSquare*> *squares;

};

#endif // MAPPER_H
