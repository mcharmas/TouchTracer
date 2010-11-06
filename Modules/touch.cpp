#include "touch.h"

Touch::Touch(const vector<Point>& contours, QObject *parent) :
    QObject(parent)
{
    contourPoints = vector<Point>(contours);
    middle = findMiddle();
    area = countArea();
}

Point Touch::findMiddle()
{
    int x=0, y=0;
    for(vector<Point>::iterator it = contourPoints.begin(); it != contourPoints.end(); it++)
    {
        x += (*it).x;
        y += (*it).y;
    }
    x/=contourPoints.size();
    y/=contourPoints.size();

    return Point(x,y);
}

int Touch::countArea()
{
    Mat m(contourPoints);
    return contourArea(m);
}


