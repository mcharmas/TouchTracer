#include "imageprocessor.h"

ImageProcessor::ImageProcessor(ImageSource* imgSrc, QObject *parent) :
    QThread(parent)
{
    init(imgSrc, NULL);
}

ImageProcessor::ImageProcessor(ImageSource* imgSrc, QList<Module *> * modules, QObject *parent)
    :     QThread(parent)
{
    init(imgSrc, modules);
}

void ImageProcessor::init(ImageSource *imgSrc, QList<Module *> *modules)
{
    this->imgSrc = imgSrc;
    setModuleList(modules);
    running = true;
    fps = 0;
}

ImageProcessor::~ImageProcessor()
{
    if(this->isRunning()) {
       this->stop();
    }
}

void ImageProcessor::run()
{
    startTimer(1000);

    while(running) {
        fpsMutex.lock();
        fps++;
        fpsMutex.unlock();

        Mat frame;
        imgSrc->getFrame(frame);

        qint64 start = QDateTime::currentMSecsSinceEpoch();
        mut.lock();
        if(modules != NULL) {
            foreach(Module *m, *modules){
                m->processImage(frame);
            }
        }
        mut.unlock();
        qint64 duration = QDateTime::currentMSecsSinceEpoch() - start;
        imgSrc->setProcessingTime(duration);
    }
}

void ImageProcessor::timerEvent(QTimerEvent *)
{
    countFps();
}

void ImageProcessor::countFps()
{
    fpsMutex.lock();
    int xfps = fps;
    fps = 0;
    int xdps = imgSrc->droppedFrames();
    fpsMutex.unlock();
    emit fpsUpdated(xfps + xdps);
    emit dpsUpdated(xdps);
}
