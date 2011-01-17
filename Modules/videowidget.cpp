#include "videowidget.h"
#include "ui_videowidget.h"

VideoWidget::VideoWidget(QString caption, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VideoWidget)
{    
    ui->setupUi(this);
    ui->caption->setText(caption);
    QAction *saveAction = new QAction("Save Image", this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveImageAction()));
    this->addAction(saveAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

VideoWidget::~VideoWidget()
{
    delete ui;
}

void VideoWidget::saveImageAction()
{
    QString result = QFileDialog::getSaveFileName(this, "Save Image", "~", tr("Image Files (*.png *.jpg *.bmp)"));
    if(result != "")
    {
        ui->video->getImage().save(result);
    }
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

void VideoWidget::setSelected(bool)
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
