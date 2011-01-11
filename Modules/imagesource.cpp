#include "imagesource.h"

FileImageSource::FileImageSource(QString fileName, QObject *parent) : ImageSource(parent), fileName(fileName)
{
    capture = new VideoCapture(fileName.toStdString());
    if(!capture->isOpened()) {
        throw new Exception();
    }
    frameGettingTime = 0;
    interval = (int)(1000000 / (capture->get(CV_CAP_PROP_FPS) + 1) );

}

FileImageSource::~FileImageSource()
{
    if(capture && capture->isOpened())
    {
        capture->release();
        delete capture;
    }
}

void FileImageSource::getFrame(Mat &mat)
{
    long p = getProcessingTime()*1000 + frameGettingTime*1000;
    if(p > interval)
    {
        qint64 start = QDateTime::currentMSecsSinceEpoch();
        Mat m;
        int framesToDrop = p / interval;
        for(int i = 0; i<framesToDrop; i++)
        {
            retriveFrame(m);
        }
        dropped += framesToDrop;
        p = p % interval - (QDateTime::currentMSecsSinceEpoch() - start)*1000;
    }
    this->usleep(interval-p);
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    retriveFrame(mat);
    frameGettingTime = QDateTime::currentMSecsSinceEpoch() - start;
}

int FileImageSource::droppedFrames()
{
    int x = dropped;
    dropped = 0;
    return x;
}


void FileImageSource::retriveFrame(Mat &mat)
{
    if(!capture->grab() || !capture->retrieve(mat))
    {
        capture->release();
        delete capture;
        capture = new VideoCapture(fileName.toStdString());
        capture->grab();
        capture->retrieve(mat);
    }
}
