#include "videogallery.h"

VideoGallery::VideoGallery(QWidget *parent) :
    QWidget(parent)
{
    new QGridLayout(this);
    columns = 2;
    x = 0;
}

void VideoGallery::registerNewWidget(QWidget *w)
{
    QGridLayout* layout = (QGridLayout*)this->layout();
    int i = x/columns;
    int j = x%columns;
    layout->addWidget(w, i, j);
    x++;
}

void VideoGallery::unRegisterWidget(QWidget *w)
{
    x--;
    layout()->removeWidget(w);
}
