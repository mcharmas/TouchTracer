#ifndef CALIBRATIONSQUARE_H
#define CALIBRATIONSQUARE_H

#include <QObject>
#include <cv.h>
#include <highgui.h>
#include <QVector>
#include <QPoint>
#include <QDebug>

using namespace cv;

/**
 * @brief Holds information about single calibration square.
 *
 * Used for mapping position between camera touch coordinates and screen position.
*/
class CalibrationSquare : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Creates object.
     * @param parent QObject parent
    */
    explicit CalibrationSquare(QObject *parent = 0);

    /**
     * @brief Cleanup.
    */
    ~CalibrationSquare();

    /**
     * @brief Checks if point is inside of a square.
     * @param point to be checked
     * @return bool response
    */
    bool isInside(Point2f point);

    /**
     * @brief Maps coordinates of camera touch point to the screen position according to calibration grid.
     * @param touchPoint to be mapped
     * @return Point2f mapped coordinates
    */
    Point2f map(Point2f touchPoint);

    /**
     * @brief Adds calibration data to this square.
     * @param screenPoint screen point
     * @param touchPoint corresponding touch point
    */
    void addCalibrationData(Point2f screenPoint, Point2f touchPoint);

protected:
    Point2f *screenPoints; /**< Screen points. */
    Point2f *touchPoints; /**< Touch points */
    Mat transformationMatrix; /**< Transformation matrix computed from coordinates. */
    bool matrixReady; /**< Flag if matrix is already computed. */
    int pointsAdded; /**< Added coordinates counter. */

};

#endif // CALIBRATIONSQUARE_H
