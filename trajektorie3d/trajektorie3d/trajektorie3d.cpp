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

    connect(ui->openMapButton, &QPushButton::clicked,
			this, &Trajektorie3d::loadMap);
    connect(ui->saveMapButton, &QPushButton::clicked,
            this, &Trajektorie3d::saveMap);
    connect(ui->newMapButton, &QPushButton::clicked,
            this, &Trajektorie3d::newMap);
    connect(ui->clearMapButton, &QPushButton::clicked,
            this, &Trajektorie3d::clearMap);

    connect(ui->actionClose, &QAction::triggered,
            this, &QMainWindow::close);
    connect(ui->actionSaveMap, &QAction::triggered,
            this, &Trajektorie3d::saveMap);
    connect(ui->actionLoadMap, &QAction::triggered,
            this, &Trajektorie3d::loadMap);
    connect(ui->actionNewMap, &QAction::triggered,
            this, &Trajektorie3d::newMap);
    connect(ui->actionClearMap, &QAction::triggered,
            this, &Trajektorie3d::clearMap);

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

	ogreWidget = new OgreWidget(this);
	ogreWidget->setFixedWidth(640);
	ogreWidget->setFixedHeight(480);

	ui->centralLayout->addWidget(ogreWidget, 0, 0, 1, 1);

    // tworzenie przykladowej mapy
    map = new Map(10, 10, 10);
    map->setStart(1, 1, 1);
    map->setStop(9, 9, 1);
    map->setObstacle(1, 0, 1);
    map->setObstacle(5, 2, 1);
    map->setObstacle(5, 3, 1);
    map->setObstacle(5, 4, 1);
    map->setObstacle(5, 5, 1);
    map->setObstacle(8, 9, 1);
    map->setObstacle(7, 8, 1);


    aboutWindow = new AboutWindow(this);
    newDimensionsDialog = new DimensionsDialog(this);
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
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("Wybierz mapê"), "maps/",
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
    QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("Zapisz mapê"), "maps/",
                                                    QStringLiteral("Map files (*.tmap)"));
    if (fileName == 0)
        return;

    ui->mapNameLabel->setText(fileName.split('/').last());

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

void Trajektorie3d::newMap()
{
    bool ok = newDimensionsDialog->exec();
    if(!ok)
        return;

    delete map;
    map = new Map(newDimensionsDialog->getX(),
                  newDimensionsDialog->getY(),
                  newDimensionsDialog->getZ());

    ui->mapNameLabel->setText(QString());
    ogreWidget->redrawScene(map);
}

void Trajektorie3d::clearMap()
{
    int width = map->getWidth();
    int depth = map->getWidth();
    int height = map->getWidth();

    for(int w = 1; w <= width; w++)
    {
        for(int d = 1; d <= depth; d++)
        {
            for(int h = 1; h <= height; h++)
            {
                if(map->returnState(w, d, h) == CellState::Droga)
                    map->setEmpty(w,d,h);
            }
        }
    }
    ogreWidget->redrawScene(map);
}

void Trajektorie3d::Start()
{
    clearMap();

    Metric metric;
    if (ui->radioButton_Manhattan->isChecked())
        metric = Manhattan;
    else if (ui->radioButton_Czebyszew->isChecked())
        metric = Czebyszew;
    else
        QMessageBox::warning(this,"Uwaga", "Zanacz matryke!");


    if (ui->comboBox_algorithm->currentIndex() == 0)
    {
        if(metric == Manhattan)
            propagacjaFaliManhattan();
        if(metric == Czebyszew)
            propagacjaFaliCzebyszew();
    }     
    else if (ui->comboBox_algorithm->currentIndex() == 1)
    {
        //StartAlg_SztucznePotencjaly(matric);
    }      
}

void Trajektorie3d::przekaz(Metric metric, Cell endCell, int lengthTrace)
{
    qDebug() << QString("wierzcholek koncowy");
    QString msg;
    msg += QString::number(endCell.cell_x()) + QString(" ") + QString::number(endCell.cell_y());
    qDebug() << msg;
    if (metric == Manhattan)
        searchTrace(endCell, lengthTrace);
    if (metric == Czebyszew)
        searchTraceCzebyszew(endCell, lengthTrace);
}

void Trajektorie3d::propagacjaFaliManhattan()
{
    if (!map)
        return;

    qDebug() << QString("start");
    //lista z aktualnym czo³em fali 
    list <Cell> listNow;
    //lista z czo³em fali w nastêpnym kroku
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

    qDebug() << QString("mapa");
    rysuj();
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
            if ((map->returnValue(currentX, currentY - 1, currentZ) == 100) ||
                (map->returnValue(currentX, currentY - 1, currentZ) == 101))
            {
                if (map->returnValue(currentX, currentY - 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY - 1, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY - 1, currentZ);
                map->setValue(currentX, currentY - 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Poludnie
            if ((map->returnValue(currentX, currentY + 1, currentZ) == 100) ||
                (map->returnValue(currentX, currentY + 1, currentZ) == 101))
            {
                if (map->returnValue(currentX, currentY + 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY + 1, currentZ);
                    //qDebug() << QString("koniec2");
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    break;
                    
                }
                potentialCell = map->getCell(currentX, currentY + 1, currentZ);
                map->setValue(currentX, currentY + 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Wschod
            if ((map->returnValue(currentX + 1, currentY, currentZ) == 100) ||
                (map->returnValue(currentX + 1, currentY, currentZ) == 101))
            {
                if (map->returnValue(currentX + 1, currentY, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY, currentZ);
                   
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    //stopCell.cell_change(101, Start);
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec3");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY, currentZ);
                map->setValue(currentX + 1, currentY, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Zachod
            if ((map->returnValue(currentX - 1, currentY, currentZ) == 100) ||
                (map->returnValue(currentX - 1, currentY, currentZ) == 101))
            {
                if (map->returnValue(currentX - 1, currentY, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX -1, currentY, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY, currentZ);
                //algorithmAddCell(&listNow, &listNext, potentialCell, lengthTrace);
                map->setValue(currentX - 1, currentY, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //dol
            if ((map->returnValue(currentX, currentY, currentZ - 1) == 100) ||
                (map->returnValue(currentX, currentY, currentZ - 1) == 101))
            {
                if (map->returnValue(currentX, currentY, currentZ - 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY, currentZ - 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY, currentZ - 1);
                //algorithmAddCell(&listNow, &listNext, potentialCell, lengthTrace);
                map->setValue(currentX, currentY, currentZ - 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //gora
            if ((map->returnValue(currentX, currentY, currentZ + 1) == 100) ||
                (map->returnValue(currentX, currentY, currentZ + 1) == 101))
            {
                if (map->returnValue(currentX, currentY, currentZ + 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY, currentZ + 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY, currentZ + 1);
                //algorithmAddCell(&listNow, &listNext, potentialCell, lengthTrace);
                map->setValue(currentX, currentY, currentZ + 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            currentCell.change_cell(lengthTrace, Wolna);
        }
        lengthTrace++;

        //przepisanie "czola fali" po zakoñczeniu iteracji
        while (!listNext.empty())
        {
            buf = listNext.back();
            listNow.push_front(buf);
            listNext.pop_back();
        }
        //lengthTrace++;
        system("pause");
        rysuj();
        
        
    }
    qDebug() << QString("koniec petli");
    //map->show();

    ogreWidget->redrawScene(map);
}
list<Cell>* Trajektorie3d::algorithmAddCell(list<Cell> *listNow, list<Cell> *listNext, Cell cell, int lengthTrace)
{
    map->setValue(cell.cell_x() - 1, cell.cell_y(), cell.cell_z(), lengthTrace);
    cell.change_cell(lengthTrace, Wolna);
 //   *listNext.push_back(cell);
    return listNext;
}

void Trajektorie3d::searchTrace(Cell endCell, int lengthTrace)
{
    Cell cellTrace;
    
    //endCell.change_cell(101, Start);
    list <Cell> trace;
    trace.push_back(endCell);
    int x = endCell.cell_x();
    int y = endCell.cell_y();
    int z = endCell.cell_z();
    map->setStart(x, y, z);

    while (lengthTrace > 1)
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
        else if (map->returnValue(x, y, z - 1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x, y, z - 1);
            map->setTrace(x, y, z - 1);
            trace.push_back(cellTrace);
            z--;
        }
        else if (map->returnValue(x, y, z + 1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x, y, z + 1);
            map->setTrace(x, y, z + 1);
            trace.push_back(cellTrace);
            z++;
        }

        QString lengthTraceString;
        //lengthTraceString.setNum(trace.size());
        ui->label_lengthWay->setText(lengthTraceString.setNum(trace.size()));
        lengthTrace--;

    }
    rysuj();


}

void Trajektorie3d::propagacjaFaliCzebyszew()
{
    if (!map)
        return;

    map->updateBuffer(ui->spinBox_przeszkoda->value());

    qDebug() << QString("start");
    //lista z aktualnym czo³em fali 
    list <Cell> listNow;
    //lista z czo³em fali w nastêpnym kroku
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

    qDebug() << QString("mapa");
    rysuj();
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

            //lewy gorny skos
            if ((map->returnValue(currentX - 1, currentY - 1, currentZ) == 100) ||
                (map->returnValue(currentX - 1, currentY - 1, currentZ) == 101))
            {
                if (map->returnValue(currentX - 1, currentY - 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY - 1, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY - 1, currentZ);
                map->setValue(currentX - 1, currentY - 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //lewy gorny skos nad
            if ((map->returnValue(currentX - 1, currentY - 1, currentZ - 1) == 100) ||
                (map->returnValue(currentX - 1, currentY - 1, currentZ - 1) == 101))
            {
                if (map->returnValue(currentX - 1, currentY - 1, currentZ - 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY - 1, currentZ - 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY - 1, currentZ - 1);
                map->setValue(currentX - 1, currentY - 1, currentZ - 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //lewy gorny skos pod
            if ((map->returnValue(currentX - 1, currentY - 1, currentZ + 1) == 100) ||
                (map->returnValue(currentX - 1, currentY - 1, currentZ + 1) == 101))
            {
                if (map->returnValue(currentX - 1, currentY - 1, currentZ + 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY - 1, currentZ + 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY - 1, currentZ + 1);
                map->setValue(currentX - 1, currentY - 1, currentZ + 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //--------------------------------------------------------------------------------
            //prawy gorny skos
            if ((map->returnValue(currentX + 1, currentY - 1, currentZ) == 100) ||
                (map->returnValue(currentX + 1, currentY - 1, currentZ) == 101))
            {
                if (map->returnValue(currentX + 1, currentY - 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY - 1, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY - 1, currentZ);
                map->setValue(currentX + 1, currentY - 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //prawy gorny skos nad
            if ((map->returnValue(currentX + 1, currentY - 1, currentZ - 1) == 100) ||
                (map->returnValue(currentX + 1, currentY - 1, currentZ - 1) == 101))
            {
                if (map->returnValue(currentX + 1, currentY - 1, currentZ - 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY - 1, currentZ - 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY - 1, currentZ - 1);
                map->setValue(currentX + 1, currentY - 1, currentZ - 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //prawy gorny skos pod
            if ((map->returnValue(currentX + 1, currentY - 1, currentZ + 1) == 100) ||
                (map->returnValue(currentX + 1, currentY - 1, currentZ + 1) == 101))
            {
                if (map->returnValue(currentX + 1, currentY - 1, currentZ + 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY - 1, currentZ + 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY - 1, currentZ + 1);
                map->setValue(currentX + 1, currentY - 1, currentZ + 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //-----------------------------------------------------------------------------------
            //prawy dolny skok 
            if ((map->returnValue(currentX - 1, currentY + 1, currentZ) == 100) ||
                (map->returnValue(currentX - 1, currentY + 1, currentZ) == 101))
            {
                if (map->returnValue(currentX - 1, currentY + 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY + 1, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY + 1, currentZ);
                map->setValue(currentX - 1, currentY + 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //prawy dolny skok nad
            if ((map->returnValue(currentX - 1, currentY + 1, currentZ - 1) == 100) ||
                (map->returnValue(currentX - 1, currentY + 1, currentZ - 1) == 101))
            {
                if (map->returnValue(currentX - 1, currentY + 1, currentZ - 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY + 1, currentZ - 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY + 1, currentZ - 1);
                map->setValue(currentX - 1, currentY + 1, currentZ - 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //prawy dolny skok pod
            if ((map->returnValue(currentX - 1, currentY + 1, currentZ + 1) == 100) ||
                (map->returnValue(currentX - 1, currentY + 1, currentZ + 1) == 101))
            {
                if (map->returnValue(currentX - 1, currentY + 1, currentZ + 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY + 1, currentZ + 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY + 1, currentZ + 1);
                map->setValue(currentX - 1, currentY + 1, currentZ + 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //------------------------------------------------------------------------------
            //lewy dolny skok
            if ((map->returnValue(currentX + 1, currentY + 1, currentZ) == 100) ||
                (map->returnValue(currentX + 1, currentY + 1, currentZ) == 101))
            {
                if (map->returnValue(currentX + 1, currentY + 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY + 1, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY + 1, currentZ);
                map->setValue(currentX + 1, currentY + 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //lewy dolny skok nad 
            if ((map->returnValue(currentX + 1, currentY + 1, currentZ - 1) == 100) ||
                (map->returnValue(currentX + 1, currentY + 1, currentZ - 1) == 101))
            {
                if (map->returnValue(currentX + 1, currentY + 1, currentZ - 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY + 1, currentZ - 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY + 1, currentZ - 1);
                map->setValue(currentX + 1, currentY + 1, currentZ - 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //lewy dolny skok pod
            if ((map->returnValue(currentX + 1, currentY + 1, currentZ + 1) == 100) ||
                (map->returnValue(currentX + 1, currentY + 1, currentZ + 1) == 101))
            {
                if (map->returnValue(currentX + 1, currentY + 1, currentZ + 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY + 1, currentZ + 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY + 1, currentZ + 1);
                map->setValue(currentX + 1, currentY + 1, currentZ + 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //---------------------------------------------------------------------------
            //Polnoc
            if ((map->returnValue(currentX, currentY - 1, currentZ) == 100) ||
                (map->returnValue(currentX, currentY - 1, currentZ) == 101))
            {
                if (map->returnValue(currentX, currentY - 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY - 1, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY - 1, currentZ);
                map->setValue(currentX, currentY - 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Polnoc nad
            if ((map->returnValue(currentX, currentY - 1, currentZ -1) == 100) ||
                (map->returnValue(currentX, currentY - 1, currentZ -1) == 101))
            {
                if (map->returnValue(currentX, currentY - 1, currentZ -1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY - 1, currentZ -1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY - 1, currentZ -1);
                map->setValue(currentX, currentY - 1, currentZ -1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Polnoc pod
            if ((map->returnValue(currentX, currentY - 1, currentZ +1) == 100) ||
                (map->returnValue(currentX, currentY - 1, currentZ +1) == 101))
            {
                if (map->returnValue(currentX, currentY - 1, currentZ +1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY - 1, currentZ +1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY - 1, currentZ +1);
                map->setValue(currentX, currentY - 1, currentZ +1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //---------------------------------------------------------------------------
            //Poludnie
            if ((map->returnValue(currentX, currentY + 1, currentZ) == 100) ||
                (map->returnValue(currentX, currentY + 1, currentZ) == 101))
            {
                if (map->returnValue(currentX, currentY + 1, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY + 1, currentZ);
                    //qDebug() << QString("koniec2");
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    break;
                }
                potentialCell = map->getCell(currentX, currentY + 1, currentZ);
                map->setValue(currentX, currentY + 1, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Poludnie nad
            if ((map->returnValue(currentX, currentY + 1, currentZ-1) == 100) ||
                (map->returnValue(currentX, currentY + 1, currentZ-1) == 101))
            {
                if (map->returnValue(currentX, currentY + 1, currentZ-1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY + 1, currentZ-1);
                    //qDebug() << QString("koniec2");
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    break;
                }
                potentialCell = map->getCell(currentX, currentY + 1, currentZ-1);
                map->setValue(currentX, currentY + 1, currentZ-1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Poludnie pod
            if ((map->returnValue(currentX, currentY + 1, currentZ +1) == 100) ||
                (map->returnValue(currentX, currentY + 1, currentZ +1) == 101))
            {
                if (map->returnValue(currentX, currentY + 1, currentZ+1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY + 1, currentZ+1);
                    //qDebug() << QString("koniec2");
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    break;
                }
                potentialCell = map->getCell(currentX, currentY + 1, currentZ+1);
                map->setValue(currentX, currentY + 1, currentZ+1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //-----------------------------------------------------------------------
            //Wschod
            if ((map->returnValue(currentX + 1, currentY, currentZ) == 100) ||
                (map->returnValue(currentX + 1, currentY, currentZ) == 101))
            {
                if (map->returnValue(currentX + 1, currentY, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec3");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY, currentZ);
                map->setValue(currentX + 1, currentY, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Wschod nad
            if ((map->returnValue(currentX + 1, currentY, currentZ -1) == 100) ||
                (map->returnValue(currentX + 1, currentY, currentZ -1) == 101))
            {
                if (map->returnValue(currentX + 1, currentY, currentZ -1) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY, currentZ -1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec3");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY, currentZ -1);
                map->setValue(currentX + 1, currentY, currentZ -1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Wschod pod
            if ((map->returnValue(currentX + 1, currentY, currentZ +1) == 100) ||
                (map->returnValue(currentX + 1, currentY, currentZ +1) == 101))
            {
                if (map->returnValue(currentX + 1, currentY, currentZ +1) == 101)
                {
                    Cell stopCell = map->getCell(currentX + 1, currentY, currentZ +1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec3");
                    break;
                }
                potentialCell = map->getCell(currentX + 1, currentY, currentZ+1);
                map->setValue(currentX + 1, currentY, currentZ+1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //--------------------------------------------------------------------------
            //Zachod
            if ((map->returnValue(currentX - 1, currentY, currentZ) == 100) ||
                (map->returnValue(currentX - 1, currentY, currentZ) == 101))
            {
                if (map->returnValue(currentX - 1, currentY, currentZ) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY, currentZ);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY, currentZ);
                map->setValue(currentX - 1, currentY, currentZ, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Zachod nad
            if ((map->returnValue(currentX - 1, currentY, currentZ-1) == 100) ||
                (map->returnValue(currentX - 1, currentY, currentZ-1) == 101))
            {
                if (map->returnValue(currentX - 1, currentY, currentZ-1) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY, currentZ-1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY, currentZ-1);
                map->setValue(currentX - 1, currentY, currentZ-1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //Zachod pod
            if ((map->returnValue(currentX - 1, currentY, currentZ+1) == 100) ||
                (map->returnValue(currentX - 1, currentY, currentZ+1) == 101))
            {
                if (map->returnValue(currentX - 1, currentY, currentZ+1) == 101)
                {
                    Cell stopCell = map->getCell(currentX - 1, currentY, currentZ+1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Czebyszew, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX - 1, currentY, currentZ+1);
                map->setValue(currentX - 1, currentY, currentZ+1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //---------------------------------------------------------------------
            //dol
            if ((map->returnValue(currentX, currentY, currentZ - 1) == 100) ||
                (map->returnValue(currentX, currentY, currentZ - 1) == 101))
            {
                if (map->returnValue(currentX, currentY, currentZ - 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY, currentZ - 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY, currentZ - 1);
                //algorithmAddCell(&listNow, &listNext, potentialCell, lengthTrace);
                map->setValue(currentX, currentY, currentZ - 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            //gora
            if ((map->returnValue(currentX, currentY, currentZ + 1) == 100) ||
                (map->returnValue(currentX, currentY, currentZ + 1) == 101))
            {
                if (map->returnValue(currentX, currentY, currentZ + 1) == 101)
                {
                    Cell stopCell = map->getCell(currentX, currentY, currentZ + 1);
                    run = 0;
                    listNext.clear();
                    listNow.clear();
                    przekaz(Manhattan, stopCell, lengthTrace);
                    //qDebug() << QString("koniec4");
                    break;
                }
                potentialCell = map->getCell(currentX, currentY, currentZ + 1);
                //algorithmAddCell(&listNow, &listNext, potentialCell, lengthTrace);
                map->setValue(currentX, currentY, currentZ + 1, lengthTrace);
                potentialCell.change_cell(lengthTrace, Wolna);
                listNext.push_back(potentialCell);
                //currentCell.change_cell(lengthTrace, Wolna);
            }
            currentCell.change_cell(lengthTrace, Wolna);
        }
        lengthTrace++;

        //przepisanie "czola fali" po zakoñczeniu iteracji
        while (!listNext.empty())
        {
            buf = listNext.back();
            listNow.push_front(buf);
            listNext.pop_back();
        }
        //lengthTrace++;
        system("pause");
        rysuj();
    }
    qDebug() << QString("koniec petli");

    //map->show();

    ogreWidget->redrawScene(map);
}

void Trajektorie3d::searchTraceCzebyszew(Cell endCell, int lengthTrace)
{
    Cell cellTrace;
    list <Cell> trace;
    trace.push_back(endCell);
    int x = endCell.cell_x();
    int y = endCell.cell_y();
    int z = endCell.cell_z();
    map->setStart(x, y, z);

    while (lengthTrace > 1)
    {
        if (map->returnValue(x - 1, y - 1, z-1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y - 1, z - 1);
            map->setTrace(x - 1, y - 1, z - 1);
            trace.push_back(cellTrace);
            x--;
            y--;
            z--;
        }
        else if (map->returnValue(x - 1, y - 1, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y - 1, z);
            map->setTrace(x - 1, y - 1, z);
            trace.push_back(cellTrace);
            x--;
            y--;
        }
        else if (map->returnValue(x - 1, y - 1, z + 1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y - 1, z + 1);
            map->setTrace(x - 1, y - 1, z + 1);
            trace.push_back(cellTrace);
            x--;
            y--;
            z--;
            z++;
        }
        //-------------------------------------------------------------------
        else if (map->returnValue(x - 1, y + 1, z-1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y + 1, z - 1);
            map->setTrace(x - 1, y + 1, z - 1);
            trace.push_back(cellTrace);
            x--;
            y++;
            z--;
        }
        else if (map->returnValue(x - 1, y + 1, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y + 1, z);
            map->setTrace(x - 1, y + 1, z);
            trace.push_back(cellTrace);
            x--;
            y++;
        }
        else if (map->returnValue(x - 1, y + 1, z + 1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y + 1, z + 1);
            map->setTrace(x - 1, y + 1, z + 1);
            trace.push_back(cellTrace);
            x--;
            y++;
            z++;
        }
        //--------------------------------------------------------------------
        else if (map->returnValue(x + 1, y - 1, z -1 ) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y - 1, z -1);
            map->setTrace(x + 1, y - 1, z-1);
            trace.push_back(cellTrace);
            x++;
            y--;
            z--;
        }
        else if (map->returnValue(x + 1, y - 1, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y - 1, z);
            map->setTrace(x + 1, y - 1, z);
            trace.push_back(cellTrace);
            x++;
            y--;
        }
        else if (map->returnValue(x + 1, y - 1, z+1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y - 1, z+1);
            map->setTrace(x + 1, y - 1, z+1);
            trace.push_back(cellTrace);
            x++;
            y--;
            z++;
        }
        //---------------------------------------------------------------------
        else if (map->returnValue(x + 1, y + 1, z-1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y + 1, z-1);
            map->setTrace(x + 1, y + 1, z-1);
            trace.push_back(cellTrace);
            x++;
            y++;
            z--;
        }
        else if (map->returnValue(x + 1, y + 1, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y + 1, z);
            map->setTrace(x + 1, y + 1, z);
            trace.push_back(cellTrace);
            x++;
            y++;
        }
        else if (map->returnValue(x + 1, y + 1, z+1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y + 1, z+1);
            map->setTrace(x + 1, y + 1, z+1);
            trace.push_back(cellTrace);
            x++;
            y++;
            z++;
        }
        //--------------------------------------------------------------------
        else if (map->returnValue(x - 1, y, z-1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y, z-1);
            map->setTrace(x - 1, y, z-1);
            trace.push_back(cellTrace);
            x--;
            z--;
        }
        else if (map->returnValue(x - 1, y, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y, z);
            map->setTrace(x - 1, y, z);
            trace.push_back(cellTrace);
            x--;
        }
        else if (map->returnValue(x - 1, y, z+1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x - 1, y, z+1);
            map->setTrace(x - 1, y, z+1);
            trace.push_back(cellTrace);
            x--;
            z++;
        }
        //----------------------------------------------------------------------
        else if (map->returnValue(x + 1, y, z-1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y, z-1);
            map->setTrace(x + 1, y, z-1);
            trace.push_back(cellTrace);
            x++;
            z--;
        }
        else if (map->returnValue(x + 1, y, z) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y, z);
            map->setTrace(x + 1, y, z);
            trace.push_back(cellTrace);
            x++;
        }
        else if (map->returnValue(x + 1, y, z+1) == lengthTrace - 1)
        {
            cellTrace = map->getCell(x + 1, y, z+1);
            map->setTrace(x + 1, y, z+1);
            trace.push_back(cellTrace);
            x++;
            z++;
        }
        //----------------------------------------------------------------------
        else if (map->returnValue(x, y + 1, z-1) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y + 1, z-1);
            map->setTrace(x, y + 1, z-1);
            trace.push_back(cellTrace);
            y++;
            z--;
        }
        else if (map->returnValue(x, y + 1, z) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y + 1, z);
            map->setTrace(x, y + 1, z);
            trace.push_back(cellTrace);
            y++;
        }
        else if (map->returnValue(x, y + 1, z+1) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y + 1, z+1);
            map->setTrace(x, y + 1, z+1);
            trace.push_back(cellTrace);
            y++;
            z++;
        }
        //----------------------------------------------------------------
        else if (map->returnValue(x, y - 1, z-1) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y - 1, z-1);
            map->setTrace(x, y - 1, z-1);
            trace.push_back(cellTrace);
            y--;
            z--;
        }
        else if (map->returnValue(x, y - 1, z) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y - 1, z);
            map->setTrace(x, y - 1, z);
            trace.push_back(cellTrace);
            y--;
        }
        else if (map->returnValue(x, y - 1, z+1) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y - 1, z+1);
            map->setTrace(x, y - 1, z+1);
            trace.push_back(cellTrace);
            y--;
            z++;
        }
        //------------------------------------------------------------------
        else if (map->returnValue(x, y, z + 1) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y, z + 1);
            map->setTrace(x, y, z + 1);
            trace.push_back(cellTrace);
            z++;
        }
        else if (map->returnValue(x, y, z - 1) == lengthTrace - 1) {
            cellTrace = map->getCell(x, y, z - 1);
            map->setTrace(x, y, z - 1);
            trace.push_back(cellTrace);
            z--;
        }

        QString lengthTraceString;
        //lengthTraceString.setNum(trace.size());
        ui->label_lengthWay->setText(lengthTraceString.setNum(trace.size()));
        lengthTrace--;

    }

}

void Trajektorie3d::rysuj()
{
    qDebug() << endl;
    Cell currentCell;
    QString msg;


    for (int i = 0; i < map->getDepth(); i++)
    {
        for (int j = 0; j < map->getWidth(); j++)
        {
            currentCell = map->getCell(j,i,1);
            if (currentCell.cell_value() == -1)
                msg += QString("| x |"); 
            else 
                msg += QString(" ") + QString::number(currentCell.cell_value()) + QString(" ");
        }     
        qDebug() << msg;
        msg = "";
    }
}