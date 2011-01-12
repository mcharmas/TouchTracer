#ifndef TOUCH_H
#define TOUCH_H

#include <vector>
#include <QVector>
#include <cv.h>
#include <highgui.h>
#include <QObject>
#include <QPoint>
#include "mapper.h"

using namespace std;
using namespace cv;

/**
 * @brief Class holding all information about touch.
*/
class Touch : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs empty touch.
     * @param parent
    */
    Touch(QObject *parent = 0);

    /**
     * @brief Copy constructor.
     * @param t touch contours.
    */
    Touch(const Touch& t);

    /**
     * @brief Creates touch on the basis of contours.
     * @param countours OpenCV contours.
     * @param parent QObject parent.
    */
    Touch(const vector<Point> &countours, QObject *parent = 0);

    /**
     * @brief Creates touch on the basis of QPoint.
     * @param p point of touch
     * @param parent QObject parent.
    */
    Touch(QPoint &p, QObject *parent = 0);

    /**
     * @brief Assignement operator.
     * @param t touch to assign
     * @return Touch & this
    */
    Touch& operator=(const Touch& t);

    /**
     * @brief Returns touch size.
     * @return touch size in pixels
    */
    int getArea() { return area; }

    /**
     * @brief Returns position of touch.
     * @return Touch position.
    */
    Point getCoordinates() const { return middle; }

    /**
     * @brief Returns Y position of touch in TUIO format.
     * @return Touch position.
    */
    float getTuioX() const { return (float)middle.x / Touch::width; }

    /**
     * @brief Returns Y position of touch in TUIO format.
     * @return Touch position.
    */
    float getTuioY() const { return (float)middle.y / Touch::height; }

    /**
     * @brief Returns position of coursor after translation by calibration matrix.
     * @return Point2f
    */
    Point2f getPosition();

    /**
     * @brief Returns OpenCv contours.
     * @return OpenCV Contours.
    */
    const vector<Point>& getCvContour() const { return contourPoints; }

    /**
     * @brief Sets new contours for the touch counting area and position again.
     * @param contours new contours
    */
    void setContours(const vector<Point>& contours);

    /**
     * @brief Draws position of the touch on given Mat.
     * @param mat to draw the position on
    */
    void drawMiddle(Mat &mat);

    /**
     * @brief Draws touch id on the given Mat.
     * @param mat to draw the id on
    */
    void drawId(Mat &mat);

    /**
     * @brief Sets touch id.
     * @param id new id
    */
    void setId(long id) { found=true; this->id = id; }

    /**
     * @brief Returns touch id.
     * @return id
    */
    long getId() const { return id; }

    /**
     * @brief Returns if touch has an id.
     * @return if touch has id
    */
    bool isFound() const { return found; }

    /**
     * @brief Counts euclidan distance between touches this touch and parameter.
     * @param t second touch
     * @return double distance between this touch and t parameter
    */
    double distance(const Touch& t) const;

    /**
     * @brief Sets point as moved (TUIO message will be sent by tracker).
     * @param b moved or not
    */
    void setMoved(bool b) { moved = b; }

    /**
     * @brief Returns if the point is to be consider as moved.
     * @return moved or not
    */
    bool hasMoved() { return moved; }

    /**
     * @brief Sets calibration mapper used by getPosition() method.
     * @param m mapper
    */
    static void setCalibrationMapper(Mapper* m)
    {
        if(calibrationMapper)
            delete calibrationMapper;
        calibrationMapper = m;
    }

    /**
     * @brief Sets frame size of current image input.
     *
     * Used when computing TUIO scaled coordinates.
     * @param w width
     * @param h height
    */
    static void setFrameSize(int w, int h)
    {
        Touch::width = w;
        Touch::height = h;
    }

protected:
    /**
     * @brief Calculates position of the point.
     * @return Point position
    */
    Point findMiddle();

    /**
     * @brief Calculates size of touch.
     * @return int touch size.
    */
    int countArea();

    bool found; /**< Indicates if touch is found. */
    vector<Point> contourPoints; /**< OpenCV contour. */
    Point middle; /**< Position of the touch. */
    int area; /**< Size of the touch. */
    long id; /**< Touch id. */
    bool moved; /**< if point was moved (used by movemement filter) */
    bool fixedMiddle; /**< one point touch (mouse emulation) */

    static Mapper* calibrationMapper; /**< calibration mapper */
    static int width; /**< frame width */
    static int height; /**< frame height */
};



#endif // TOUCH_H
