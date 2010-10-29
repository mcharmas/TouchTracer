#ifndef ABSTRACTSETTINGSWIDGET_H
#define ABSTRACTSETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
    class AbstractSettingsWidget;
}

class AbstractSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractSettingsWidget(QWidget *parent = 0);
    ~AbstractSettingsWidget();

protected:
    QWidget* getSettingsWidget();

private:
    Ui::AbstractSettingsWidget *baseUi;


private slots:
    void toggleVideo(bool);

signals:
    void showVideoChanged(bool);
};

#endif // ABSTRACTSETTINGSWIDGET_H
