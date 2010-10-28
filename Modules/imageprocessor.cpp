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
    capture = new VideoCapture(fileName.toStdString());
    if(!capture->isOpened()) {
        throw new Exception();
    }

    interval = (int)(1000000 / (capture->get(CV_CAP_PROP_FPS)));
    setModuleList(modules);
    running = true;
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
    while(running) {
        Mat frame;
        *capture >> frame;
        //TODO: dodac liczenie czasu i odejmowac od intervala
        mut.lock();
        if(modules != NULL) {
           foreach(Module *m, *modules){
               m->processImage(frame);
           }
        }
        mut.unlock();

        this->usleep(interval);
    }
}



