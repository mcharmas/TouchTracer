#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QFrame>

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
     \param bool true - selected / false not
    */
    void setSelected(bool);

public slots:
    /*!
     \brief Used to get over frame to display.
     \param frame
    */
    void showFrame(const QImage&);

private:
    Ui::VideoWidget *ui; /*!< UI */
    bool sizeSet;

};

#endif // VIDEOWIDGET_H
