#ifndef MODULEMANAGERWIDGET_H
#define MODULEMANAGERWIDGET_H

#include <QWidget>
#include <QStringListModel>
#include <QDebug>
#include <QMessageBox>
#include "videogallery.h"
#include "Modules/imageprocessor.h"
#include "Modules/modulevideo.h"
#include "Modules/modulebackground.h"
#include "Modules/modulefilters.h"
#include "Modules/moduletracking.h"
#include "Modules/imagesource.h"

namespace Ui {
    class ModuleManagerWidget;
}

/*!
 \brief Widget providing module management and settings.

*/
class ModuleManagerWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     \brief Constructor.

     \param videoWidget pointer to VideoWidget (to show effect of modules)
     \param parent QWidget parent
    */
    ModuleManagerWidget(QWidget* videoWidget, QWidget *parent = 0);

    /*!
     \brief Clean up.
    */
    virtual ~ModuleManagerWidget();

    /**
     * @brief Opens video file.
     *
     * Stops currently processing thread (if any) and sets the name.
     * New thread is created and started by on_start_button_clicked().
     * @param fileName
    */
    void openFile(QString fileName);


    void openCameraDevice(int i);

private:
    /*!
     \brief Updates list of loaded modules in QListView.
    */
    void updateList();

    Ui::ModuleManagerWidget *ui; /*!< UI */
    VideoGallery* videoWidget; /*!< pointer to video widget */
    ImageProcessor *processor; /*!< pointer to image processor thread */
    QList<Module*> *modules; /*!< list of modules passed to processor */
    ImageSource *imgSrc;

private slots:
    /*!
     \brief Stops processing thread and sets processor = NULL;
    */
    void on_stopButton_clicked();

    /*!
     \brief Creates new processor, sets module list and starts thread.
    */
    void on_startButton_clicked();

    /**
     * @brief Shows FPS in GUI.
     * Used by ImageProcessor to notify about current framerate.
     * @param x current framerate to display
    */
    void showFps(int x);

    /**
     * @brief Shows DPS in GUI.
     * Used by ImageProcessor to notify about current dropped frames.
     * @param x current dropped frames to display
    */
    void showDps(int x);

};

#endif // MODULEMANAGERWIDGET_H
