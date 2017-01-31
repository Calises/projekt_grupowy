#ifndef TRAJEKTORIE3D_H
#define TRAJEKTORIE3D_H

#include <QMainWindow>
#include <QWidget>
#include "ui_trajektorie3d.h"
#include "ogrewidget.h"

class trajektorie3d : public QMainWindow
{
    Q_OBJECT

public:
    trajektorie3d(QWidget *parent = 0);
    ~trajektorie3d();

public slots:
    void startAlgorithm();

private:
    Ui::trajektorie3dClass* ui;

	OgreWidget* ogreWidget;
	void chooseMapClicked();
};

#endif // TRAJEKTORIE3D_H
