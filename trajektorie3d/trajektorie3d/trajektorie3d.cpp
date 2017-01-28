#include "trajektorie3d.h"

trajektorie3d::trajektorie3d(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::trajektorie3dClass)
{
    ui->setupUi(this);

	OgreWidget* ogreWidget = new OgreWidget(this);
	ogreWidget->setFixedWidth(640);
	ogreWidget->setFixedHeight(480);

	ui->centralLayout->addWidget(ogreWidget, 0, 0, 1, 1);
}

trajektorie3d::~trajektorie3d()
{

}