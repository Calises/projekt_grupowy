#include "dimensionsdialog.h"
#include "ui_dimensionsdialog.h"

DimensionsDialog::DimensionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DimensionsDialog)
{
    ui->setupUi(this);
}

DimensionsDialog::~DimensionsDialog()
{
    delete ui;
}


int DimensionsDialog::getX()
{
    return ui->xSpinBox->value();
}

int DimensionsDialog::getY()
{
    return ui->ySpinBox->value();
}

int DimensionsDialog::getZ()
{
    return ui->zSpinBox->value();
}

