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
    Touch(QObject *parent = 0);
    Touch(const Touch& t);
    Touch(const vector<Point> &countours, QObject *parent = 0);
    Touch& operator=(const Touch& t);
    int getArea() { return area; }
    Point getCoordinates() { return middle; }
    const vector<Point>& getCvContour() const { return contourPoints; }
    void setContours(const vector<Point>& contours);
    void drawMiddle(Mat &mat);
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
