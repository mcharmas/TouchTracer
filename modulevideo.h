#ifndef MODULEVIDEO_H
#define MODULEVIDEO_H
#include "module.h"
#include <cv.h>
#include <highgui.h>
#include <QLabel>

using namespace cv;

class ModuleVideo : public Module
{
    Q_OBJECT
public:
    explicit ModuleVideo(QObject *parent = 0);
    ~ModuleVideo();
    void process(Mat &mat);
    QWidget* getSettingsWidget() { return NULL; }
    QString getName() { return "ModuleVideo"; }

};

#endif // MODULEVIDEO_H
