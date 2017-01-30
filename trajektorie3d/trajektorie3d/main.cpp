#include "trajektorie3d.h"
#include "ui_trajektorie3d.h"
#include <QtWidgets/QApplication>
#include <QVBoxLayout>
#include <QtWidgets/QGroupBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    trajektorie3d window;

    window.setWindowTitle("Trajektorie 3D");

    window.show();
    return a.exec();
}
