#include "imageprocessor.h"

ImageProcessor::ImageProcessor(cv::VideoCapture* cap, QObject *parent) :
    QThread(parent), QList<Module*>(), capture(cap)
{
    if(!cap->isOpened()) {
        throw new Exception();
    }

    interval = (int)(1000000 / (cap->get(CV_CAP_PROP_FPS)));
    running = true;
}

ImageProcessor::~ImageProcessor()
{
    if(this->isRunning()) {
       this->stop();
    }

    foreach(Module *m, (QList<Module*>)*this){
        delete m;
    }
}

void ImageProcessor::run()
{
    while(running) {
        Mat frame;
        *capture >> frame;
        //TODO: dodac liczenie czasu i odejmowac od intervala

        foreach(Module *m, (QList<Module*>)*this){
            m->processImage(frame);
        }

        this->usleep(interval);
    }
}

void ImageProcessor::addModule(Module *m)
{
    this->append(m);
}

void ImageProcessor::addModule(Module *m, int pos)
{
    this->insert(pos, m);
}

void ImageProcessor::removeModule(Module *m)
{
    this->removeOne(m);
}


