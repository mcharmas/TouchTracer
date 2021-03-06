#ifndef MODULEVIDEOSETTIGNS_H
#define MODULEVIDEOSETTIGNS_H

#include <QWidget>
#include "abstractsettingswidget.h"

namespace Ui {
    class ModuleVideoSettigns;
}

/*!
 \brief Class implementing empty settings to dummy ModuleVideo.
*/
class ModuleVideoSettigns : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    /*!
     \brief Setups UI on getSettingsWidget() widget.
     \param moduleName name of module - used to store settings
     \param parent
    */
    explicit ModuleVideoSettigns(QString moduleName, QWidget *parent = 0);

    /*!
     \brief Clean up.
    */
    virtual ~ModuleVideoSettigns();      

private:
    Ui::ModuleVideoSettigns *ui; /*!< UI */

};

#endif // MODULEVIDEOSETTIGNS_H
