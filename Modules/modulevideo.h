#ifndef MODULEVIDEO_H
#define MODULEVIDEO_H
#include "module.h"
#include "modulevideosettigns.h"
#include <cv.h>
#include <highgui.h>
#include <QLabel>

using namespace cv;

/*!
 \brief Class implementing dumm Module.

 Does absolutly nothing with frame except showing it.
 Only for debugging purposes and probably will be deleted in later stage of development.
 Shows very basic implementation of module.
*/
class ModuleVideo : public Module
{
    Q_OBJECT
public:
    /*!
     \brief Constructor showing how to create new module.

     Calls init method which create VideoWidget for this module.
     Creates SettingsWidget.
     Connects AbstractSettingsWidget::showVideoChanged(bool) to Module::setVideo(bool) slot.
     \param parent
    */

    explicit ModuleVideo(QObject *parent = 0);
    /*!
     \brief Cleans up.
    */
    virtual ~ModuleVideo();

    /*!
     \brief Implemented abstract process method.

     Does nothing.
     \param mat frame to process.
    */
    void process(Mat &mat);

    /*!
     \brief Implemented method.

     Returns settings widget.
     \return pointer to settings widget.
    */
    AbstractSettingsWidget* getSettingsWidget() { return settings; }

    /*!
     \brief Implemented method. Returns module name.

     \return module name (shown in module list in  ModuleManagerWidget).
    */
    QString getName() { return "ModuleVideo"; }

    /**
     * @brief Toggles video on/off.
     * @param b
    */
    void toggleVideoSetting(bool b);

private:
    ModuleVideoSettigns *settings; /*!< Settings. */

};

#endif // MODULEVIDEO_H
