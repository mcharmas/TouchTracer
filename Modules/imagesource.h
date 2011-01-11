#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QDebug>
#include <cv.h>
#include <highgui.h>

using namespace cv;

class ImageSource : public QObject
{
    Q_OBJECT
public:
    ImageSource(QObject *parent = 0):QObject(parent),processingTime(0) {}
    virtual void getFrame(Mat &mat) = 0;
    void setProcessingTime(long time) { this->processingTime = time; }
    virtual int droppedFrames() = 0;

protected:
    long getProcessingTime() { return this->processingTime; }

private:
    long processingTime;


};

class FileImageSource : public ImageSource, QThread
{
public:
    FileImageSource(QString fileName, QObject *parent = 0);
    ~FileImageSource();
    void getFrame(Mat &mat);
    int droppedFrames();

protected:
    void retriveFrame(Mat &mat);

private:
    QString fileName;
    VideoCapture *capture;
    int interval;
    int dropped;
    long frameGettingTime;

};

#endif // IMAGESOURCE_H
