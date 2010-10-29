#include "modulebackgroundsettings.h"
#include "ui_modulebackgroundsettings.h"

ModuleBackgroundSettings::ModuleBackgroundSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModuleBackgroundSettings)
{
    ui->setupUi(this);
}

ModuleBackgroundSettings::~ModuleBackgroundSettings()
{
    delete ui;
}
