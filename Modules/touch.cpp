#include "touch.h"

Touch::Touch(QObject *parent) :QObject(parent)
{
    middle = Point(0,0);
    area = 0;
    found = false;
}

Touch::Touch(const vector<Point>& contours, QObject *parent) :
    QObject(parent)
{
    setContours(contours);
    found = false;
}

Touch::Touch(const Touch &t) : QObject(t.parent())
{
    setContours(t.getCvContour());
    found = t.isFound();
    id = t.getId();
}


Touch& Touch::operator=(const Touch& t)
{
    setContours(t.getCvContour());
    found = t.isFound();
    id = t.getId();
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

void Touch::drawId(Mat &mat)
{
    Point p(getCoordinates().x, getCoordinates().y-10);
    putText(mat, QString::number(getId()).toStdString(), p, FONT_HERSHEY_SIMPLEX, 1.2, Scalar(0,0,255,0), 2);
}

double Touch::distance(const Touch &t) const
{
    int x_dst = this->getCoordinates().x - t.getCoordinates().x;
    int y_dst = this->getCoordinates().y - t.getCoordinates().y;
    return sqrt(x_dst*x_dst + y_dst*y_dst);
}
