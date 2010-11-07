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
    Point getCoordinates() const { return middle; }
    const vector<Point>& getCvContour() const { return contourPoints; }
    void setContours(const vector<Point>& contours);

    void drawMiddle(Mat &mat);
    void drawId(Mat &mat);

    void setId(long id) { found=true; this->id = id; }
    long getId() const { return id; }
    bool isFound() const { return found; }
    double distance(const Touch& t) const;
signals:

public slots:

private:
    Point findMiddle();
    int countArea();
    bool found;

    vector<Point> contourPoints;
    Point middle;
    int area;

    long id;


};

#endif // TOUCH_H
