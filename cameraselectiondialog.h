#ifndef CAMERASELECTIONDIALOG_H
#define CAMERASELECTIONDIALOG_H

#include <QDialog>

namespace Ui {
    class CameraSelectionDialog;
}

class CameraSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSelectionDialog(QWidget *parent = 0);
    ~CameraSelectionDialog();
    int getSelectedDevice();

private:
    Ui::CameraSelectionDialog *ui;
};

#endif // CAMERASELECTIONDIALOG_H
