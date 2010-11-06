#ifndef MODULETRACKING_H
#define MODULETRACKING_H
#include "module.h"
#include "moduletrackingsettings.h"
#include "touch.h"
#include "tracker.h"

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
    int minBlob;
    int maxBlob;


private:
    ModuleTrackingSettings* settings;
    void filterContours(vector<vector<Point> > &contours, vector<vector<Point> >& filtered);
    void drawMiddles(Mat& mat, QVector<Touch*>* touches);
    Tracker tracker;

signals:
    void thresholdChanged(int);
    void minBlobChanged(int);
    void maxBlobChanged(int);

public slots:
    void setThreshold(int);
    void setMinBlob(int);
    void setMaxBlob(int);

};

#endif // MODULETRACKING_H
