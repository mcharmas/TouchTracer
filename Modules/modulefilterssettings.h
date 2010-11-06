#ifndef MODULEFILTERSSETTINGS_H
#define MODULEFILTERSSETTINGS_H

#include <QWidget>
#include "abstractsettingswidget.h"

namespace Ui {
    class ModuleFiltersSettings;
}

class ModuleFiltersSettings : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit ModuleFiltersSettings(QWidget *parent = 0);
    ~ModuleFiltersSettings();

signals:
    void blurValueChanged(int);

private:
    Ui::ModuleFiltersSettings *ui;

public slots:
    void changeBlurValue(int);
};

#endif // MODULEFILTERSSETTINGS_H