#include "RemoveObstacle.h"
#include "ui_RemoveObstacle.h"
#include <vector>

RemoveObstacle::RemoveObstacle(QWidget *parent, Map* m) :
QDialog(parent),
ui(new Ui::RemoveObstacle)
{
	map = m;
	ui->setupUi(this);

	QObject::connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(remove()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	model = new QStringListModel(this);
	std::vector <Cell> obstacleList = map->getObstacleList();
	QStringList list;

	for (size_t i = 0; i < obstacleList.size(); i++) {
		Cell obstacleCell = obstacleList[i];
		list << ("X: " + QString::number(obstacleCell.cell_x()) + " Y: " + QString::number(obstacleCell.cell_y()));
	}

	model->setStringList(list);
	ui->obList->setModel(model);
}

void RemoveObstacle::remove() {
	std::vector <Cell> obstacleList = map->getObstacleList();
	QModelIndexList selectedRowsIndexesList = ui->obList->selectionModel()->selectedRows();
	for (int i = 0; i < selectedRowsIndexesList.size(); i++) {		
		QModelIndex q = selectedRowsIndexesList[i];
		Cell c = obstacleList[q.row()];
		map->setEmpty(c.cell_x(), c.cell_y());
	}
	QDialog::accept(); // to close the dialog and return 1
}


RemoveObstacle::~RemoveObstacle()
{
}
