#ifndef MODULEFILTERS_H
#define MODULEFILTERS_H
#include "module.h"
#include "modulefilterssettings.h"
#include <cv.h>
#include <highgui.h>
#include <QObject>

using namespace cv;

class ModuleFilters : public Module
{
    Q_OBJECT
public:
    explicit ModuleFilters(QObject *parent = 0);
    ~ModuleFilters();

    void process(Mat &mat);

    QWidget* getSettingsWidget() { return settings; }

    QString getName() { return "Filters module"; }

public slots:
    void changeBlur(int);
    void changeGain(int);


private:
    ModuleFiltersSettings *settings;
    int blurValue;
    double gain;

};

#endif // MODULEFILTERS_H
