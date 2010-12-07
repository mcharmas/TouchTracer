#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QTimer>
#include <QMap>

#include "touch.h"

class CalibrationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalibrationWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void calibrationFinished();

public slots:
    void startNextPointCalibration(QPoint p);
    void abortPointCalibration();
    void pointCalibrationCompleted();

    void touchDown(Touch t);
    void touchMoved(Touch t);
    void touchUp(Touch t);

private:
    void drawCalibrationPoints(QPainter &p);
    void drawCalibrationLines(QPainter &p);

    QVector<QPoint> calibrationPoints;
    QVector<QPoint> calibrationData;

    QPoint currentCalibrationPoint;

    int offset;
    int pointInCalibration;
    int calibrationProgress;
    bool duringCalibration;
    bool lastPointCompleted;
    bool finished;

    int pointSize;

    QTimer timer;
    QMap<int, Touch> touches;

private slots:
    void updateProgress();

};

#endif // CALIBRATIONWIDGET_H
