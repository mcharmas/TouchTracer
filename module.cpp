#include "module.h"

QImage Module::matToQImage(const cv::Mat& mat) const
{
    QImage img(mat.data, mat.size().width, mat.size().height, mat.step,QImage::Format_RGB888);
    return img.rgbSwapped();
}

void Module::showFrame(const QImage & img)
{
    if (this->videoWidget)
    {
        QPixmap pix = QPixmap::fromImage(img);
        videoWidget->setPixmap(pix);
    }
}

void Module::setVideo(bool b) {
    if(b)
    {
        if(!displayVideo)
        {
            connect(this, SIGNAL(frameReady(QImage)), this, SLOT(showFrame(QImage)), Qt::QueuedConnection);
            displayVideo=true;
            emit videoEmited(getVideoWidget());
        }
    }
    else
    {
        if(displayVideo)
        {
            disconnect(this, SIGNAL(frameReady(QImage)), this, SLOT(showFrame(QImage)));
            displayVideo=false;
            emit videoStopped(getVideoWidget());
        }
    }
}

