#ifndef VIDEOGALLERY_H
#define VIDEOGALLERY_H

#include <QWidget>
#include <QGridLayout>

/*!
 \brief Class used to display videowidgets in grid layout.

*/
class VideoGallery : public QWidget
{
    Q_OBJECT
public:
    /*!
     \brief Constructor

     \param parent QWidget parent
    */
    explicit VideoGallery(QWidget *parent = 0);

signals:

public slots:
    /*!
     \brief Registers new VideoWidget and displays it on the layout.

     \param pointer to widget
    */
    void registerNewWidget(QWidget*);

    /*!
     \brief Removes widget from gallery.

     \param pointer to widget to remove
    */
    void unRegisterWidget(QWidget*);

private:
    int columns; /*!< number of columns*/
    int x; /*!< number of widgets */
};

#endif // VIDEOGALLERY_H
