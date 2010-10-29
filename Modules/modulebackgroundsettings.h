#ifndef MODULEBACKGROUNDSETTINGS_H
#define MODULEBACKGROUNDSETTINGS_H

#include <QWidget>

namespace Ui {
    class ModuleBackgroundSettings;
}

class ModuleBackgroundSettings : public QWidget
{
    Q_OBJECT

public:
    explicit ModuleBackgroundSettings(QWidget *parent = 0);
    ~ModuleBackgroundSettings();

private:
    Ui::ModuleBackgroundSettings *ui;
};

#endif // MODULEBACKGROUNDSETTINGS_H
