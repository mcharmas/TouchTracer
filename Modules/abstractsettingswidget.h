#ifndef ABSTRACTSETTINGSWIDGET_H
#define ABSTRACTSETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSettings>
#include <QCheckBox>

namespace Ui {
    class AbstractSettingsWidget;
}

/*!
 \brief Abstract widget used to create settings widget.

 Provides one setting common for all modules: showVideo - shows video in VideoGallery
 after processing it by module.
*/
class AbstractSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs object.
     *
     * @param moduleName name of module (used for storing settings in proper section).
     * @param parent QObject parent
    */
    explicit AbstractSettingsWidget(QString moduleName, QWidget *parent = 0);

    /*!
     \brief Cleans up.
    */
    virtual ~AbstractSettingsWidget();

    QCheckBox* videoCheckBox; /**< Check box used for enabling video. */

protected:
    /*!
     \brief Returns settings widget in which subclasses can show other settings.

     \return QWidget * empty widget placed below showVideo setting.
    */
    QWidget* getSettingsWidget();

    const QString PROP_VIDEO; /**< Constant property used for storing settings. */

    /**
     * @brief Stores property in config file.
     *
     * Stores property in config file in the section responsible for each module.
     * @param prop key
     * @param v value
    */
    void storeProperty(const QString prop, QVariant v);


    /**
     * @brief Reads property from config file.
     *
     * @param prop key
     * @param v default value
     * @return QVariant value from cfg file or default value when not asvailable
    */
    QVariant getProperty(const QString prop, QVariant v);

    /**
     * @brief Returns module name.
     *
     * @return module name
    */
    QString getModuleName() {return moduleName;}

private:
    Ui::AbstractSettingsWidget *baseUi; /*!< UI */
    static QSettings* storedSettings;
    QString moduleName;

    static QSettings& getStoredSettings();
    QString getSettingName(QString name) { return getModuleName()+"/"+name; }

private slots:
    /*!
     \brief Turns on / off video by emmiting showVideoChanged() and saves showVideo property.
     \param b true - on / false = off
    */
    void toggleVideo(bool b);

signals:
    /*!
     \brief Signal used to notify module that showVideo property has changed.

     Sholud be connected in constructor of new module.
     \param b indicates if property has changed
    */
    void showVideoChanged(bool b);    
};

#endif // ABSTRACTSETTINGSWIDGET_H
