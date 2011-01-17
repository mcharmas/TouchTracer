#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QFrame>
#include <QFileDialog>

namespace Ui {
    class VideoWidget;
}

/*!
 \brief Class used for displaying video.

 For now it consists of two labels.
 One for displaying caption with module name and one displaying pixmap with video frame.
*/
class VideoWidget : public QFrame
{
    Q_OBJECT

public:
     /*!
      \brief Constructor.

      Creates object with caption.
      \param caption caption should contain module name.
      \param parent QWidget parent.
     */
     VideoWidget(QString caption, QWidget *parent = 0);

     /*!
     \brief cleans after itself.
    */
    ~VideoWidget();

    /*!
     \brief Shows information on video label that video has been stopped.
    */
    void stopVideo();

    /*!
     \brief Changes look of widget to notify user that it is selected.

     Not working right now due to problems with QGLWidget displaying video.
     \param b true - selected / false not
    */
    void setSelected(bool b);

public slots:
    /*!
     \brief Used to get over frame to display.
     \param frame image to be displayed.
    */
    void showFrame(const QImage& frame);

    /**
     * @brief Saves displayed image.
     *
    */
    void saveImageAction();

private:
    Ui::VideoWidget *ui; /*!< UI */

};

#endif // VIDEOWIDGET_H
