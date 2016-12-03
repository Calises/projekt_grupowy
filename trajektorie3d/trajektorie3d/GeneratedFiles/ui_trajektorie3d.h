/********************************************************************************
** Form generated from reading UI file 'trajektorie3d.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRAJEKTORIE3D_H
#define UI_TRAJEKTORIE3D_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_trajektorie3dClass
{
public:
    QAction *actionZamknij;
    QAction *actionOtw_rz_map;
    QAction *actionZapisz_map;
    QAction *actionNowa_mapa;
    QAction *actionO_programie;
    QWidget *centralWidget;
    QGridLayout *centralLayout;
    QWidget *dummyWidget;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QGroupBox *mapEditBox;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *d2Button;
    QPushButton *d3Button;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QGroupBox *algorithmBox;
    QGroupBox *computingBox;
    QMenuBar *menuBar;
    QMenu *menuPlik;
    QMenu *menuPomoc;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *trajektorie3dClass)
    {
        if (trajektorie3dClass->objectName().isEmpty())
            trajektorie3dClass->setObjectName(QStringLiteral("trajektorie3dClass"));
        trajektorie3dClass->setEnabled(true);
        trajektorie3dClass->resize(876, 531);
        actionZamknij = new QAction(trajektorie3dClass);
        actionZamknij->setObjectName(QStringLiteral("actionZamknij"));
        actionOtw_rz_map = new QAction(trajektorie3dClass);
        actionOtw_rz_map->setObjectName(QStringLiteral("actionOtw_rz_map"));
        actionZapisz_map = new QAction(trajektorie3dClass);
        actionZapisz_map->setObjectName(QStringLiteral("actionZapisz_map"));
        actionNowa_mapa = new QAction(trajektorie3dClass);
        actionNowa_mapa->setObjectName(QStringLiteral("actionNowa_mapa"));
        actionO_programie = new QAction(trajektorie3dClass);
        actionO_programie->setObjectName(QStringLiteral("actionO_programie"));
        centralWidget = new QWidget(trajektorie3dClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralLayout = new QGridLayout(centralWidget);
        centralLayout->setSpacing(6);
        centralLayout->setContentsMargins(11, 11, 11, 11);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        dummyWidget = new QWidget(centralWidget);
        dummyWidget->setObjectName(QStringLiteral("dummyWidget"));
        dummyWidget->setMinimumSize(QSize(640, 480));
        dummyWidget->setMaximumSize(QSize(640, 480));

        centralLayout->addWidget(dummyWidget, 0, 0, 1, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mapEditBox = new QGroupBox(frame);
        mapEditBox->setObjectName(QStringLiteral("mapEditBox"));
        mapEditBox->setMinimumSize(QSize(0, 100));
        gridLayout = new QGridLayout(mapEditBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        spinBox = new QSpinBox(mapEditBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(false);

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        label_2 = new QLabel(mapEditBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        pushButton = new QPushButton(mapEditBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 1, 1, 1);

        pushButton_2 = new QPushButton(mapEditBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 3, 0, 1, 1);

        d2Button = new QPushButton(mapEditBox);
        d2Button->setObjectName(QStringLiteral("d2Button"));

        gridLayout->addWidget(d2Button, 0, 0, 1, 1);

        d3Button = new QPushButton(mapEditBox);
        d3Button->setObjectName(QStringLiteral("d3Button"));

        gridLayout->addWidget(d3Button, 0, 1, 1, 1);

        label = new QLabel(mapEditBox);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setTextFormat(Qt::AutoText);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboBox = new QComboBox(mapEditBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(false);

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(mapEditBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 4, 1, 1, 1);

        pushButton_4 = new QPushButton(mapEditBox);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 4, 0, 1, 1);


        verticalLayout->addWidget(mapEditBox);

        algorithmBox = new QGroupBox(frame);
        algorithmBox->setObjectName(QStringLiteral("algorithmBox"));
        algorithmBox->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(algorithmBox);

        computingBox = new QGroupBox(frame);
        computingBox->setObjectName(QStringLiteral("computingBox"));
        computingBox->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(computingBox);


        centralLayout->addWidget(frame, 0, 2, 1, 1);

        trajektorie3dClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(trajektorie3dClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 876, 21));
        menuPlik = new QMenu(menuBar);
        menuPlik->setObjectName(QStringLiteral("menuPlik"));
        menuPomoc = new QMenu(menuBar);
        menuPomoc->setObjectName(QStringLiteral("menuPomoc"));
        trajektorie3dClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(trajektorie3dClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        trajektorie3dClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuPlik->menuAction());
        menuBar->addAction(menuPomoc->menuAction());
        menuPlik->addAction(actionOtw_rz_map);
        menuPlik->addAction(actionZapisz_map);
        menuPlik->addAction(actionNowa_mapa);
        menuPlik->addSeparator();
        menuPlik->addAction(actionZamknij);
        menuPomoc->addAction(actionO_programie);

        retranslateUi(trajektorie3dClass);

        QMetaObject::connectSlotsByName(trajektorie3dClass);
    } // setupUi

    void retranslateUi(QMainWindow *trajektorie3dClass)
    {
        trajektorie3dClass->setWindowTitle(QApplication::translate("trajektorie3dClass", "trajektorie3d", 0));
        actionZamknij->setText(QApplication::translate("trajektorie3dClass", "Zamknij", 0));
        actionOtw_rz_map->setText(QApplication::translate("trajektorie3dClass", "Otw\303\263rz map\304\231", 0));
        actionZapisz_map->setText(QApplication::translate("trajektorie3dClass", "Zapisz map\304\231", 0));
        actionNowa_mapa->setText(QApplication::translate("trajektorie3dClass", "Nowa mapa", 0));
        actionO_programie->setText(QApplication::translate("trajektorie3dClass", "O programie", 0));
        mapEditBox->setTitle(QApplication::translate("trajektorie3dClass", "Edycja mapy", 0));
        label_2->setText(QApplication::translate("trajektorie3dClass", "Obiekt do dodania:", 0));
        pushButton->setText(QApplication::translate("trajektorie3dClass", "Dodawaj", 0));
        pushButton_2->setText(QApplication::translate("trajektorie3dClass", "Usuwaj", 0));
        d2Button->setText(QApplication::translate("trajektorie3dClass", "Widok 2D", 0));
        d3Button->setText(QApplication::translate("trajektorie3dClass", "Widok 3D", 0));
        label->setText(QApplication::translate("trajektorie3dClass", "Wybierz poziom:", 0));
        pushButton_3->setText(QApplication::translate("trajektorie3dClass", "Umie\305\233\304\207 CEL", 0));
        pushButton_4->setText(QApplication::translate("trajektorie3dClass", "Umie\305\233\304\207 START", 0));
        algorithmBox->setTitle(QApplication::translate("trajektorie3dClass", "Ustawienia algorytmu", 0));
        computingBox->setTitle(QApplication::translate("trajektorie3dClass", "Liczenie trajektorii", 0));
        menuPlik->setTitle(QApplication::translate("trajektorie3dClass", "Plik", 0));
        menuPomoc->setTitle(QApplication::translate("trajektorie3dClass", "Pomoc", 0));
    } // retranslateUi

};

namespace Ui {
    class trajektorie3dClass: public Ui_trajektorie3dClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAJEKTORIE3D_H
