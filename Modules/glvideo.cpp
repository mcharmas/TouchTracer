#include "glvideo.h"

GLVideo::GLVideo(QWidget *parent) :
    QGLWidget(parent)
{
    hasImage = false;
    //resize(QSize(400,300));
}

void GLVideo::paintGL()
{
    if(hasImage)
    {
        glDrawPixels(glImg.width(), glImg.height(), GL_RGBA, GL_UNSIGNED_BYTE, glImg.bits());
    }
}

void GLVideo::resizeGL(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w,0,h,-1,1);
    glMatrixMode (GL_MODELVIEW);
}

void GLVideo::setImage(const QImage & img)
{
    this->img = img;
    glImg = QGLWidget::convertToGLFormat(img);
    glImg = glImg.scaled(this->size(), Qt::KeepAspectRatio);
    if(!hasImage)
    {
        hasImage=true;
        //resize(img.size());
    }
    updateGL();
}
