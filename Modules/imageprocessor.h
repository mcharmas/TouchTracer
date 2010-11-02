#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QThread>
#include <QtGlobal>
#include <QDateTime>
#include <QTimer>
#include <QAtomicInt>

#include <cv.h>
#include <highgui.h>

#include "module.h"

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

     \param QString name of the file to be opened.
     \param parent QObject parent.
    */
    ImageProcessor(QString, QObject *parent = 0);

    /*!
     \brief Constructor.

     \param QString name of the file to be opened.
     \param modules list of pointer to modules which should be used during processing.
     \param parent QObject parent.
    */
    ImageProcessor(QString, QList<Module*> *modules, QObject *parent = 0);

    /*!
     \brief Cleans.
    */
    ~ImageProcessor();


    /*!
     \brief Processing loop.
     Reads frame by frame from input and process it by each filter from the list.
    */
    void run();

    /*!
      \brief Sets module list. Should be thread safe.
    */
    void setModuleList(QList<Module*> *modules) { mut.lock(); this->modules = modules; mut.unlock(); }

    /*!
      \brief Should be called before modules list is changed outside the thread.
    */
    void chModList() { mut.lock(); }

    /*!
      \brief Should be called after changing of module list to unlock processing
    */
    void stopChModList() { mut.unlock(); }


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
    QString fileName;
    QTimer timer;

    QMutex fpsMutex;
    int fps;


    /*!
     \brief Inits whole class.

     Opens the file through OpenCV VideoCapture class.
     Registers all the modules.
     \param fileName
     \param modules
    */
    void init(QString fileName, QList<Module*> *modules);

private slots:
    void countFps();

signals:
    void fpsUpdated(int);


};

#endif // IMAGEPROCESSOR_H
