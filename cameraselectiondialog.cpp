#include "cameraselectiondialog.h"
#include "ui_cameraselectiondialog.h"

CameraSelectionDialog::CameraSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraSelectionDialog)
{
    ui->setupUi(this);
}

CameraSelectionDialog::~CameraSelectionDialog()
{
    delete ui;
}

int CameraSelectionDialog::getSelectedDevice()
{
    return ui->deviceBox->value();
}
