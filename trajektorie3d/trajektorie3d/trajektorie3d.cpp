#include "trajektorie3d.h"
#include "utils.h"

trajektorie3d::trajektorie3d(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::trajektorie3dClass)
{
    ui->setupUi(this);

	connect(ui->chooseMapButton, &QPushButton::clicked,
			this, &trajektorie3d::chooseMapClicked);

    connect(ui->turnLeftButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Left); });
    connect(ui->turnRightButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Right); });
    connect(ui->turnUpButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Up); });
    connect(ui->turnDownButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Down); });

	ogreWidget = new OgreWidget(this);
	ogreWidget->setFixedWidth(640);
	ogreWidget->setFixedHeight(480);

	ui->centralLayout->addWidget(ogreWidget, 0, 0, 1, 1);
}

trajektorie3d::~trajektorie3d()
{
}

void trajektorie3d::chooseMapClicked()
{
	ogreWidget->redrawScene();
}