#ifndef MODULEBACKGROUNDSETTINGS_H
#define MODULEBACKGROUNDSETTINGS_H

#include <QWidget>

#include "abstractsettingswidget.h"

namespace Ui {
    class ModuleBackgroundSettings;
}

/*!
 \brief Class implementing settings widget for ModuleBackground.
*/
class ModuleBackgroundSettings : public AbstractSettingsWidget
{
    Q_OBJECT

public:
    /*!
     \brief Creates widget.
     \param parent
    */
    explicit ModuleBackgroundSettings(QWidget *parent = 0);

    /*!
     \brief Destroys widget.
    */
    ~ModuleBackgroundSettings();

public slots:
    /*!
     \brief Slot used to show stored background by ModuleBackground.

     Shows background image on label on settings widget.
     \param QImage shown image
    */
    void showStoredBackground(QImage);

private:
    Ui::ModuleBackgroundSettings *ui; /*!< UI */

private slots:
    /*!
     \brief Emits storeFrameButtonClicked().
    */
    void on_storeButton_clicked();

signals:
    /*!
     \brief Signal used to notify ModuleBackground that user requested to save background frame.
    */
    void storeFrameButtonClicked();

};

#endif // MODULEBACKGROUNDSETTINGS_H