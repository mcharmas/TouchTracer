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

class CalibrationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalibrationWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    Mapper* getCalibrationData();

signals:
    void calibrationFinished();

public slots:
    void touchDown(Touch t);
    void touchMoved(Touch t);
    void touchUp(Touch t);

private:
    void startNextPointCalibration(QPoint p);
    void abortPointCalibration();
    void pointCalibrationCompleted();
    void restartCalibration();
    Point2f scalePoint(const QPoint& p);

    void generateCalibrationPoints();

    void drawCalibrationPoints(QPainter &p);
    void drawCalibrationLines(QPainter &p);
    void drawTouches(QPainter &p);

    QVector<QPoint> calibrationPoints;
    QVector<QPoint> calibrationData;

    QPoint currentCalibrationPoint;

    int top_offset;
    int down_offset;
    int left_offset;
    int right_offset;

    int rows;
    int cols;

    int pointInCalibration;
    int calibrationProgress;
    bool duringCalibration;
    bool lastPointCompleted;
    bool finished;
    bool started;

    int pointSize;

    QTimer timer;
    QMap<int, Touch> touches;

private slots:
    void updateProgress();

};

#endif // CALIBRATIONWIDGET_H
