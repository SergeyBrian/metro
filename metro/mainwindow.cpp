#include "mainwindow.h"
#include "./ui_mainwindow.h"


void MainWindow::HandleStationButtonPress(station_id id) {
    qDebug() << stationList->getStation(id)->name.c_str() << "\n";
    switch (navState) {
    case AWAIT_BEGIN:
        HideAllButtons();
        ShowButton(id);
        begin = id;
        navState = AWAIT_END;
        break;
    case AWAIT_END:
        Route *route = navigator->findShortestRoute(begin, id);
        std::string routeString = "";
        for (int i  = 0; i < route->path.size(); i++) {
            ShowButton(route->path[i]);
            routeString += stationList->getStation(route->path[i])->name;
            if (i < route->path.size() - 1) routeString += " -> ";
        }
        qDebug() << routeString.c_str();
        navigator->forgetRoutes();
        navState = AWAIT_BEGIN;
        break;
    }
}

void MainWindow::HideAllButtons() {
    for (auto const& button : stationButtonPtrs) {
        ShowButton(button.first, 0);
    }
}

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
    navState = AWAIT_BEGIN;

    stationList = new StationList();
    navigator = new Navigator(stationList);

    for (int i = 0; i < this->stationButtons.size(); i++) {
        StationButton buttonInfo = stationButtons[i];
        QPushButton *button = new QPushButton("", subwayMapLabel);
        button->setGeometry(buttonInfo.coords.first, buttonInfo.coords.second, 20, 20);
        button->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        this->stationButtonPtrs.insert(std::make_pair(buttonInfo.id, button));
        connect(button, &QPushButton::clicked, [=](){
            HandleStationButtonPress(buttonInfo.id);
        });
    }
}

void MainWindow::ShowButton(station_id id, bool show) {
    QPushButton *button = stationButtonPtrs.find(id)->second;
    if (show) {
        button->setStyleSheet("QPushButton { background-color: #ffe600; }");
    } else {
        button->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stationList;
    delete navigator;
}

