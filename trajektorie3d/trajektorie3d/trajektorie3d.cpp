#include "Trajektorie3d.h"
#include "Map.h"
#include "utils.h"

#include <QCoreApplication>
#include <QSettings>
#include <QFileDialog>
#include <qmessagebox.h>
#include <list>

Trajektorie3d::Trajektorie3d(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Trajektorie3dClass)
{
    ui->setupUi(this);

    // widgety algorytm ------------------------------------------
    ui->comboBox_algorithm->addItem("Propagacja Fali");
    ui->comboBox_algorithm->addItem("Sztuczne Pola Potencjalowe");
    ui->radioButton_Manhattan->setChecked(true);
    connect(ui->button_start, &QPushButton::clicked,
        [=]() {Start();  });
    // -----------------------------------------------------------

	connect(ui->chooseMapButton, &QPushButton::clicked,
			this, &Trajektorie3d::loadMap);

    connect(ui->actionClose, &QAction::triggered,
            this, &QMainWindow::close);
    connect(ui->actionSaveMap, &QAction::triggered,
            this, &Trajektorie3d::saveMap);
    connect(ui->actionLoadMap, &QAction::triggered,
            this, &Trajektorie3d::loadMap);

    connect(ui->actionAbout, &QAction::triggered,
            [=]() { aboutWindow->show(); });

    connect(ui->turnLeftButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Left); });
    connect(ui->turnRightButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Right); });
    connect(ui->turnUpButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Up); });
    connect(ui->turnDownButton, &QPushButton::clicked,
        [=](){ ogreWidget->turnCamera(Direction::Down); });

	connect(ui->setStartButton, &QPushButton::clicked,
		[=]() {showEditMap("Start", CellState::Start); });
	connect(ui->setStopButton, &QPushButton::clicked,
		[=]() {showEditMap("Stop", CellState::Koniec);  });
	connect(ui->addObstacleButton, &QPushButton::clicked,
		[=]() {showEditMap("Przeszkoda", CellState::Zajeta);  });
	connect(ui->removeObstacleButton, &QPushButton::clicked,
		[=]() {removeObstacle();  });

    


	//ogreWidget = new OgreWidget(this);
	//ogreWidget->setFixedWidth(640);
	//ogreWidget->setFixedHeight(480);

	//ui->centralLayout->addWidget(ogreWidget, 0, 0, 1, 1);

    // tworzenie przykladowej mapy
    map = new Map(10, 10, 10);
    map->setStart(1, 1, 1);
    map->setStop(9, 9, 1);
    map->setObstacle(1, 0, 1);
    map->setObstacle(5, 2, 1);
    map->setObstacle(5, 3, 1);
    map->setObstacle(5, 4, 1);
    map->setObstacle(5, 5, 1);

	aboutWindow = new AboutWindow(this); 
}

void Trajektorie3d::showEditMap(std::string name, CellState cS){
	EditMapAdd* editMappAddStart = new EditMapAdd(this);
	QObject::connect(editMappAddStart, SIGNAL(finished(int)), this, SLOT(dialogIsFinished(int)));
	editMappAddStart->setEditMap(name, map, cS);
	editMappAddStart->show();
}

void Trajektorie3d::removeObstacle() {
	RemoveObstacle* ro = new RemoveObstacle(this, map);
	QObject::connect(ro, SIGNAL(finished(int)), this, SLOT(dialogIsFinished(int)));
	ro->show();
}

Trajektorie3d::~Trajektorie3d()
{
}

void Trajektorie3d::dialogIsFinished(int result) {
	if (result == QDialog::Accepted) {
        ogreWidget->redrawScene(map);
		return;
	}
}

void Trajektorie3d::loadMap()
{
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Wybierz map�"), "maps/",
                                                    QStringLiteral("Map files (*.tmap)"));
    if (fileName == 0)
        return;

    ui->mapNameLabel->setText(fileName.split('/').last());

    QSettings settings(fileName, QSettings::IniFormat);

    int width = settings.value("width").toInt();
    int depth = settings.value("depth").toInt();
    int height = settings.value("height").toInt();
    map = new Map(width, depth, height);
    
    for (int w = 1; w <= width; w++)
    {
        settings.beginGroup(QString::number(w));
        for (int d = 1; d <= depth; d++)
        {
            settings.beginGroup(QString::number(d));
            for (int h = 1; h <= height; h++)
            {
                CellState newState =
                    CellState(settings.value(QString::number(h),CellState::Wolna).toInt());

                switch(newState)
                {
                case CellState::Zajeta:
                    map->setObstacle(w, d, h);
                    break;
                case CellState::Start:
                    map->setStart(w, d, h);
                    break;
                case CellState::Koniec:
                    map->setStop(w, d, h);
                    break;
                case CellState::Droga:
                    map->setTrace(w, d, h);
                    break;
                default:
                    break;
                }
            }
            settings.endGroup();
        }
        settings.endGroup();
    }

    ogreWidget->redrawScene(map);
}

void Trajektorie3d::saveMap()
{
    QDir::current().mkdir("maps/");
    QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("Zapisz map�"), "maps/",
                                                    QStringLiteral("Map files (*.tmap)"));
    if (fileName == 0)
        return;

    if (QFile::exists(fileName))
        QFile::remove(fileName);

    QSettings settings(fileName, QSettings::IniFormat);

    int width = map->getWidth();
    settings.setValue("width", width);
    int depth = map->getDepth();
    settings.setValue("depth", depth);
    int height = map->getHeight();
    settings.setValue("height", height);

    for (int w = 1; w <= width; w++)
    {
        settings.beginGroup(QString::number(w));
        for (int d = 1; d <= depth; d++)
        {
            settings.beginGroup(QString::number(d));
            for (int h = 1; h <= height; h++)
            {
                CellState state = map->returnState(w, d, h);
                if (state != CellState::Wolna)
                    settings.setValue(QString::number(h), state);
            }
            settings.endGroup();
        }
        settings.endGroup();
    }
}



void Trajektorie3d::Start()
{
    Metric metric;
    if (ui->radioButton_Manhattan->isChecked())
        metric = Manhattan;
    else if (ui->radioButton_Czebyszew->isChecked())
        metric = Czebyszew;
    else
        QMessageBox::warning(this,"Uwaga", "Zanacz matryke!");


    if (ui->comboBox_algorithm->currentIndex() == 0)
    {
        //StartAlg_Propagacja(metric);
    }     
    else if (ui->comboBox_algorithm->currentIndex() == 1)
    {
        //StartAlg_SztucznePotencjaly(matric);
    }      
}
void Trajektorie3d::przekaz(Cell endCell, int lengthTrace)
{
    cout << endl << "wierzcholek koncowy: " << "x " << endCell.cell_x() << " y " << endCell.cell_y() << " z " << endCell.cell_z() << " krok " << lengthTrace;
    searchTrace(endCell, lengthTrace);
}
void Trajektorie3d::StartAlg_Propagacja(Metric metric)
{

    if (!map)
        return;

    //lista z aktualnym czo�em fali 
    list <Cell> listNow;
    //lista z czo�em fali w nast�pnym kroku
    list <Cell> listNext;

    Cell stop = map->getStop();
    listNow.push_back(stop);
    Cell currentCell = map->getStop();
    Cell buf = map->getStop();
    Cell potentialCell = map->getStop();

    bool run = 1;
    int lengthTrace = 1;
    int rr = 1;
    int currentX = map->getStop().cell_x();
    int currentY = map->getStop().cell_y();
    int currentZ = map->getStop().cell_z();

    while (run)
    {
        while (!listNow.empty())
        {
            cout << "list now" << endl;
            currentCell = listNow.back();
            listNow.pop_back();

            currentX = currentCell.cell_x();
            currentY = currentCell.cell_y();
            currentZ = currentCell.cell_z();

            cout << "aktualny: " << currentX << " " << currentY << " " << currentZ << " ";
            cout << "rr" << rr;

            //Polnoc
            if ((map->returnState(currentX, currentY - 1, currentZ) == Wolna) ||
                (map->returnState(currentX, currentY - 1, currentZ) == CellState::Start))
            {
                if (map->returnState(currentX, currentY - 1, currentZ) == CellState::Start)
                {
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(currentCell, lengthTrace);
                }
                potentialCell = map->getCell(currentX, currentY - 1, currentZ);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Poludnie
            if ((map->returnState(currentX, currentY + 1, currentZ) == Wolna) ||
                (map->returnState(currentX, currentY + 1, currentZ) == CellState::Start))
            {
                if (map->returnState(currentX, currentY + 1, currentZ) == CellState::Start)
                {
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(currentCell, lengthTrace);
                }
                potentialCell = map->getCell(currentX, currentY + 1, currentZ);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Wschod
            if ((map->returnState(currentX + 1, currentY, currentZ) == Wolna) ||
                (map->returnState(currentX + 1, currentY, currentZ) == CellState::Start))
            {
                if (map->returnState(currentX + 1, currentY, currentZ) == CellState::Start)
                {
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(currentCell, lengthTrace);
                }
                potentialCell = map->getCell(currentX + 1, currentY, currentZ);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Zachod
            if ((map->returnState(currentX - 1, currentY, currentZ) == Wolna) ||
                (map->returnState(currentX - 1, currentY, currentZ) == CellState::Start))
            {
                if (map->returnState(currentX - 1, currentY, currentZ) == CellState::Start)
                {
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(currentCell, lengthTrace);
                }
                potentialCell = map->getCell(currentX - 1, currentY, currentZ);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            currentCell.change_cell(lengthTrace, Wolna);
        }

        //przepisanie "czola fali" po zako�czeniu iteracji
        while (!listNext.empty())
        {
            buf = listNext.back();
            listNow.push_front(buf);
            listNext.pop_back();
        }
    }


    map->show();

    //tymczasowe wywo�anie, domy�lnie zamiast map wrzuci� wynik algorytmu
    //ogreWidget->redrawScene(map);
}

void Trajektorie3d::searchTrace(Cell endCell, int lengthTrace)
{
    Cell cellTrace;
    list <Cell> trace;
    trace.push_back(endCell);
    int x = endCell.cell_x();
    int y = endCell.cell_y();
    int z = endCell.cell_z();


    while (lengthTrace > 0)
    {
        if (map->returnValue(x - 1, y, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y, z);
            map->setTrace(x - 1, y, z);
            trace.push_back(cellTrace);
            x--;
        }
        else if (map->returnValue(x + 1, y, z) == lengthTrace - 1) 
        {
            cellTrace = map->getCell(x + 1, y, z);
            map->setTrace(x + 1, y, z);
            trace.push_back(cellTrace);
            x++;
        }
        else if (map->returnValue(x, y + 1, z) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y + 1, z);
            map->setTrace(x, y + 1, z);
            trace.push_back(cellTrace);
            y++;
        }
        else if (map->returnValue(x, y - 1, z) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y - 1, z);
            map->setTrace(x, y - 1, z);
            trace.push_back(cellTrace);
            y--;
        }

        QString lengthTraceString;
        //lengthTraceString.setNum(trace.size());
        //ui->label_lengthWay.setText(lengthTraceString.setNum(trace.size()));
        lengthTrace--;

    }

}