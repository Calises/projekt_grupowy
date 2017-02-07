#ifndef DIMENSIONSDIALOG_H
#define DIMENSIONSDIALOG_H

#include <QDialog>

namespace Ui {
class DimensionsDialog;
}

class DimensionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DimensionsDialog(QWidget *parent = 0);
    ~DimensionsDialog();

    int getX();
    int getY();
    int getZ();

private:
    Ui::DimensionsDialog *ui;
};

#endif // DIMENSIONSDIALOG_H
