#ifndef MODULETRACKING_H
#define MODULETRACKING_H
#include "module.h"
#include "moduletrackingsettings.h"
#include "touch.h"
#include "tracker.h"

#include <cv.h>
#include <highgui.h>
#include <QObject>
#include <vector>

using namespace std;
using namespace cv;

/**
 * @brief Module which performs finder tracking.
*/
class ModuleTracking : public Module
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     * @param parent QObject parent
    */
    explicit ModuleTracking(QObject *parent = 0);
    /**
     * @brief Clena up.
    */
    ~ModuleTracking();

    QWidget* getSettingsWidget() { return settings; }
    QString getName() { return "Tracking"; };

protected:
    /**
     * @brief Processes current frame.
     *
     * How is it done:
     * - if image is not monochromatic yet - converts it
     * - performs thresholding according to thres variable value (adjustable in ModuleTrackingSettings)
     * - searches for contours
     * - filters contours using filterContours() method
     * - pushes current touches to Tracker object
     * - draws filtered contours on thresholded image
     * @param mat frame to be processed
    */
    void process(cv::Mat &mat);

    /**
     * @brief Method used to filter found contours.
     *
     * Method goes through each contour (vector<Point>) from contours parameter,
     * creates Touch object to count size
     * and adds proper contours (vector<Point>) to filtered parameter.
     * Method check contours size to be between minBlob size and maxBlob size.
     * @param contours
     * @param filtered
    */
    void filterContours(vector<vector<Point> > &contours, vector<vector<Point> >& filtered);

    int thres; /**< Threshold value. */
    int minBlob; /**< Minimal blob size. */
    int maxBlob; /**< Maximum blob size. */

private:
    ModuleTrackingSettings* settings; /**< Settings widget. */
    Tracker tracker; /**< Tracker object. */

signals:
    /**
     * @brief Emmited when threshold value changed to update settings GUI.
     * @param x
    */
    void thresholdChanged(int x);

    /**
     * @brief Emmited when min blob size value changed to update settings GUI.
     * @param x
    */
    void minBlobChanged(int x);

    /**
     * @brief Emmited when max blob size value changed to update settings GUI.
     * @param x
    */
    void maxBlobChanged(int x);

public slots:
    /**
     * @brief Sets threshold value (used in process() method).
     * @param x threshold <0 ; 255>
    */
    void setThreshold(int x);

    /**
     * @brief Sets minimal blob size value (probably in pixels).
     * @param x minimal blob size value (in pixels).
    */
    void setMinBlob(int x);

    /**
     * @brief Set maximum blob size value (probably in pixels).
     * @param x maximum blob size value (in pixels).
    */
    void setMaxBlob(int x);

};

#endif // MODULETRACKING_H
