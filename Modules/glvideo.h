#ifndef GLVIDEO_H
#define GLVIDEO_H

#include <QtOpenGL/qgl.h>
using namespace QGL;

class GLVideo : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLVideo(QWidget *parent = 0);
    void paintGL();
    void resizeGL(int w, int h);

    void setImage(const QImage & img);

private:
    QImage img, glImg;
    bool hasImage;

signals:

public slots:

};

#endif // GLVIDEO_H
