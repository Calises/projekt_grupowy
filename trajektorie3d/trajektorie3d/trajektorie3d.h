#ifndef TRAJEKTORIE3D_H
#define TRAJEKTORIE3D_H

#include <QMainWindow>
#include <QWidget>

#include "ui_Trajektorie3d.h"
#include "ogrewidget.h"
#include "Map.h"
#include "aboutwindow.h"
#include "EditMapAdd.h"
#include "RemoveObstacle.h"

enum Metric {
    Manhattan,
    Czebyszew,
};

class Trajektorie3d : public QMainWindow
{
    Q_OBJECT

public:
    Trajektorie3d(QWidget *parent = 0);
    ~Trajektorie3d();

public slots:
    void Start();  
	void dialogIsFinished(int);

private:
    Ui::Trajektorie3dClass* ui;

	OgreWidget* ogreWidget;
	void loadMap();

    Map* map = NULL;

    void saveMap();
	void showEditMap(std::string, CellState);
	void removeObstacle();
    void StartAlg_Propagacja(Metric metric);
    void propagacjaFaliManhattan();
    void propagacjaFaliCzebyszew();     
    void przekaz(Metric metric, Cell endCell, int lengthTrace);
    void searchTrace(Cell endCell, int lengthTrace);
    void searchTraceCzebyszew(Cell endCell, int lengthTrace);
    void rysuj();
    AboutWindow* aboutWindow;
};

#endif // TRAJEKTORIE3D_H
