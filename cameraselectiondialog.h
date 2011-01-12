#ifndef CAMERASELECTIONDIALOG_H
#define CAMERASELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
    class CameraSelectionDialog;
}

/**
 * @brief Dialog used to as a user what camera device to use.
*/
class CameraSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs.
     *
     * @param parent
    */
    explicit CameraSelectionDialog(QWidget *parent = 0);

    /**
     * @brief Clean up.
     *
    */
    ~CameraSelectionDialog();

    /**
     * @brief Returns selected device by user.
     * @return int
    */
    int getSelectedDevice();

private:
    Ui::CameraSelectionDialog *ui; /**< UI */
};

#endif // CAMERASELECTIONDIALOG_H
