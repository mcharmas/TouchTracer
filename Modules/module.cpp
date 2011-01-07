#include "module.h"

Module::Module(QObject *parent):QObject(parent),locked(false)
{
}

void Module::init()
{
    videoWidget = new VideoWidget(getName());
    if(getSettingsWidget())
    {
        connect(getSettingsWidget(), SIGNAL(showVideoChanged(bool)), this, SLOT(setVideo(bool)));
        setVideo(getSettingsWidget()->videoCheckBox->isChecked());
    }
}

Module::~Module()
{
    emit videoStopped(getVideoWidget());
    // this is probably removed by QT when exiting the application
    //setVideo(false);
    //delete videoWidget;
}

bool Module::processImage(cv::Mat &mat)
{
    if(isSettingsLocked()) {
        return false;
    }
    process(mat);

    if(displayVideo) {
        cv::Mat m;
        cv::resize(mat, m, cv::Size(), 0.5, 0.5);
        QImage img = matToQImage(m);
        emit frameReady(img);
    }
    return true;
}


QImage Module::matToQImage(const cv::Mat& mat) const
{
    if(mat.channels()==1)
    {
        cv::Mat m;
        cv::cvtColor(mat, m, CV_GRAY2RGB);
        QImage img(m.data, m.size().width, m.size().height, m.step, QImage::Format_RGB888);
        return img.copy(0,0,img.width(),img.height());
    }
    else
    {
        QImage img(mat.data, mat.size().width, mat.size().height, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
}

void Module::setVideo(bool b) {
    if(b)
    {
        if(!displayVideo)
        {
            connect(this, SIGNAL(frameReady(QImage)), videoWidget, SLOT(showFrame(QImage)), Qt::QueuedConnection);
            displayVideo=true;
        }
    }
    else
    {
        if(displayVideo)
        {
            disconnect(this, SIGNAL(frameReady(QImage)), videoWidget, SLOT(showFrame(QImage)));
            displayVideo=false;
            videoWidget->stopVideo();
        }
    }
}

