/********************************************************************************
** Form generated from reading UI file 'trajektorie3d.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
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
#include <QtWidgets/QRadioButton>
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
    QGroupBox *groupBox_Metric;
    QRadioButton *radioButton_Manhattan;
    QRadioButton *radioButton_Czebyszew;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBox_przeszkoda;
    QComboBox *comboBox_algorithm;
    QGroupBox *computingBox;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_lengthEuclides;
    QLabel *label_lengthWay;
    QLabel *label_numOperations;
    QLabel *label_5;
    QPushButton *button_start;
    QRadioButton *radioButton_Wisualisation;
    QWidget *dummyWidget;
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
        groupBox_Metric = new QGroupBox(algorithmBox);
        groupBox_Metric->setObjectName(QStringLiteral("groupBox_Metric"));
        groupBox_Metric->setGeometry(QRect(10, 40, 171, 61));
        radioButton_Manhattan = new QRadioButton(groupBox_Metric);
        radioButton_Manhattan->setObjectName(QStringLiteral("radioButton_Manhattan"));
        radioButton_Manhattan->setGeometry(QRect(10, 20, 82, 17));
        radioButton_Czebyszew = new QRadioButton(groupBox_Metric);
        radioButton_Czebyszew->setObjectName(QStringLiteral("radioButton_Czebyszew"));
        radioButton_Czebyszew->setGeometry(QRect(10, 40, 82, 17));
        label_3 = new QLabel(algorithmBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 20, 47, 13));
        label_4 = new QLabel(algorithmBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 110, 121, 16));
        spinBox_przeszkoda = new QSpinBox(algorithmBox);
        spinBox_przeszkoda->setObjectName(QStringLiteral("spinBox_przeszkoda"));
        spinBox_przeszkoda->setGeometry(QRect(140, 110, 42, 22));
        comboBox_algorithm = new QComboBox(algorithmBox);
        comboBox_algorithm->setObjectName(QStringLiteral("comboBox_algorithm"));
        comboBox_algorithm->setGeometry(QRect(70, 20, 111, 22));

        verticalLayout->addWidget(algorithmBox);

        computingBox = new QGroupBox(frame);
        computingBox->setObjectName(QStringLiteral("computingBox"));
        computingBox->setMinimumSize(QSize(0, 100));
        label_6 = new QLabel(computingBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 70, 81, 16));
        label_7 = new QLabel(computingBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 90, 81, 16));
        label_lengthEuclides = new QLabel(computingBox);
        label_lengthEuclides->setObjectName(QStringLiteral("label_lengthEuclides"));
        label_lengthEuclides->setGeometry(QRect(110, 50, 51, 16));
        label_lengthWay = new QLabel(computingBox);
        label_lengthWay->setObjectName(QStringLiteral("label_lengthWay"));
        label_lengthWay->setGeometry(QRect(110, 70, 51, 16));
        label_numOperations = new QLabel(computingBox);
        label_numOperations->setObjectName(QStringLiteral("label_numOperations"));
        label_numOperations->setGeometry(QRect(110, 90, 51, 16));
        label_5 = new QLabel(computingBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 50, 81, 16));
        button_start = new QPushButton(computingBox);
        button_start->setObjectName(QStringLiteral("button_start"));
        button_start->setGeometry(QRect(20, 20, 81, 23));
        radioButton_Wisualisation = new QRadioButton(computingBox);
        radioButton_Wisualisation->setObjectName(QStringLiteral("radioButton_Wisualisation"));
        radioButton_Wisualisation->setGeometry(QRect(110, 20, 81, 21));

        verticalLayout->addWidget(computingBox);


        centralLayout->addWidget(frame, 0, 2, 1, 1);

        dummyWidget = new QWidget(centralWidget);
        dummyWidget->setObjectName(QStringLiteral("dummyWidget"));
        dummyWidget->setMinimumSize(QSize(640, 480));
        dummyWidget->setMaximumSize(QSize(640, 480));

        centralLayout->addWidget(dummyWidget, 0, 0, 1, 1);

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
        trajektorie3dClass->setWindowTitle(QApplication::translate("trajektorie3dClass", "trajektorie3d", Q_NULLPTR));
        actionZamknij->setText(QApplication::translate("trajektorie3dClass", "Zamknij", Q_NULLPTR));
        actionOtw_rz_map->setText(QApplication::translate("trajektorie3dClass", "Otw\303\263rz map\304\231", Q_NULLPTR));
        actionZapisz_map->setText(QApplication::translate("trajektorie3dClass", "Zapisz map\304\231", Q_NULLPTR));
        actionNowa_mapa->setText(QApplication::translate("trajektorie3dClass", "Nowa mapa", Q_NULLPTR));
        actionO_programie->setText(QApplication::translate("trajektorie3dClass", "O programie", Q_NULLPTR));
        mapEditBox->setTitle(QApplication::translate("trajektorie3dClass", "Edycja mapy", Q_NULLPTR));
        label_2->setText(QApplication::translate("trajektorie3dClass", "Obiekt do dodania:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("trajektorie3dClass", "Dodawaj", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("trajektorie3dClass", "Usuwaj", Q_NULLPTR));
        d2Button->setText(QApplication::translate("trajektorie3dClass", "Widok 2D", Q_NULLPTR));
        d3Button->setText(QApplication::translate("trajektorie3dClass", "Widok 3D", Q_NULLPTR));
        label->setText(QApplication::translate("trajektorie3dClass", "Wybierz poziom:", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("trajektorie3dClass", "Umie\305\233\304\207 CEL", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("trajektorie3dClass", "Umie\305\233\304\207 START", Q_NULLPTR));
        algorithmBox->setTitle(QApplication::translate("trajektorie3dClass", "Ustawienia algorytmu", Q_NULLPTR));
        groupBox_Metric->setTitle(QApplication::translate("trajektorie3dClass", "Metryka", Q_NULLPTR));
        radioButton_Manhattan->setText(QApplication::translate("trajektorie3dClass", "Manhattan", Q_NULLPTR));
        radioButton_Czebyszew->setText(QApplication::translate("trajektorie3dClass", "Czebyszew", Q_NULLPTR));
        label_3->setText(QApplication::translate("trajektorie3dClass", "Algorytm", Q_NULLPTR));
        label_4->setText(QApplication::translate("trajektorie3dClass", "Poszerz przeszkody o: ", Q_NULLPTR));
        comboBox_algorithm->setCurrentText(QString());
        computingBox->setTitle(QApplication::translate("trajektorie3dClass", "Liczenie trajektorii", Q_NULLPTR));
        label_6->setText(QApplication::translate("trajektorie3dClass", "D\305\202. drogi:", Q_NULLPTR));
        label_7->setText(QApplication::translate("trajektorie3dClass", "Ilo\305\233\304\207 operacji:", Q_NULLPTR));
        label_lengthEuclides->setText(QApplication::translate("trajektorie3dClass", "0", Q_NULLPTR));
        label_lengthWay->setText(QApplication::translate("trajektorie3dClass", "0", Q_NULLPTR));
        label_numOperations->setText(QApplication::translate("trajektorie3dClass", "0", Q_NULLPTR));
        label_5->setText(QApplication::translate("trajektorie3dClass", "D\305\202. Euklidesowa:", Q_NULLPTR));
        button_start->setText(QApplication::translate("trajektorie3dClass", "START", Q_NULLPTR));
        radioButton_Wisualisation->setText(QApplication::translate("trajektorie3dClass", "Wizualizacja", Q_NULLPTR));
        menuPlik->setTitle(QApplication::translate("trajektorie3dClass", "Plik", Q_NULLPTR));
        menuPomoc->setTitle(QApplication::translate("trajektorie3dClass", "Pomoc", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class trajektorie3dClass: public Ui_trajektorie3dClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRAJEKTORIE3D_H
