#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->managerWidget->setLayout(new QVBoxLayout());

    manager = new ModuleManagerWidget(ui->videosContainer);
    ui->managerWidget->layout()->addWidget(manager);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "~", tr("Video Files (*.avi)"));
    if(fileName!="")
    {
        manager->openFile(fileName);
    }
}
