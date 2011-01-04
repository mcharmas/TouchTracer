#include "calibrationwidget.h"

CalibrationWidget::CalibrationWidget(QWidget *parent) :
    QWidget(parent)
{
    //showFullScreen();
    show();
    setFixedSize(640,480);

    top_offset = 50;
    down_offset = 50;
    left_offset = 50;
    right_offset = 50;

    pointInCalibration = 0;
    calibrationProgress = 0;
    pointSize = 15;

    rows = 4;
    cols = 3;

    timer.setInterval(10);
    connect(&timer,SIGNAL(timeout()), this, SLOT(updateProgress()));

    started = false;
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

    if(ev->key() == Qt::Key_S)
    {
        if(started)
        {
            restartCalibration();
        }
        else
        {
            started = true;
        }
        update();
    }

    if(ev->key() == Qt::Key_Z && !started)
    {
        if(ev->modifiers() && Qt::ShiftModifier)
        {
            if(cols > 2)
                cols--;
        }
        else
        {
            cols++;
        }
        update();
    }

    if(ev->key() == Qt::Key_X && !started)
    {
        if(ev->modifiers() && Qt::ShiftModifier)
        {
            if(rows > 2)
                rows--;
        }
        else
        {
            rows++;
        }
        update();
    }

}

void CalibrationWidget::generateCalibrationPoints()
{
    calibrationPoints.clear();
    if(rows < 2)
        rows = 2;
    if(cols < 2)
        cols = 2;

    int row_offset = (height()-left_offset-right_offset)/(rows-1);
    int col_offset = (width()-top_offset-down_offset)/(cols-1);
    int row_start = top_offset;
    int col_start = left_offset;
    for(int i = 0; i<rows; i++)
    {
        int x = col_start;
        int y = row_start;
        for(int j = 0; j < cols; j++)
        {
            calibrationPoints.append(QPoint(x, y));
            x+=col_offset;
        }
        row_start+=row_offset;
    }
}

void CalibrationWidget::restartCalibration()
{
    abortPointCalibration();
    calibrationData.clear();
    pointInCalibration = 0;
}

void CalibrationWidget::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width(), this->height(), Qt::black);

    drawCalibrationPoints(painter);
    drawCalibrationLines(painter);
    drawTouches(painter);
}

Mat* CalibrationWidget::getCalibrationData()
{
    vector<Point2f> src;
    vector<Point2f> dst;
    Mat *h = NULL;
    if(finished && calibrationPoints.size() == calibrationData.size())
    {
        h = new Mat();
        for(int i = 0; i<calibrationPoints.size(); i++)
        {
            QPoint data = calibrationPoints[i];
            QPoint cal = calibrationData[i];
            src.push_back(Point2f(data.x()/(float)width(), data.y()/(float)height()));
            dst.push_back(Point2f(cal.x()/(float)width(), cal.y()/(float)height()));
        }
        Mat m = findHomography(Mat(dst), Mat(src), CV_LMEDS);
        m.copyTo(*h);
    }

    return h;
}

void CalibrationWidget::drawCalibrationPoints(QPainter &p)
{
    generateCalibrationPoints();
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
        else if(pointInCalibration == i && started)
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
    if(!duringCalibration && started)
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

    if(!finished && pointInCalibration == calibrationPoints.size())
    {
        finished = true;
        emit calibrationFinished();
        Touch::setCalibrationMat(getCalibrationData());
    }
    update();
}

void CalibrationWidget::pointCalibrationCompleted()
{
    calibrationData.append(currentCalibrationPoint);
}

void CalibrationWidget::mousePressEvent(QMouseEvent *ev)
{
    QPoint p = ev->pos();
    Touch t(p);
    t.setId(-1);
    touchDown(t);
}

void CalibrationWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    QPoint p = ev->pos();
    Touch t(p);

    t.setId(-1);
    touchUp(t);
}

void CalibrationWidget::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint p = ev->pos();
    Touch t(p);

    t.setId(-1);
    touchMoved(t);
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

    if (!finished && touches.size() > 1 )
    {
        abortPointCalibration();
    }

    update();
}

void CalibrationWidget::touchMoved(Touch t)
{
    Touch &t_old = touches[t.getId()];
    if(t_old.distance(t) > 5)
    {
        abortPointCalibration();
    }
    touches[t.getId()] = t;
    update();
}

void CalibrationWidget::touchUp(Touch t)
{
    touches.remove(t.getId());

    if(duringCalibration)
        abortPointCalibration();

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

void CalibrationWidget::drawTouches(QPainter &p)
{
    if(finished)
    {
        for(QList<Touch>::iterator it = touches.values().begin(); it!=touches.values().end(); it++)
        {
            Touch &t = *it;
            Point2f pos = t.getPosition();
            QPoint c(pos.x*width(), pos.y*height());
            QBrush green(Qt::green);
            p.setBrush(green);
            p.setPen(Qt::green);
            p.drawEllipse(c, 12, 12);
        }
    }
}
