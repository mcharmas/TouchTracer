#ifndef CALIBRATIONSQUARE_H
#define CALIBRATIONSQUARE_H

#include <QObject>
#include <cv.h>
#include <highgui.h>
#include <QVector>
#include <QPoint>
#include <QDebug>

using namespace cv;

class CalibrationSquare : public QObject
{
    Q_OBJECT
public:
    explicit CalibrationSquare(QObject *parent = 0);
    ~CalibrationSquare();
    bool isInside(Point2f point);
    Point2f map(Point2f touchPoint);

    void addCalibrationData(Point2f screenPoint, Point2f touchPoint);
signals:

public slots:

protected:
    Point2f *screenPoints;
    Point2f *touchPoints;
    Mat transformationMatrix;
    bool matrixReady;
    int pointsAdded;


};

#endif // CALIBRATIONSQUARE_H
