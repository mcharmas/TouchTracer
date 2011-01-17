#include "modulebackgroundsettings.h"
#include "ui_modulebackgroundsettings.h"

ModuleBackgroundSettings::ModuleBackgroundSettings(QWidget *parent) :
    AbstractSettingsWidget("ModuleBackground", parent),
    ui(new Ui::ModuleBackgroundSettings)
{
    ui->setupUi(getSettingsWidget());    
    connect(ui->storeButton, SIGNAL(clicked()), this, SLOT(on_storeButton_clicked()));
    connect(ui->saveBackground, SIGNAL(clicked()), this, SLOT(on_saveBackground_clicked()));
}

ModuleBackgroundSettings::~ModuleBackgroundSettings()
{
    delete ui;
}

void ModuleBackgroundSettings::on_storeButton_clicked()
{
    emit storeFrameButtonClicked();
}

void ModuleBackgroundSettings::showStoredBackground(QImage img)
{
    img = img.scaled(ui->frameLabel->size(),Qt::KeepAspectRatio);
    ui->frameLabel->setPixmap(QPixmap::fromImage(img));
}

void ModuleBackgroundSettings::on_saveBackground_clicked()
{
    emit saveFrameButtonClicked();
}
