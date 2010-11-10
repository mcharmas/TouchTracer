#ifndef MODULEFILTERSSETTINGS_H
#define MODULEFILTERSSETTINGS_H

#include <QWidget>
#include <QSlider>
#include "abstractsettingswidget.h"

namespace Ui {
    class ModuleFiltersSettings;
}

/**
 * @brief Filetering module settings widget.
 *
 * For now it has 2 sliders representing gain and blur values (see ModuleFilters).
 * For convenience both widgets are exported as public to connect them in ModuleFilter constructor.
 * @class ModuleFiltersSettings modulefilterssettings.h "Modules/modulefilterssettings.h"
*/
class ModuleFiltersSettings : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent QWidget parent.
    */
    explicit ModuleFiltersSettings(QWidget *parent = 0);

    /**
     * @brief Clean up.
    */
    ~ModuleFiltersSettings();
    QSlider* gainSlider; /**< Gain slider. */
    QSlider* blurSlider; /**< Blur slider. */

private:
    Ui::ModuleFiltersSettings *ui; /**< UI */

};

#endif // MODULEFILTERSSETTINGS_H
