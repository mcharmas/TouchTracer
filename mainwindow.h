#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <cv.h>
#include <highgui.h>
#include "Modules/imageprocessor.h"
#include "modulemanagerwidget.h"

namespace Ui {
    class MainWindow;
}

/*!
 \brief MainWindow class.

 Does nothing except showing GUI components (VideoGallery and ModuleManagerWidget).
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     \brief Constructs.
     \param parent
    */
    explicit MainWindow(QWidget *parent = 0);

    /*!
     \brief Destroys.
    */
    virtual ~MainWindow();

private:
    Ui::MainWindow *ui; /*!< UI */
    ModuleManagerWidget *manager; /*!< Pointer to module manager widget. */


private slots:
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
