#include "touch.h"

Touch::Touch(QObject *parent) :QObject(parent)
{
    middle = Point(0,0);
    area = 0;
}

Touch::Touch(const vector<Point>& contours, QObject *parent) :
    QObject(parent)
{
    setContours(contours);
}

Touch::Touch(const Touch &t) : QObject(t.parent())
{
    setContours(t.getCvContour());
}

Touch& Touch::operator=(const Touch& t)
{
    setContours(t.getCvContour());
    return *this;
}

void Touch::setContours(const vector<Point>& contours)
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


void Touch::drawMiddle(Mat &mat)
{
    Point up(getCoordinates().x, getCoordinates().y+2);
    Point down(getCoordinates().x, getCoordinates().y-2);
    Point left(getCoordinates().x-2, getCoordinates().y);
    Point right(getCoordinates().x+2, getCoordinates().y);
    line(mat, up, down, Scalar(0,0,255,0), 1);
    line(mat, left, right, Scalar(0,0,255,0), 1);
}
