#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new QVBoxLayout(ui->videosContainer);

    cv::VideoCapture* capture = new VideoCapture("/media/disk/Downloads/Dexter.S05E03.HDTV.XviD-2HD/dexter.s05e03.hdtv.xvid-2hd.avi");
    processor = new ImageProcessor(capture);
    video = new ModuleVideo(this);
    processor->addModule(video);
    ui->videosContainer->layout()->addWidget(video->getVideoWidget());
    video->setVideo(true);

}

MainWindow::~MainWindow()
{
    delete processor;
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    processor->start();
}
