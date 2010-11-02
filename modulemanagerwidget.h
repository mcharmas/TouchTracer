#ifndef MODULEMANAGERWIDGET_H
#define MODULEMANAGERWIDGET_H

#include <QWidget>
#include <QStringListModel>
#include <QDebug>
#include "videogallery.h"
#include "Modules/imageprocessor.h"
#include "Modules/modulevideo.h"
#include "Modules/modulebackground.h"

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
    ~ModuleManagerWidget();

private:
    /*!
     \brief Updates list of loaded modules in QListView.
    */
    void updateList();

    Ui::ModuleManagerWidget *ui; /*!< UI */
    VideoGallery* videoWidget; /*!< pointer to video widget */
    ImageProcessor *processor; /*!< pointer to image processor thread */
    QStringList possibleModules; /*!< list of possible modules (shown in modulesBox) */
    QList<Module*> *modules; /*!< list of modules passed to processor */
    QString fileName; /*!< name of videoFile */
    QWidget *currentSettingsWidget; /*!< Pointer to currently displayed settings widget */
    Module *selectedModule; /*!< pointer to currently selected modules */

private slots:
    /*!
     \brief Method called after removeButton click.
    */
    void on_removeModuleButton_clicked();

    /*!
     \brief Method called afted addButton click.
    */
    void on_addModuleButton_clicked();

    /*!
     \brief Stops processing thread and sets processor = NULL;
    */
    void on_stopButton_clicked();

    /*!
     \brief Creates new processor, sets module list and starts thread.
    */
    void on_startButton_clicked();

    /*!
     \brief Shows settings of selected module.
     \param QItemSelection
     \param QItemSelection
    */
    void showSettings(QItemSelection,QItemSelection);

    void showFps(int);

};

#endif // MODULEMANAGERWIDGET_H
