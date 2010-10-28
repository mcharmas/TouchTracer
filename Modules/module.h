#ifndef MODULE_H
#define MODULE_H
#include <cv.h>
#include <QString>
#include <QMutex>
#include <QWidget>
#include <QObject>
#include <QLabel>

#include "videowidget.h"

class Module : public QObject
{
    Q_OBJECT
public:
    Module(QObject *parent = 0);
    ~Module();

    bool processImage(cv::Mat &mat);

    QWidget* getVideoWidget() { return videoWidget; }

    virtual QString getName() { return ""; }
    virtual QWidget* getSettingsWidget()=0;

public slots:
    void setVideo(bool);

signals:
    void frameReady(const QImage &);
    void videoStopped(QWidget*);

private:
    QImage matToQImage(const cv::Mat& mat) const;

    VideoWidget* videoWidget;
    bool locked;
    bool isSettingsLocked() { return locked; }
    bool displayVideo;
    QMutex mutex;

protected:
    /**
      Uzyc tego przed edycja ustawien.
      **/
    void settingsLock() { mutex.lock(); locked = true; }

    /**
      Uzyc tego do oblokowania ustawien.
      **/
    void settingsUnlock() { mutex.unlock(); locked = false; }

    virtual void process(cv::Mat &mat)=0;

    void init();
};

#endif // MODULE_H
