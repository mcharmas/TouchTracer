#ifndef TOUCH_H
#define TOUCH_H

#include <vector>
#include <QVector>
#include <cv.h>
#include <highgui.h>
#include <QObject>

using namespace std;
using namespace cv;

class Touch : public QObject
{
    Q_OBJECT
public:
    Touch(const vector<Point> &countours, QObject *parent = 0);
    int getArea() { return area; }
    Point getCoordinates() { return middle; }
    vector<Point>& getCvContour() { return contourPoints; }

signals:

public slots:

private:
    Point findMiddle();
    int countArea();

    vector<Point> contourPoints;
    Point middle;
    int area;

};

#endif // TOUCH_H
