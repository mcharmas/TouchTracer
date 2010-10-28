#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QThread>
#include <QtGlobal>

#include <cv.h>
#include <highgui.h>

#include "module.h"

using namespace cv;

class ImageProcessor : public QThread
{
    Q_OBJECT
public:
    ImageProcessor(QString, QObject *parent = 0);
    ImageProcessor(QString, QList<Module*> *modules, QObject *parent = 0);
    ~ImageProcessor();
    void init(QString fileName, QList<Module*> *modules);
    void run();
    void setModuleList(QList<Module*> *modules) { mut.lock(); this->modules = modules; mut.unlock(); }
    void chModList() { mut.lock(); }
    void stopChModList() { mut.unlock(); }


public slots:
    void stop() { this->running = false; QThread::wait();}

private:
    VideoCapture *capture;
    int interval;
    bool running;
    QList<Module*> *modules;
    QMutex mut;

};

#endif // IMAGEPROCESSOR_H
