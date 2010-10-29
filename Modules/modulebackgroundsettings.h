#ifndef MODULEBACKGROUNDSETTINGS_H
#define MODULEBACKGROUNDSETTINGS_H

#include <QWidget>

#include "abstractsettingswidget.h"

namespace Ui {
    class ModuleBackgroundSettings;
}

class ModuleBackgroundSettings : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit ModuleBackgroundSettings(QWidget *parent = 0);
    ~ModuleBackgroundSettings();

public slots:
    void showStoredBackground(QImage);

private:
    Ui::ModuleBackgroundSettings *ui;

private slots:
    void on_storeButton_clicked();

signals:
    void storeFrameButtonClicked();

};

#endif // MODULEBACKGROUNDSETTINGS_H
