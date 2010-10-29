#ifndef MODULEVIDEOSETTIGNS_H
#define MODULEVIDEOSETTIGNS_H

#include <QWidget>
#include "abstractsettingswidget.h"

namespace Ui {
    class ModuleVideoSettigns;
}

class ModuleVideoSettigns : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    explicit ModuleVideoSettigns(QWidget *parent = 0);
    ~ModuleVideoSettigns();

protected:
    QWidget* getConreteWidget() { return this; }

private:
    Ui::ModuleVideoSettigns *ui;
};

#endif // MODULEVIDEOSETTIGNS_H
