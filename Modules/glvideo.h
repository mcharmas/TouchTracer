#ifndef GLVIDEO_H
#define GLVIDEO_H

#include <QtOpenGL/qgl.h>
#include <QDebug>
using namespace QGL;

/**
 * @brief Class used to display video frames.
 *
 * Draws each frame using OpenGL.
 * @class GLVideo glvideo.h "Modules/glvideo.h"
*/
class GLVideo : public QGLWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor.
     *
     * @param parent QWidget parent
    */
    explicit GLVideo(QWidget *parent = 0);

    /**
     * @brief Paints frame on OpenGL Viewport.
     *
    */
    void paintGL();

    /**
     * @brief Resizes the widget.
     *
     * @param w widht
     * @param h height
    */
    void resizeGL(int w, int h);

    /**
     * @brief Sets new frame to display.
     *
     * Should be called to display each frame.
     * Resizes widget to the size of the first frame.
     * @param img Image to be drawn.
    */
    void setImage(const QImage & img);

    /**
     * @brief Returns displayed image.
     * @return QImage displayed image.
    */
    QImage getImage()
    {
        return img;
    }


private:
    QImage img, glImg; /**< Images */
    bool hasImage; /**< If had imagebefore. Used to check if resizing needed. */

};

#endif // GLVIDEO_H
