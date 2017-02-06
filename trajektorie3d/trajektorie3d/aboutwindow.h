#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QFile>

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutWindow(QWidget *parent = 0);
    ~AboutWindow();

private:
    Ui::AboutWindow *ui;

    QFile* MITlicenseFile;
    QFile* LGPLlicenseFile;

    void showMitLicense();
    void showLgplLicense();
};

#endif // ABOUTWINDOW_H
