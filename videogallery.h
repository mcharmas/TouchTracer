#ifndef VIDEOGALLERY_H
#define VIDEOGALLERY_H

#include <QWidget>
#include <QGridLayout>

class VideoGallery : public QWidget
{
    Q_OBJECT
public:
    explicit VideoGallery(QWidget *parent = 0);

signals:

public slots:
    void registerNewWidget(QWidget*);
    void unRegisterWidget(QWidget*);

private:
    int columns;
    int rows;
    int x;
};

#endif // VIDEOGALLERY_H
