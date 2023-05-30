#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap subwayMapPixmap(":/image/img/bg.jpg");
    QLabel* subwayMapLabel = new QLabel(this);
    subwayMapLabel->setPixmap(subwayMapPixmap);
    subwayMapLabel->setScaledContents(true);
    setCentralWidget(subwayMapLabel);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    QSize imageSize = subwayMapPixmap.size();
    int windowWidth = imageSize.width() + 16;
    int windowHeight = imageSize.height() + 16;
    setFixedSize(windowWidth, windowHeight);

    stationList = new StationList();
    navigator = new Navigator(stationList);

    for (int i = 0; i < this->stationButtons.size(); i++) {
        StationButton buttonInfo = stationButtons[i];
        QPushButton *button = new QPushButton("", subwayMapLabel);
        button->setGeometry(buttonInfo.coords.first, buttonInfo.coords.second, 20, 20);
//      button->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        this->stationButtonPtrs.push_back(button);
        connect(button, &QPushButton::clicked, [=](){
            std::string station_name = stationList->getStation(buttonInfo.id)->name;
            qDebug() << station_name.c_str() << "\n";
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stationList;
    delete navigator;
}

