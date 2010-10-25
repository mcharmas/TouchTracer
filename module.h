#ifndef MODULE_H
#define MODULE_H
#include <cv.h>
#include <QString>
#include <QMutex>
#include <QWidget>
#include <QObject>
#include <QLabel>

class Module : public QObject
{
    Q_OBJECT
public:
    Module(QObject *parent = 0):QObject(parent),locked(false){ videoWidget = new QLabel(); }
    ~Module() { delete videoWidget; }

    bool processImage(cv::Mat &mat)
    {
        if(isSettingsLocked()) {
            return false;
        }
        process(mat);

        if(displayVideo) {
            QImage img = matToQImage(mat);
            emit frameReady(img);
        }
        return true;
    }

    virtual QString getName()=0;
    virtual QWidget* getSettingsWidget()=0;

    QWidget* getVideoWidget() { return videoWidget; }

    void setVideo(bool);

signals:
    void frameReady(const QImage &);

private:
    QImage matToQImage(const cv::Mat& mat) const;

    QLabel* videoWidget;
    bool locked;
    bool isSettingsLocked() { return locked; }
    bool displayVideo;
    QMutex mutex;

private slots:
    void showFrame(const QImage &);

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

};

#endif // MODULE_H
