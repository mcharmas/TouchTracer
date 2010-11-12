#ifndef ABSTRACTSETTINGSWIDGET_H
#define ABSTRACTSETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
    class AbstractSettingsWidget;
}

/*!
 \brief Abstract widget used to create settings widget.

 Provides one setting common for all modules: showVideo - shows video in VideoGallery
 after processing it by module.
*/
class AbstractSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     \brief Constructs.
     \param parent QWidget parent
    */
    explicit AbstractSettingsWidget(QWidget *parent = 0);

    /*!
     \brief Cleans up.
    */
    virtual ~AbstractSettingsWidget();

protected:
    /*!
     \brief Returns settings widget in which subclasses can show other settings.

     \return QWidget * empty widget placed below showVideo setting.
    */
    QWidget* getSettingsWidget();

private:
    Ui::AbstractSettingsWidget *baseUi; /*!< UI */


private slots:
    /*!
     \brief Turns on / off video by emmiting showVideoChanged().
     \param b true - on / false = off
    */
    void toggleVideo(bool b);

signals:
    /*!
     \brief Signal used to notify module that showVideo property has changed.

     Sholud be connected in constructor of new module.
     \param b indicates if property has changed
    */
    void showVideoChanged(bool b);
};

#endif // ABSTRACTSETTINGSWIDGET_H
