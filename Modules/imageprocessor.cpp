#include "imageprocessor.h"

ImageProcessor::ImageProcessor(QString fileName, QObject *parent) :
    QThread(parent)
{
    init(fileName, NULL);
}

ImageProcessor::ImageProcessor(QString fileName, QList<Module *> * modules, QObject *parent)
    :     QThread(parent)
{
    init(fileName, modules);
}

void ImageProcessor::init(QString fileName, QList<Module *> *modules)
{
    this->fileName = fileName;
    capture = new VideoCapture(fileName.toStdString());
    if(!capture->isOpened()) {
        throw new Exception();
    }

    qDebug() << capture->get(CV_CAP_PROP_FPS);
    interval = (int)(1000000 / (capture->get(CV_CAP_PROP_FPS) + 1) );
    setModuleList(modules);
    running = true;
    this->timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(countFps()));
    fps = 30;
}

ImageProcessor::~ImageProcessor()
{
    if(this->isRunning()) {
       this->stop();
    }
    delete capture;

}

void ImageProcessor::run()
{
    bool skipFrame = false;
    qint64 timeToWait = 0;
    timer.start();

    while(running) {
        while(capture->grab() && running)
        {
            qint64 start = QDateTime::currentMSecsSinceEpoch();

            fpsMutex.lock();
            fps++;
            fpsMutex.unlock();

            Mat frame;
            if(!capture->retrieve(frame))
                break;

            if(skipFrame) {
                int x = timeToWait - interval;
                if(x > 0) {
                    skipFrame = true;
                    timeToWait = x;
                } else {
                    skipFrame = false;
                    this->usleep(interval - timeToWait);
                }
                continue;
            }

            mut.lock();
            if(modules != NULL) {
                foreach(Module *m, *modules){
                    m->processImage(frame);
                }
            }
            mut.unlock();

            qint64 duration = QDateTime::currentMSecsSinceEpoch() - start;

            if((interval - duration*1000) < 0)
            {
                skipFrame = true;
                timeToWait = duration*1000 - interval;
            }
            else
            {
                this->usleep(interval - duration*1000);
            }
        }

        capture->release();
        delete capture;
        capture = new VideoCapture(fileName.toStdString());
    }
}


void ImageProcessor::countFps()
{
    fpsMutex.lock();
    int xfps = fps;
    fps = 0;
    fpsMutex.unlock();
    emit fpsUpdated(xfps);
}
