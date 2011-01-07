#include "touch.h"

Mapper* Touch::calibrationMapper = 0;

Touch::Touch(QObject *parent) :QObject(parent)
{
    fixedMiddle = false;
    middle = Point(0,0);
    area = 0;
    found = false;
    setFrameSize(640, 480);
    moved = true;
}

Touch::Touch(const vector<Point>& contours, QObject *parent) :
    QObject(parent)
{
    fixedMiddle = false;
    setContours(contours);
    found = false;
    setFrameSize(640, 480);
}

Touch::Touch(const Touch &t) : QObject(t.parent())
{
    fixedMiddle = t.fixedMiddle;
    setContours(t.getCvContour());
    found = t.isFound();
    id = t.getId();
    setFrameSize(640, 480);
}

Touch::Touch(QPoint &p, QObject *parent)
{
    fixedMiddle = true;
    vector<Point> contours;
    contours.push_back(Point(p.x(), p.y()));
    setContours(contours);
    found = false;
    setFrameSize(640, 480);    
}

Touch& Touch::operator=(const Touch& t)
{
    fixedMiddle = t.fixedMiddle;
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
    if(fixedMiddle)
    {
        Point p = contourPoints[0];
        x = p.x;
        y = p.y;
    }
    else
    {
        Mat m(contourPoints);
        Moments mom = moments(m, true);
        x = mom.m10 / mom.m00;
        y = mom.m01 / mom.m00;
    }
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

Point2f Touch::getPosition()
{
    Point2f p(getTuioX(), getTuioY());

    if(calibrationMapper)
    {
        return calibrationMapper->map(p);
    }
    return p;
}
