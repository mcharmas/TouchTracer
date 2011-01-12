#ifndef IMAGESOURCE_H
#define IMAGESOURCE_H

#include <QObject>
#include <QThread>
#include <QDateTime>
#include <QDebug>
#include <cv.h>
#include <highgui.h>
#include "Modules/touch.h"

using namespace cv;

/**
 * @brief Abstract class used as image source.
*/
class ImageSource : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     * @param parent QObject parent
    */
    ImageSource(QObject *parent = 0):QObject(parent),processingTime(0)
    {
        capture = NULL;
    }

    /**
     * @brief Function used to obtain a frame in proper time.
     *
     * Blocking function which computes frame releasing time to obtain proper framerate.
     * @param mat frame from image source
    */
    virtual void getFrame(Mat &mat) = 0;

    /**
     * @brief Sets procesing time which is taken into consideration when calculating frame releasing time.
     * @param time in miliseconds (how long frame processing took).
    */
    void setProcessingTime(long time) { this->processingTime = time; }

    /**
     * @brief Dropped frames counter.
     *
     * Value of dropped frames is reseted after calling this function.
     * To obtain amount of dropped frames per second call it once during a second.
     * @return int number of dropped frames
    */
    virtual int droppedFrames() = 0;

protected:
    /**
     * @brief Returns processing time previously set by calling setProcessingTime().
     * @return long processing time
    */
    long getProcessingTime() { return this->processingTime; }

    /**
     * @brief Updates frame size in Touch class.
    */
    void updateFrameSize()
    {
        if(capture && capture->isOpened())
        {
            int w = capture->get(CV_CAP_PROP_FRAME_WIDTH);
            int h = capture->get(CV_CAP_PROP_FRAME_HEIGHT);
            Touch::setFrameSize(w,h);
        }
    }

    VideoCapture *capture; /**< capture */

private:
    long processingTime; /**<  frame processing time used during time calculations */


};

/**
 * @brief Class used to obtain video from file.
*/
class FileImageSource : public ImageSource, QThread
{
public:
    /**
     * @brief Constructs.
     *
     * @param fileName of a video to be opened.
     * @param parent QObject parent
    */
    FileImageSource(QString fileName, QObject *parent = 0);

    /**
     * @brief Clean up.
    */
    ~FileImageSource();

    /**
     * @brief Blocking function returning frame by frame from video file in proper time.
     * @param mat obtained frame.
    */
    void getFrame(Mat &mat);

    /**
     * @brief Dropped frames counter.
     * @return int number of dropped frames.
    */
    int droppedFrames();

protected:
    /**
     * @brief Immediately retrives frame from file.
     * @param mat retrivet frame.
    */
    void retriveFrame(Mat &mat);

private:
    QString fileName; /**< Name of file to read. */
    int interval; /**< interval counted using movie FPS property */
    int dropped; /**< amount of dropped frames */
    long frameGettingTime; /**< frame getting time */

};

/**
 * @brief Class used as image source getting frames from camera device.
*/
class CameraImageSource : public ImageSource
{
public:
    /**
     * @brief Constructs object.
     * @param device number of device (X in /dev/videoX)
     * @param parent QObject parent
    */
    CameraImageSource(int device, QObject *parent=0);

    /**
     * @brief Clean up.
    */
    ~CameraImageSource();

    /**
     * @brief Gets frame by frame from camera device.
     * @param mat read frame
    */
    void getFrame(Mat &mat);

    /**
     * @brief Amount of dropped frames - NOT SUPPORTED
     * @return int dropped frames
    */
    int droppedFrames();

};

#endif // IMAGESOURCE_H
