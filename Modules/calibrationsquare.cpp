#include "calibrationsquare.h"

CalibrationSquare::CalibrationSquare(QObject *parent) :
    QObject(parent)
{
    matrixReady = false;
    pointsAdded = 0;
    screenPoints = new Point2f[4];
    touchPoints = new Point2f[4];
}

CalibrationSquare::~CalibrationSquare()
{
    delete screenPoints;
    delete touchPoints;
}

void CalibrationSquare::addCalibrationData(Point2f screenPoint, Point2f touchPoint)
{
    if(pointsAdded == 4)
        return;

    screenPoints[pointsAdded] = screenPoint;
    touchPoints[pointsAdded] = touchPoint;
    pointsAdded++;

    if(pointsAdded == 4)
    {
        transformationMatrix = getPerspectiveTransform(touchPoints, screenPoints);
        matrixReady = true;
    }
}

bool CalibrationSquare::isInside(Point2f point)
{
    //TODO: this can be optimized
    QVector<Point2f> v;
    for(int  i = 0; i<4 ; i++)
    {
        v.append(touchPoints[i]);
    }

    Mat m(v.toStdVector());
    int result =  pointPolygonTest(m, point, false);
    return result >= 1 ? true : false;
}

Point2f CalibrationSquare::map(Point2f touchPoint)
{
    vector<Point2f> srcV;
    srcV.push_back(touchPoint);
    Mat src(srcV);

    Point2f point;
    vector<Point2f> dstV;
    dstV.push_back(point);
    Mat dst(dstV);

    perspectiveTransform(src, dst, transformationMatrix);

    Point2f result=dst.at<Point2f>(0,0);
    return result;
}


