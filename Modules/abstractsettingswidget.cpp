#include "abstractsettingswidget.h"
#include "ui_abstractsettingswidget.h"

AbstractSettingsWidget::AbstractSettingsWidget(QWidget *parent) :
    QWidget(parent),
    baseUi(new Ui::AbstractSettingsWidget)
{
    baseUi->setupUi(this);
    connect(baseUi->videoCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleVideo(bool)));
//    if(getConreteSettings())
//        ui->settingsWidget->layout()->addWidget(getConreteSettings());
}

AbstractSettingsWidget::~AbstractSettingsWidget()
{
    delete baseUi;
}

void AbstractSettingsWidget::toggleVideo(bool b)
{
    emit showVideoChanged(b);
}

QWidget* AbstractSettingsWidget::getSettingsWidget()
{
    return baseUi->settingsWidget;
}
