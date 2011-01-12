#include "modulemanagerwidget.h"
#include "ui_modulemanagerwidget.h"

ModuleManagerWidget::ModuleManagerWidget(QWidget *videoWidget, QWidget *parent) :
    QWidget(parent), ui(new Ui::ModuleManagerWidget), videoWidget((VideoGallery*)videoWidget)
{
    ui->setupUi(this);
    imgSrc = NULL;

    processor = NULL;
    modules = new QList<Module*>();

    ModuleVideo *mVideo = new ModuleVideo(this);
    ModuleBackground *mBackground = new ModuleBackground(this);
    ModuleFilters *mFilters = new ModuleFilters(this);
    ModuleTracking *mTracking = new ModuleTracking(this);

    modules->append(mVideo);
    modules->append(mBackground);
    modules->append(mFilters);
    modules->append(mTracking);

    ui->inVideoTab->setLayout(new QVBoxLayout());
    ui->inVideoTab->layout()->addWidget(mVideo->getSettingsWidget());
    ui->bgRemovalTab->setLayout(new QVBoxLayout());
    ui->bgRemovalTab->layout()->addWidget(mBackground->getSettingsWidget());
    ui->filtersTab->setLayout(new QVBoxLayout());
    ui->filtersTab->layout()->addWidget(mFilters->getSettingsWidget());
    ui->trackingTab->setLayout(new QVBoxLayout());
    ui->trackingTab->layout()->addWidget(mTracking->getSettingsWidget());

    VideoGallery *vg = (VideoGallery*)videoWidget;
    vg->registerNewWidget(mVideo->getVideoWidget());
    vg->registerNewWidget(mBackground->getVideoWidget());
    vg->registerNewWidget(mFilters->getVideoWidget());
    vg->registerNewWidget(mTracking->getVideoWidget());

    connect(mVideo, SIGNAL(videoStopped(QWidget*)), videoWidget, SLOT(unRegisterWidget(QWidget*)));
    connect(mBackground, SIGNAL(videoStopped(QWidget*)), videoWidget, SLOT(unRegisterWidget(QWidget*)));
    connect(mFilters, SIGNAL(videoStopped(QWidget*)), videoWidget, SLOT(unRegisterWidget(QWidget*)));
    connect(mTracking, SIGNAL(videoStopped(QWidget*)), videoWidget, SLOT(unRegisterWidget(QWidget*)));
}

void ModuleManagerWidget::openFile(QString fileName)
{
    on_stopButton_clicked();
    if(imgSrc)
    {
        delete imgSrc;
        imgSrc = NULL;
    }
    try
    {
        this->imgSrc = new FileImageSource(fileName);
        ui->startButton->setEnabled(true);
    }
    catch (...)
    {
        ui->startButton->setEnabled(false);
        QMessageBox::critical(this, tr("Error opening video."), tr("Unable to open this file."), QMessageBox::Ok);
    }
}

void ModuleManagerWidget::openCameraDevice(int i)
{
    on_stopButton_clicked();
    if(imgSrc)
    {
        delete imgSrc;
        imgSrc = NULL;
    }
    try
    {
        this->imgSrc = new CameraImageSource(i);
        ui->startButton->setEnabled(true);
    }
    catch (...)
    {
        ui->startButton->setEnabled(false);
        QMessageBox::critical(this, tr("Error opening video."), tr("Unable to open this device."), QMessageBox::Ok);
    }
}

ModuleManagerWidget::~ModuleManagerWidget()
{    

    if(processor)
    {
        processor->stop();
        delete processor;
    }
    if(imgSrc)
    {
        delete imgSrc;
    }

    foreach(Module *m, *modules)
    {
        delete m;
    }

    delete ui;
}

void ModuleManagerWidget::on_startButton_clicked()
{
    if(!imgSrc)
    {
        QMessageBox::information(this, tr("No file opened."), tr("No video source has been opened."), QMessageBox::Ok);
        return;
    }

    if(!processor) {
        processor = new ImageProcessor(imgSrc, modules, this);
        processor->setModuleList(modules);
        connect(processor, SIGNAL(fpsUpdated(int)), this, SLOT(showFps(int)));
        connect(processor, SIGNAL(dpsUpdated(int)), this, SLOT(showDps(int)));
    }

    if(!processor->isRunning()) {
        processor->start();
    }
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
}

void ModuleManagerWidget::on_stopButton_clicked()
{
    if(processor && processor->isRunning()){
        processor->stop();
        disconnect(processor, SIGNAL(fpsUpdated(int)));
        disconnect(processor, SIGNAL(dpsUpdated(int)));
        delete processor;
        processor = NULL;
    }
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void ModuleManagerWidget::showFps(int x)
{
    ui->fpsLabel->setText(QString::number(x));
}

void ModuleManagerWidget::showDps(int x)
{
    ui->dpsLabel->setText(QString::number(x));
}
