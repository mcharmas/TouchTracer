#ifndef MODULETRACKINGSETTINGS_H
#define MODULETRACKINGSETTINGS_H
#include "abstractsettingswidget.h"
#include "calibrationwidget.h"

#include <QSlider>
#include <QWidget>
#include <QDebug>

namespace Ui {
    class ModuleTrackingSettings;
}

/**
 * @brief Class providing settings for ModuleTracking.
 *
 * Export 3 sliders as public members to easily connect them in ModuleTracking.
 * Provides labels for displaying settings values.
*/
class ModuleTrackingSettings : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     * @param parent QWidget parent
    */
    explicit ModuleTrackingSettings(QWidget *parent = 0);

    /**
     * @brief Clean up;
    */
    virtual ~ModuleTrackingSettings();

    QSlider* thresholdSlider; /**< Threshold slider. */
    QSlider* minBlobSizeSlider; /**< Minimum blob size slider. */
    QSlider* maxBlobSizeSlider; /**< Maximum blob size slider. */
    QSlider* movementFilterSlider; /**< Movement filter value slider */

public slots:
    /**
     * @brief Displays threshold value on label.
     * @param x
    */
    void setThresholdInfo(int x);

    /**
     * @brief Displays min blob size value on label.
     * @param x
    */
    void setMinBlobInfo(int x);

    /**
     * @brief Displays max blob size value on label.
     * @param x
    */
    void setMaxBlobInfo(int x);

    /**
     * @brief Displays movement filter value.
     * @param x
    */
    void setMovementInfo(int x);

private:
    Ui::ModuleTrackingSettings *ui; /**< Settings. */
    const QString PROP_THRESH;
    const QString PROP_MINBLOB;
    const QString PROP_MAXBLOB;
    const QString PROP_MOV;

private slots:
    void openCalibration();

};

#endif // MODULETRACKINGSETTINGS_H
