#ifndef MAPPER_H
#define MAPPER_H

#include <QObject>
#include <QDebug>
#include <cv.h>
#include <highgui.h>
#include "calibrationsquare.h"

using namespace cv;

/**
 * @brief Object use for easy mapping touch coordinates to screen coordinates.
 *
 * Uses CalibrationSquare objects.
*/
class Mapper : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Construct objects using CalibrationSquare vector.
     *
     * @param squares
     * @param parent
    */
    Mapper(QVector<CalibrationSquare*> *squares, QObject *parent = 0);

    /**
     * @brief Clean up.
     *
    */
    ~Mapper();

    /**
     * @brief Maps touch point to screen point using collection of callibration squares.
     * @param point to be mapped
     * @return Point2f correspondin point in screen coordinates.
    */
    Point2f map(Point2f &point);

private:
    QVector<CalibrationSquare*> *squares; /**< Squares collection. */

};

#endif // MAPPER_H
