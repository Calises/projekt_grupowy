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

//private:
    Ui::trajektorie3dClass ui;
};

#endif // TRAJEKTORIE3D_H
