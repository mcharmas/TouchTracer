#ifndef MODULE_H
#define MODULE_H
#include <cv.h>
#include <highgui.h>
#include <QString>
#include <QMutex>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QDebug>

#include "videowidget.h"

/*!
 \brief Base class for all modules.

 Important methods to override are:
 process(), getName(), getSettingsWidget()

 Modules are sstored in list. When processing every frame process() method is called.
 First method called in Constructor should be init() to create proper VideoWidget.
*/
class Module : public QObject
{
    Q_OBJECT
public:

    /*!
     \brief Constructor.
     Does nothing except setting QObject parent.
     \param parent
    */
    Module(QObject *parent = 0);

    /*!
     \brief Removes all stuff.
    */
    virtual ~Module();


    /*!
     \brief Method called by ImageProcessor in order to process frame.
     It is a wrapper to process method which check if settings are not locked (mutex because of thread).

     If settings are locked it returns false in order to ommit this frame.
     \param mat frame to process
     \return bool false if settings are locked, true if frame was properly processed
    */
    bool processImage(cv::Mat &mat);

    /*!
      \brief Getter for VideoWidget of module.

      \return videoWidget ready to show video after processing frame.
    */
    QWidget* getVideoWidget() { return videoWidget; }

    /*!
      \brief Should be overriten in order to get proper module name on VideoWidget.

      \return Name of module.
    */
    virtual QString getName() { return ""; }
    /*!
     \brief Should be overriten and provide module configuration interface.

     \return QWidget * with module configuration interface.
    */
    virtual QWidget* getSettingsWidget()=0;

public slots:
    /*!
     \brief Turns on/off video on VideoWidget.

     \param b true - on / false - off
    */
    void setVideo(bool b);

signals:
    /*!
     \brief Emited when frame has been processed and is ready to be shown.

     \param img reference to frame to be shown.
    */
    void frameReady(const QImage& img);

    /*!
     \brief Emited when Module is removed from the list in order to unregister it from VideoGallery.

     \param w Pointer to VideoWidget.
    */
    void videoStopped(QWidget* w);

private:
    VideoWidget* videoWidget; /*!< Pointer to VideoWidget */
    bool locked; /*!< State of settings. */
    bool displayVideo; /*!< If videoPlaying is on */
    QMutex mutex; /*!< Mutex locking module settings. */

    /*!
      \brief Check if settings are locked.
      \return if settings are locked.
    */
    bool isSettingsLocked() { return locked; }

protected:
    /*!
     \brief Converts BGR cv::Mat to QImage in order to display it on VideoWidget.

     \param mat cv::Mat to be converted.
     \return QImage corresponding QImage
    */
    QImage matToQImage(const cv::Mat& mat) const;

    /*!
      Should be used before settings change.
    */
    void settingsLock() { mutex.lock(); locked = true; }

    /*!
      Should be used to unlock processing after settings change.
     */
    void settingsUnlock() { mutex.unlock(); locked = false; }

    /*!
     \brief Module processing method.
     The most important method. Should be overriten to provide frame processing.
     \param mat cv::Mat to process
    */
    virtual void process(cv::Mat &mat)=0;

    /*!
     \brief This method creates proper VideoWidget.
     Should be called in subclass Constructor!
    */
    void init();
};

#endif // MODULE_H
