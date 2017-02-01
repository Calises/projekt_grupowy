#include "trajektorie3d.h"
#include <QCoreApplication>
#include "Map.h"
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

    QObject::connect(ui->button_start, SIGNAL(clicked()), this, SLOT(startAlgorithm()));

	ogreWidget = new OgreWidget(this);
	ogreWidget->setFixedWidth(640);
	ogreWidget->setFixedHeight(480);

	ui->centralLayout->addWidget(ogreWidget, 0, 0, 1, 1);

    // tworzenie przykladowej mapy
    int n = 10;
    int m = 10;
    map = new Map(n, m);
    map->setStart(1, 1);
    map->setStop(9, 9);
    map->setObstacle(1, 0);
    map->setObstacle(5, 2);
    map->setObstacle(5, 3);
    map->setObstacle(5, 4);
    map->setObstacle(5, 5);
}

trajektorie3d::~trajektorie3d()
{
}

void trajektorie3d::chooseMapClicked()
{
    ogreWidget->redrawScene(map);
}

void trajektorie3d::startAlgorithm()
{
    if (!map)
        return;

	// change the text
	ui->button_start->setText("GO");

	std::cout << "Hej! ";

	QString a = QString::number(map->returnValue(1, 1));
	ui->label_numOperations->setText(a);

	map->show();
}