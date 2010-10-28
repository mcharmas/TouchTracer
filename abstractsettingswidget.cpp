#include "abstractsettingswidget.h"
#include "ui_abstractsettingswidget.h"

AbstractSettingsWidget::AbstractSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractSettingsWidget)
{
    ui->setupUi(this);
    new QVBoxLayout(ui->settingsWidget);
    connect(ui->videoCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleVideo(bool)));
}

AbstractSettingsWidget::~AbstractSettingsWidget()
{
    delete ui;
}

void AbstractSettingsWidget::toggleVideo(bool b)
{
    emit showVideoChanged(b);
}
