#ifndef REMOVEOBSTACLE_H
#define REMOVEOBSTACLE_H

#include <QDialog>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include "Map.h"

namespace Ui {
	class RemoveObstacle;
}

class RemoveObstacle : public QDialog
{
	Q_OBJECT

public:
	explicit RemoveObstacle(QWidget *parent, Map* m);
	~RemoveObstacle();

private:
	Ui::RemoveObstacle *ui;
	QStringListModel *model;
	Map* map;

public slots:
	void remove();
};

#endif // REMOVEOBSTACLE_H

