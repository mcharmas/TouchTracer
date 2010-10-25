#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageprocessor.h"
#include "modulevideo.h"
#include <cv.h>
#include <highgui.h>
#include "videowidget.h"

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
    ImageProcessor *processor;
    ModuleVideo *video;

private slots:
    void on_startButton_clicked();

};

#endif // MAINWINDOW_H
