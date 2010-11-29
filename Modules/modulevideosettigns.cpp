#include "modulevideosettigns.h"
#include "ui_modulevideosettigns.h"

ModuleVideoSettigns::ModuleVideoSettigns(QString moduleName, QWidget *parent) :
    AbstractSettingsWidget(moduleName, parent),
    ui(new Ui::ModuleVideoSettigns)
{
    ui->setupUi(getSettingsWidget());
}

ModuleVideoSettigns::~ModuleVideoSettigns()
{
    delete ui;
}
