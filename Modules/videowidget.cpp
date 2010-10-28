#include "videowidget.h"
#include "ui_videowidget.h"

VideoWidget::VideoWidget(QString caption, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VideoWidget)
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
    ui->video->setPixmap(QPixmap::fromImage(img));
}

void VideoWidget::stopVideo()
{
    ui->video->setText("No Video");
}

void VideoWidget::setSelected(bool b)
{
    if(b) {
        this->setFrameShadow(QFrame::Sunken);
    }
    else {
        this->setFrameShadow(QFrame::Raised);
    }

    hide();
    show();
    //update();
}
