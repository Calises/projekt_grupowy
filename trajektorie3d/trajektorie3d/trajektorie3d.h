#ifndef TRAJEKTORIE3D_H
#define TRAJEKTORIE3D_H

#include <QMainWindow>
#include <QWidget>

#include "ui_Trajektorie3d.h"
#include "ogrewidget.h"
#include "Map.h"
#include "aboutwindow.h"

class Trajektorie3d : public QMainWindow
{
    Q_OBJECT

public:
    Trajektorie3d(QWidget *parent = 0);
    ~Trajektorie3d();

public slots:
    void startAlgorithm();

private:
    Ui::Trajektorie3dClass* ui;

	OgreWidget* ogreWidget;
	void loadMap();

    Map* map = NULL;

    void saveMap();

    AboutWindow* aboutWindow;
};

#endif // TRAJEKTORIE3D_H
