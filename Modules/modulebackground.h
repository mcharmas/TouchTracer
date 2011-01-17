#ifndef MODULEBACKGROUND_H
#define MODULEBACKGROUND_H

#include <cv.h>
#include <highgui.h>

#include "module.h"
#include "modulebackgroundsettings.h"
#include <QDebug>
#include <QFileDialog>
using namespace cv;

/*!
 \brief Class implementing background removal module.

 Processing method from this class converts frame to gray scale and than substracts frame
 marked as background from current video frame.
*/
class ModuleBackground : public Module
{
    Q_OBJECT

public:
    /*!
     \brief Creates module object.
     \param parent
    */
    explicit ModuleBackground(QObject *parent = 0);

    /*!
     \brief Cleans up.
    */
    virtual ~ModuleBackground();

    /*!
     \brief Processing method.

     Converts frame to grayscale.
     Checks if got a request to save frame as background and saves.
     For every frame substracts background of current frame calling substractBackground() method.
     \param mat processed frame
    */
    void process(Mat &mat);

    /*!
     \brief Look to Module documentation.
    */
    AbstractSettingsWidget* getSettingsWidget() { return settings; }

    /*!
     \brief Look to Module documentation.
    */
    QString getName() { return "Background removal"; }

public slots:
    /*!
     \brief Slot which handles request from settings widget and make process method to store frame as background.
    */
    void storeFrame();

    /*!
     \brief To save bg image.
    */
    void saveFrame();

private:
    bool frameToStore; /*!< if process method have to store new background */
    Mat storedFrame; /*!< backgorund frame */
    ModuleBackgroundSettings *settings; /*!< Settings widget */

signals:
    /*!
     \brief Signal used to notify settings widget that background have been stored.

     \param img background QImage
    */
    void frameStored(QImage img);

};

#endif // MODULEBACKGROUND_H
