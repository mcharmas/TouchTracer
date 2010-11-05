#ifndef MODULETRACKING_H
#define MODULETRACKING_H
#include "module.h"
#include "moduletrackingsettings.h"

#include <cv.h>
#include <highgui.h>
#include <QObject>
#include <vector>

using namespace std;
using namespace cv;

class ModuleTracking : public Module
{
    Q_OBJECT
public:
    explicit ModuleTracking(QObject *parent = 0);
    ~ModuleTracking();

    QWidget* getSettingsWidget() { return settings; }
    QString getName() { return "Tracking"; };

protected:
    void process(cv::Mat &mat);
    int thres;


private:
    ModuleTrackingSettings* settings;

signals:

public slots:
    void setThreshold(int);

};

#endif // MODULETRACKING_H
