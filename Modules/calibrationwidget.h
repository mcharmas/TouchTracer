#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QTimer>
#include <QMap>
#include <QPair>
#include <QDebug>
#include <cv.h>
#include <highgui.h>

#include "touch.h"
#include "calibrationsquare.h"
#include "mapper.h"
using namespace cv;

/**
 * @brief Widget used to create calibration grid.
*/
class CalibrationWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Creates and shows widget.
     * @param parent QWidget parent
    */
    explicit CalibrationWidget(QWidget *parent = 0);

    /**
     * @brief Event processing key presses.
     *
     *  X, Z adding cols/rows, Shift+X/Y
     *  S start calibration
     *  R restarts calibration process
     * @param ev
    */
    void keyPressEvent(QKeyEvent *);

    /**
     * @brief Paints scene.
    */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Transfers mouse presses to touches for testing purpose.
    */
    void mousePressEvent(QMouseEvent *);

    /**
     * @brief Transfers mouse presses to touches for testing purpose.
     * @param ev
    */
    void mouseReleaseEvent(QMouseEvent *);

    /**
     * @brief Transfers mouse presses to touches for testing purpose.
     * @param ev
    */
    void mouseMoveEvent(QMouseEvent *);

    /**
     * @brief Returns calibration mapper when ready.
     * @return Mapper *
    */
    Mapper* getCalibrationData();

signals:
    /**
     * @brief Signal emmited when calibration is finished.
    */
    void calibrationFinished();

public slots:
    /**
     * @brief Slot which should be connected to touch tracer.
     * @param t
    */
    void touchDown(Touch t);

    /**
     * @brief Slot which should be connected to touch tracer.
     * @param t
    */
    void touchMoved(Touch t);

    /**
     * @brief Slot which should be connected to touch tracer.
     * @param t
    */
    void touchUp(Touch t);

private:
    /**
     * @brief Moves calibration to next point.
     * @param p of touch
    */
    void startNextPointCalibration(QPoint p);

    /**
     * @brief Aborts current point calibration.
    */

    void abortPointCalibration();

    /**
     * @brief Saves calibration and generates Mapper from collected data.
    */
    void pointCalibrationCompleted();

    /**
     * @brief Restarts calibration process.
    */
    void restartCalibration();

    /**
     * @brief Scales point from QT coordinates to TUIO coordinates.
     * @param p to be scalled
     * @return Point2f scalled point
    */
    Point2f scalePoint(const QPoint& p);

    /**
     * @brief Generates calibration points on the grid.
    */
    void generateCalibrationPoints();

    /**
     * @brief Draws calibration points using the painter.
     * @param p painter
    */
    void drawCalibrationPoints(QPainter &p);

    /**
     * @brief Does not work.
     * @param painter
    */
    void drawCalibrationLines(QPainter&);

    /**
     * @brief Draws touches when callibration is finished.
     * @param p
    */
    void drawTouches(QPainter &p);

    QVector<QPoint> calibrationPoints; /**< Points on the screen. */
    QVector<QPoint> calibrationData; /**< Camera points. */

    QPoint currentCalibrationPoint; /**< Current calibration point. */

    int top_offset; /**< Offset from top used while generating calibration points. */
    int down_offset; /**< Down */
    int left_offset; /**< Left */
    int right_offset; /**< Right */

    int rows; /**< Rows count */
    int cols; /**< Cols count */

    int pointInCalibration; /**< Number of point in calibtration */
    int calibrationProgress; /**< Calibration progress. */
    bool duringCalibration; /**< If is during calibration. */
    bool lastPointCompleted; /**< If last point was succesfuly calibrated. */
    bool finished; /**< Calibration is finished. */
    bool started; /**< Calibration is started. */

    int pointSize; /**< Calibration poin size. */

    QTimer timer; /**< Timer counting one touch calibration time to draw proper circle. */
    QMap<int, Touch> touches; /**< Map of current touches on the widget (used by functions touchDown... */

private slots:
    /**
     * @brief Updates progress of point calibration.
    */
    void updateProgress();

};

#endif // CALIBRATIONWIDGET_H
