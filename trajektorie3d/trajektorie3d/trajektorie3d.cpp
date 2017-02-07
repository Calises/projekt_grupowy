#include "Trajektorie3d.h"
#include "Map.h"
#include "utils.h"

#include <QCoreApplication>
#include <QSettings>
#include <QFileDialog>
#include <qmessagebox.h>

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

enum Metric {
    Manhattan,
    Czebyszew,
};

void Trajektorie3d::Start()
{
    Metric metric;
    if (ui->radioButton_Manhattan->isChecked())
    {
        ui->label_numOperations->setText("Manhat");
        metric = Manhattan;
    }
       
    else if (ui->radioButton_Czebyszew->isChecked())
    {
        ui->label_numOperations->setText("czeb");
        metric = Czebyszew;
    }
        
    else
        QMessageBox::warning(this,"Uwaga", "Zanacz matryke!");



    if (ui->comboBox_algorithm->currentIndex() == 0)
    {
        //ui->label_numOperations->setText("propagacja fali");
        //StartAlg_Propagacja();
    }     
    else if (ui->comboBox_algorithm->currentIndex() == 1)
    {
        //ui->label_numOperations->setText("drugi algorytm");
        //StartAlg_SztucznePotencjaly
    }      
}

void Trajektorie3d::StartAlg_Propagacja()
{
    if (!map)
        return;

    // change the text
    ui->button_start->setText("GO");

    std::cout << "Hej! ";

    QString a = QString::number(map->returnValue(1, 1, 1));
    //ui->label_numOperations->setText(a);

    map->show();

    //tymczasowe wywo³anie, domyœlnie zamiast map wrzuciæ wynik algorytmu
    //ogreWidget->redrawScene(map);
}