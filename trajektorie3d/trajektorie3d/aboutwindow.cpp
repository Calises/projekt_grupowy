#include "aboutwindow.h"
#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    LGPLlicenseFile = new QFile(":/licenses/LGPL");
    MITlicenseFile = new QFile(":/licenses/MIT");

    connect(ui->qtPushButton, &QPushButton::clicked,
            this, &AboutWindow::showLgplLicense);
    connect(ui->ogrePushButton, &QPushButton::clicked,
            this, &AboutWindow::showMitLicense);

    showLgplLicense();
}

void AboutWindow::showLgplLicense()
{
    if(LGPLlicenseFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString licenseText = LGPLlicenseFile->readAll();
        ui->licensesTextBrowser->setText(licenseText);

        LGPLlicenseFile->close();
    }
}

void AboutWindow::showMitLicense()
{
    if(MITlicenseFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString licenseText = MITlicenseFile->readAll();
        ui->licensesTextBrowser->setText(licenseText);

        MITlicenseFile->close();
    }
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
