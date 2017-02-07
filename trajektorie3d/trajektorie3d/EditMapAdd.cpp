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
		ui->zLineEdit->setText(QString::number(cell.cell_z()));
	} else {
		ui->xLineEdit->setText("");
		ui->yLineEdit->setText("");
		ui->zLineEdit->setText("");
	}

	QPalette palette;
	palette.setColor(QPalette::Base, Qt::white);
	palette.setColor(QPalette::Text, Qt::black);
	ui->xLineEdit->setPalette(palette);
	ui->yLineEdit->setPalette(palette);
	ui->zLineEdit->setPalette(palette);
	ui->errorLabel->setText("");
}


void EditMapAdd::accept2() {
	int w = (ui->xLineEdit->text()).toInt();
	int d = (ui->yLineEdit->text()).toInt();
	int h = (ui->zLineEdit->text()).toInt();

	QPalette palette;
	palette.setColor(QPalette::Base, Qt::white);
	palette.setColor(QPalette::Text, Qt::black);
	ui->xLineEdit->setPalette(palette);
	ui->yLineEdit->setPalette(palette);
	ui->zLineEdit->setPalette(palette);
	ui->errorLabel->setText("");
	
	if (!(w < 1 || w > map->getWidth() || d < 1 || d > map->getDepth() || h < 1 || h > map->getHeight())) {
		if (cellState == CellState::Start) {
			Cell lastCell = map->getStart();
			Cell stopCell = map->getStop();
			if (w == stopCell.cell_x() && d == stopCell.cell_y() && h == stopCell.cell_z()) {
				ui->errorLabel->setText("Tutaj znajduje się STOP");
			} else if (!(w == lastCell.cell_x() && d == lastCell.cell_y() && h == lastCell.cell_z())) {
				map->setStart(w, d, h);
				map->setEmpty(lastCell.cell_x(), lastCell.cell_y(), lastCell.cell_z());
				QDialog::accept(); // to close the dialog and return 1
			}
		} else if (cellState == CellState::Koniec) {
			Cell lastCell = map->getStop();
			Cell startCell = map->getStart();
			if (w == startCell.cell_x() && d == startCell.cell_y() && h == startCell.cell_z()) {
				ui->errorLabel->setText("Tutaj znajduje się START");
			} else if (!(w == lastCell.cell_x() && d == lastCell.cell_y() && h == lastCell.cell_z())) {
				map->setStop(w, d);
				map->setEmpty(lastCell.cell_x(), lastCell.cell_y(), lastCell.cell_z());
				QDialog::accept(); // to close the dialog and return 1
			}
		} else if (cellState == CellState::Zajeta) {
			Cell stopCell = map->getStop();
			Cell startCell = map->getStart();
			if (w == startCell.cell_x() && d == startCell.cell_y() && h == startCell.cell_z()) {
				ui->errorLabel->setText("Tutaj znajduje się START");
			} else if (w == stopCell.cell_x() && d == stopCell.cell_y() && h == stopCell.cell_z()) {
				ui->errorLabel->setText("Tutaj znajduje się STOP");
			} else {
				map->setObstacle(w, d, h);
				QDialog::accept(); // to close the dialog and return 1
			}
		}
	}
	else {
		palette.setColor(QPalette::Base, Qt::red);
		palette.setColor(QPalette::Text, Qt::black);
		if (w < 1 || w > map->getWidth()) {
			ui->xLineEdit->setPalette(palette);
		}
		if (d < 1 || d > map->getDepth()) {
			ui->yLineEdit->setPalette(palette);
		}
		if (h < 1 || h > map->getHeight()) {
			ui->zLineEdit->setPalette(palette);
		}
		ui->errorLabel->setText("Nieprawidłowy zakres");
	}
	

}


EditMapAdd::~EditMapAdd()
{
}
