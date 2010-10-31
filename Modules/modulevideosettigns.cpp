#include "modulevideosettigns.h"
#include "ui_modulevideosettigns.h"

ModuleVideoSettigns::ModuleVideoSettigns(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ModuleVideoSettigns)
{
    ui->setupUi(getSettingsWidget());
}

ModuleVideoSettigns::~ModuleVideoSettigns()
{
    delete ui;
}
