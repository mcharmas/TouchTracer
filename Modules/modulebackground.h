#ifndef MODULEBACKGROUND_H
#define MODULEBACKGROUND_H

#include <cv.h>

#include "module.h"
#include "modulebackgroundsettings.h"

using namespace cv;

class ModuleBackground : public Module
{
    Q_OBJECT

public:
    explicit ModuleBackground(QObject *parent = 0);
    ~ModuleBackground();
    void process(Mat &mat);
    QWidget* getSettingsWidget() { return settings; }
    QString getName() { return "Background removal"; }

public slots:
    void storeFrame();

private:
    bool frameToStore;
    Mat storedFrame;
    ModuleBackgroundSettings *settings;

signals:
    void frameStored(QImage);

};

#endif // MODULEBACKGROUND_H
