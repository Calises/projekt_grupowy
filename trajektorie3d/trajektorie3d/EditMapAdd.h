#ifndef EDITMAPADD_H
#define EDITMAPADD_H

#include <QDialog>
#include "Map.h"
#include "Cell.h"

namespace Ui {
	class EditMapAdd;
}

class EditMapAdd : public QDialog
{
	Q_OBJECT

public:
	explicit EditMapAdd(QWidget *parent = 0);
	~EditMapAdd();

public slots:
	void accept2();
	void setEditMap(std::string, Map*, CellState);


private:
	Ui::EditMapAdd *ui;
	Map* map = NULL;
	CellState cellState;
};

#endif // EDITMAPADD_H

