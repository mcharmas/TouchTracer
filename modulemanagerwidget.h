#ifndef MODULEMANAGERWIDGET_H
#define MODULEMANAGERWIDGET_H

#include <QWidget>
#include <QStringListModel>
#include <QDebug>
#include "videogallery.h"
#include "imageprocessor.h"
#include "modulevideo.h"

namespace Ui {
    class ModuleManagerWidget;
}

class ModuleManagerWidget : public QWidget
{
    Q_OBJECT

public:
    ModuleManagerWidget(QWidget* videoWidget, QWidget *parent = 0);
    ~ModuleManagerWidget();

private:
    Ui::ModuleManagerWidget *ui;
    VideoGallery* videoWidget;
    ImageProcessor *processor;
    QStringList possibleModules;
    QList<Module*> *modules;
    cv::VideoCapture *capture;
    QString fileName;
    void updateList();


private slots:
    void on_removeModuleButton_clicked();
    void on_addModuleButton_clicked();
    void on_stopButton_clicked();
    void on_startButton_clicked();
};

#endif // MODULEMANAGERWIDGET_H
