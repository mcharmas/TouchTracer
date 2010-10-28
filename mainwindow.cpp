#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new QHBoxLayout(ui->managerWidget);

    manager = new ModuleManagerWidget(ui->videosContainer, ui->managerWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
