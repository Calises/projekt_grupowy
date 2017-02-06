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

    //OgreWidget* ogreWidget = new OgreWidget(&window);
    //ogreWidget->setFixedWidth(640);
    //ogreWidget->setFixedHeight(480);

    //window.ui.centralLayout->addWidget(ogreWidget, 0, 0, 1, 1);
	
    window.show();
    return a.exec();
}
