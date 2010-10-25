#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QThread>
#include "module.h"
#include <cv.h>
#include <highgui.h>
#include <QtGlobal>
using namespace cv;

class ImageProcessor : public QThread, public QList<Module*>
{
    Q_OBJECT
public:
    ImageProcessor(VideoCapture* cap, QObject *parent = 0);
    ~ImageProcessor();
    void run();

    void addModule(Module *m, int pos);
    void addModule(Module *m);
    void removeModule(Module *m);
signals:

public slots:
    void stop() { this->running = false; QThread::wait();}

private:
    VideoCapture *capture;
    int interval;
    bool running;

};

#endif // IMAGEPROCESSOR_H
