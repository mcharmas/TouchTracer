#ifndef MODULEVIDEO_H
#define MODULEVIDEO_H
#include "module.h"
#include "modulevideosettigns.h"
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
    QWidget* getSettingsWidget() { return settings; }
    QString getName() { return "ModuleVideo"; }

private:
    ModuleVideoSettigns *settings;

};

#endif // MODULEVIDEO_H
