#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QThread>
#include <QtGlobal>
#include <QDateTime>
#include <QAtomicInt>

#include <cv.h>
#include <highgui.h>

#include "module.h"
#include "imagesource.h"

using namespace cv;

/*!
 \brief Object of this class is used for getting frames from input and processing it with provided modules.

Works in different thread.
Use chModList() and stopChModList() when changing module list.
*/
class ImageProcessor : public QThread
{
    Q_OBJECT
public:
    /*!
     \brief Constructor.

     \param fileName of the file to be opened.
     \param parent QObject parent.
    */
    ImageProcessor(ImageSource *imgSrc, QObject *parent = 0);

    /*!
     \brief Constructor.

     \param fileName name of the file to be opened.
     \param modules list of pointer to modules which should be used during processing.
     \param parent QObject parent.
    */
    ImageProcessor(ImageSource *imgSrc, QList<Module*> *modules, QObject *parent = 0);

    /*!
     \brief Cleans.
    */
    virtual ~ImageProcessor();


    /*!
     \brief Processing loop.
     Reads frame by frame from input and process it by each filter from the list.
    */
    void run();

    /*!
      \brief Sets module list. Should be thread safe.
    */
    void setModuleList(QList<Module*> *modules) { mut.lock(); this->modules = modules; mut.unlock(); }

    /**
     * @brief Used to count FPS.
     *
     * Timer is started by new thread.
     * @param e event
    */
    void timerEvent(QTimerEvent *e);


public slots:
    /*!
      \brief Stops thread and joins. After this method thread is dead for sure.
    */
    void stop() { this->running = false; QThread::wait();}

private:
    VideoCapture *capture; /*!< Pointer to capture device. */
    int interval; /*!< Frame reading interval to mantain proper framerate. */
    bool running; /*!< If thread is running. */
    QList<Module*> *modules; /*!< Pointer to module list. */
    QMutex mut; /*!< Mutex securing module list. */    
    QMutex fpsMutex; /**< Mutex controlling access to fps and dps. */
    int fps; /**< Fps counter */
    ImageSource *imgSrc;

    /*!
     \brief Inits whole class.

     Opens the file through OpenCV VideoCapture class.
     Registers all the modules.
     \param imgSrc image source class
     \param modules
    */
    void init(ImageSource *imgSrc, QList<Module*> *modules);

private slots:
    /**
     * @brief Counts frames and emits fpsUpdated() and dpsUpdates() signals.
    */
    void countFps();

signals:
    /**
     * @brief Signal emmited when fps value is updated.
     * @param x current fps value.
    */
    void fpsUpdated(int x);

    /**
     * @brief Signal emmited when dps(dropped frames per second) value is updated.
     * @param x current dps value.
    */
    void dpsUpdated(int x);


};

#endif // IMAGEPROCESSOR_H
