#include "abstractsettingswidget.h"
#include "ui_abstractsettingswidget.h"

QSettings* AbstractSettingsWidget::storedSettings = 0;

AbstractSettingsWidget::AbstractSettingsWidget(QString moduleName, QWidget *parent) :
    QWidget(parent),PROP_VIDEO("showVideo"),
    baseUi(new Ui::AbstractSettingsWidget)
{
    this->moduleName = moduleName;
    baseUi->setupUi(this);
    videoCheckBox = baseUi->videoCheckBox;
    videoCheckBox->setChecked(getProperty(PROP_VIDEO, false).toBool());
    connect(baseUi->videoCheckBox, SIGNAL(toggled(bool)), this, SLOT(toggleVideo(bool)));
}

AbstractSettingsWidget::~AbstractSettingsWidget()
{
    delete baseUi;
}

void AbstractSettingsWidget::toggleVideo(bool b)
{
    storeProperty(PROP_VIDEO, b);
    emit showVideoChanged(b);
}

QWidget* AbstractSettingsWidget::getSettingsWidget()
{
    return baseUi->settingsWidget;
}

QSettings& AbstractSettingsWidget::getStoredSettings()
{
    if(!AbstractSettingsWidget::storedSettings)
        AbstractSettingsWidget::storedSettings = new QSettings();

    return *storedSettings;
}

void AbstractSettingsWidget::storeProperty(const QString prop, QVariant v)
{
    QString n = getSettingName(prop);
    getStoredSettings().setValue(n, v);
}

QVariant AbstractSettingsWidget::getProperty(const QString prop, QVariant v)
{
    QString n = getSettingName(prop);
    return getStoredSettings().value(n, v);
}
