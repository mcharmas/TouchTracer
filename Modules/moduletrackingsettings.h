#ifndef MODULETRACKINGSETTINGS_H
#define MODULETRACKINGSETTINGS_H
#include "abstractsettingswidget.h"

#include <QSlider>
#include <QWidget>

namespace Ui {
    class ModuleTrackingSettings;
}

class ModuleTrackingSettings : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit ModuleTrackingSettings(QWidget *parent = 0);
    ~ModuleTrackingSettings();

    QSlider* thresholdSlider;
private:
    Ui::ModuleTrackingSettings *ui;
};

#endif // MODULETRACKINGSETTINGS_H
