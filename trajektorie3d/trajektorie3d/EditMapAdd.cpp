#include "EditMapAdd.h"
#include "ui_EditMapAdd.h"

EditMapAdd::EditMapAdd(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::EditMapAdd)
{
	ui->setupUi(this);
	QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept2()));
	QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

}

void EditMapAdd::setEditMap(std::string name, Map *m, CellState cS) {
	setWindowTitle(QString::fromStdString(name));
	map = m;
	cellState = cS;
	Cell cell;
	Cell *p = &cell;
	//Set p to hold NULL
	p = NULL;

	if (cellState == CellState::Start) {
		cell = map->getStart();
	} else if (cellState == CellState::Koniec) {
		cell = map->getStop();
	}

	if (p != NULL) {
		ui->xLineEdit->setText(QString::number(cell.cell_x()));
		ui->yLineEdit->setText(QString::number(cell.cell_y()));
	} else {
		ui->xLineEdit->setText("");
		ui->yLineEdit->setText("");
	}

	QPalette palette;
	palette.setColor(QPalette::Base, Qt::white);
	palette.setColor(QPalette::Text, Qt::black);
	ui->xLineEdit->setPalette(palette);
	ui->yLineEdit->setPalette(palette);
	ui->errorLabel->setText("");
}


void EditMapAdd::accept2() {
	QString w = ui->xLineEdit->text();
	QString d = ui->yLineEdit->text();

	QPalette palette;
	palette.setColor(QPalette::Base, Qt::white);
	palette.setColor(QPalette::Text, Qt::black);
	ui->xLineEdit->setPalette(palette);
	ui->yLineEdit->setPalette(palette);
	ui->errorLabel->setText("");
	
	if (!(w.toInt() < 1 || w.toInt() > map->getWidth() || d.toInt() < 1 || d.toInt() > map->getDepth())) {
		if (cellState == CellState::Start) {
			Cell lastCell = map->getStart();
			Cell stopCell = map->getStop();
			if (w.toInt() == stopCell.cell_x() && d.toInt() == stopCell.cell_y()) {
				ui->errorLabel->setText("Tutaj znajduje się STOP");
			} else if (!(w.toInt() == lastCell.cell_x() && d.toInt() == lastCell.cell_y())) {
				map->setStart(w.toInt(), d.toInt());
				map->setEmpty(lastCell.cell_x(), lastCell.cell_y());
				QDialog::accept(); // to close the dialog and return 1
			}
		} else if (cellState == CellState::Koniec) {
			Cell lastCell = map->getStop();
			Cell startCell = map->getStart();
			if (w.toInt() == startCell.cell_x() && d.toInt() == startCell.cell_y()) {
				ui->errorLabel->setText("Tutaj znajduje się START");
			} else if (!(w.toInt() == lastCell.cell_x() && d.toInt() == lastCell.cell_y())) {
				map->setStop(w.toInt(), d.toInt());
				map->setEmpty(lastCell.cell_x(), lastCell.cell_y());
				QDialog::accept(); // to close the dialog and return 1
			}
		} else if (cellState == CellState::Zajeta) {
			Cell stopCell = map->getStop();
			Cell startCell = map->getStart();
			if (w.toInt() == startCell.cell_x() && d.toInt() == startCell.cell_y()) {
				ui->errorLabel->setText("Tutaj znajduje się START");
			} else if (w.toInt() == stopCell.cell_x() && d.toInt() == stopCell.cell_y()) {
				ui->errorLabel->setText("Tutaj znajduje się STOP");
			} else {
				map->setObstacle(w.toInt(), d.toInt());
				QDialog::accept(); // to close the dialog and return 1
			}
		}
	}
	else {
		palette.setColor(QPalette::Base, Qt::red);
		palette.setColor(QPalette::Text, Qt::black);
		if (w.toInt() < 1 || w.toInt() > map->getWidth()) {
			ui->xLineEdit->setPalette(palette);
		}
		if (d.toInt() < 1 || d.toInt() > map->getDepth()) {
			ui->yLineEdit->setPalette(palette);
		}
		ui->errorLabel->setText("Nieprawidłowy zakres");
	}
	

}


EditMapAdd::~EditMapAdd()
{
}
