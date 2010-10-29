#include "modulebackgroundsettings.h"
#include "ui_modulebackgroundsettings.h"

ModuleBackgroundSettings::ModuleBackgroundSettings(QWidget *parent) :
    AbstractSettingsWidget(parent),
    ui(new Ui::ModuleBackgroundSettings)
{
    ui->setupUi(getSettingsWidget());
    connect(ui->storeButton, SIGNAL(clicked()), this, SLOT(on_storeButton_clicked()));
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
    img = img.scaled(this->size(),Qt::KeepAspectRatio);
    ui->frameLabel->setPixmap(QPixmap::fromImage(img));
}
