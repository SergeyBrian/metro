#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QDebug>

#include "navigator/Navigator.h"
#include "stationbutton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Navigator *navigator;
    StationList *stationList;
    std::vector<StationButton> stationButtons = {
        StationButton(PARNAS, 260, 40),
        StationButton(PROSPEKT_PROSVESHCHENIYA, 260, 70),
        StationButton(OZERKI, 260, 95),
        StationButton(UDELNAYA, 260, 125),
        StationButton(PIONERSKAYA, 260, 155),
        StationButton(CHYORNAYA_RECHKA, 260, 180),
        StationButton(PETROGRADSKAYA, 260, 267),
        StationButton(GORKOVSKAYA, 260, 310),
        StationButton(NEVSKIY_PROSPEKT, 260, 370),
        StationButton(GOSTINY_DVOR, 280, 390),
        StationButton(SENNAYA_PLOSHCHAD, 260, 430),
        StationButton(TEKHNOLOGICHESKIY_INSTITUT_BLUE, 260, 555),
        StationButton(FRUNZENSKAYA, 260, 590),
        StationButton(MOSKOVSKIE_VOROTA, 260, 615),
        StationButton(ELEKTROSILA, 260, 642),
        StationButton(PARK_POBEDY, 260, 670),
        StationButton(MOSKOVSKAYA, 260, 700),
        StationButton(ZVYOZDNAYA, 260, 773),
        StationButton(KUPCHINO, 260, 800),
    };
    std::vector<QPushButton *> stationButtonPtrs;
};
#endif // MAINWINDOW_H
