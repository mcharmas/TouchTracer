#include "calibrationwidget.h"

CalibrationWidget::CalibrationWidget(QWidget *parent) :
    QWidget(parent)
{
    showFullScreen();
    offset = 50;
    pointInCalibration = 0;
    calibrationProgress = 0;
    pointSize = 15;

    timer.setInterval(30);
    connect(&timer,SIGNAL(timeout()), this, SLOT(updateProgress()));

    duringCalibration = false;
    lastPointCompleted = false;
    finished = false;
}

void CalibrationWidget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Q)
    {
        ev->accept();
        this->hide();
    }

    if(ev->key() == Qt::Key_U)
    {
        ev->accept();
        update();
    }
}

void CalibrationWidget::paintEvent(QPaintEvent *ev)
{
    calibrationPoints.clear();
    calibrationPoints.append(QPoint(offset,offset));
    calibrationPoints.append(QPoint(width()-offset,offset));
    calibrationPoints.append(QPoint(offset, height()-offset));
    calibrationPoints.append(QPoint(width()-offset, height()-offset));

    QPainter painter(this);
    painter.fillRect(0, 0, this->width(), this->height(), Qt::black);

    drawCalibrationPoints(painter);
    drawCalibrationLines(painter);
}

void CalibrationWidget::drawCalibrationPoints(QPainter &p)
{
    QPen redPen(Qt::red);
    redPen.setWidth(2);
    p.setPen(redPen);
    int i = 0;
    for(QVector<QPoint>::iterator it = calibrationPoints.begin(); it!=calibrationPoints.end(); it++)
    {
        if(i < pointInCalibration)
        {
            QBrush brush(Qt::red);
            p.setBrush(brush);
            p.drawEllipse(*it, pointSize, pointSize);
            p.setBrush(Qt::NoBrush);
        }
        else if(pointInCalibration == i)
        {
            int cSize = 2*pointSize;
            int s = 255 * (calibrationProgress/100.0);
            QColor c(s,s,s);
            QBrush brush(c);
            if(calibrationProgress==100)
            {
                brush.setColor(Qt::red);
            }

            QPen pen(Qt::white);
            pen.setWidth(3);

            p.setBrush(brush);
            p.setPen(pen);

            p.drawEllipse(*it, cSize, cSize);

            p.setBrush(Qt::NoBrush);
            p.setPen(redPen);

        }
        else
        {
            p.drawEllipse(*it, pointSize, pointSize);
        }

        i++;
    }
}

void CalibrationWidget::drawCalibrationLines(QPainter &p)
{
}

void CalibrationWidget::startNextPointCalibration(QPoint p)
{
    if(!duringCalibration)
    {
        duringCalibration = true;
        currentCalibrationPoint = p;
        timer.start();
    }
}

void CalibrationWidget::abortPointCalibration()
{
    if(calibrationProgress == 100)
    {
        pointCalibrationCompleted();
        lastPointCompleted = true;
        pointInCalibration++;
        calibrationProgress=0;
    }
    else
    {
        lastPointCompleted = false;
    }

    duringCalibration = false;

    if(pointInCalibration == calibrationPoints.size())
    {
        finished = true;
        emit calibrationFinished();
    }
    update();
}

void CalibrationWidget::pointCalibrationCompleted()
{
    calibrationData.append(currentCalibrationPoint);
}

void CalibrationWidget::mousePressEvent(QMouseEvent *ev)
{
    startNextPointCalibration(ev->pos());
}

void CalibrationWidget::mouseReleaseEvent(QMouseEvent *)
{
    abortPointCalibration();
}

void CalibrationWidget::touchDown(Touch t)
{
    touches.insert(t.getId(), t);
    if(!finished && touches.size() == 1)
    {
        int x = width()*t.getTuioX();
        int y = height()*t.getTuioY();
        startNextPointCalibration(QPoint(x,y));
    }

    if (!finished && touches.size() >= 1 )
    {
        abortPointCalibration();
    }
    update();
}

void CalibrationWidget::touchMoved(Touch t)
{
    touches[t.getId()] = t;
    update();
}

void CalibrationWidget::touchUp(Touch t)
{
    touches.remove(t.getId());
    update();
}

void CalibrationWidget::updateProgress()
{
    if(calibrationProgress<100)
    {
        if(duringCalibration)
            calibrationProgress++;
        else
            calibrationProgress=0;
    }
    else
        timer.stop();

    update();
}
