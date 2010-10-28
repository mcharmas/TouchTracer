#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cv.h>
#include <highgui.h>
#include "imageprocessor.h"
#include "modulemanagerwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ModuleManagerWidget *manager;


private slots:


};

#endif // MAINWINDOW_H
