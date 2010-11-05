#ifndef MODULETRACKING_H
#define MODULETRACKING_H
#include "module.h"

#include <cv.h>
#include <highgui.h>
#include <QObject>

class ModuleTracking : public Module
{
    Q_OBJECT
public:
    explicit ModuleTracking(QObject *parent = 0);

    QWidget* getSettingsWidget() { return NULL; }
    QString getName() { return "Tracking"; };

protected:
    void process(cv::Mat &mat);


signals:

public slots:

};

#endif // MODULETRACKING_H
