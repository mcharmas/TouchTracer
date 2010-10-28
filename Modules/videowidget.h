#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QFrame>

namespace Ui {
    class VideoWidget;
}

class VideoWidget : public QFrame
{
    Q_OBJECT

public:
     VideoWidget(QString caption, QWidget *parent = 0);
    ~VideoWidget();

    void stopVideo();
    void setSelected(bool);

public slots:
    void showFrame(const QImage&);

private:
    Ui::VideoWidget *ui;

};

#endif // VIDEOWIDGET_H
