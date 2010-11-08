#include "videowidget.h"
#include "ui_videowidget.h"

VideoWidget::VideoWidget(QString caption, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VideoWidget),
    sizeSet(false)
{    
    ui->setupUi(this);
    ui->caption->setText(caption);
}

VideoWidget::~VideoWidget()
{
    delete ui;
}

void VideoWidget::showFrame(const QImage &img)
{
/*    if(!sizeSet)
    {
        ui->video->setMaximumSize(img.width(),img.height());
        sizeSet = true;
    }
    ui->video->setPixmap(QPixmap::fromImage(img));*/
    ui->video->setImage(img);
}

void VideoWidget::stopVideo()
{
    //ui->video->setText("No Video");
}

void VideoWidget::setSelected(bool b)
{
/*    if(b) {
        this->setFrameShadow(QFrame::Sunken);
    }
    else {
        this->setFrameShadow(QFrame::Raised);
    }*/
    //ui->video->updateGL();

//    hide();
//    show();
    //update();
}
