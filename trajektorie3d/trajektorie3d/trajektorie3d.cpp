#include "trajektorie3d.h"
#include <QCoreApplication>
#include "Map.h"


trajektorie3d::trajektorie3d(QWidget *parent)
	: QMainWindow(parent)
{
    ui.setupUi(this);

	QObject::connect(ui.button_start, SIGNAL(clicked()), this, SLOT(startAlgorithm()));
	
	
}

trajektorie3d::~trajektorie3d()
{

}

void trajektorie3d::startAlgorithm()
{
	// change the text
	ui.button_start->setText("GO");

	std::cout << "Hej! ";
	int n = 10;
	int m = 10;
	
	// rysowanie przyk³adowej mapy
	Map map(n,m);
	map.setStart(1, 1);
	map.setStop(9, 9);
	map.setObstacle(1, 0);
	map.setObstacle(5, 2);
	map.setObstacle(5, 3);
	map.setObstacle(5, 4);
	map.setObstacle(5, 5);

	QString a = QString::number(map.returnValue(1, 1));
	ui.label_numOperations->setText(a);

	map.show();
        


}