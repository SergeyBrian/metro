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
        StationButton(DEVYATKINO, 360, 110),
        StationButton(GRAZHDANSKIY_PROSPEKT, 360, 140),
        StationButton(AKADEMICHESKAYA, 360, 170),
        StationButton(POLITEKHNICHESKAYA, 360, 195),
        StationButton(PLOSHCHAD_MUZHESTVA, 360, 225),
        StationButton(LESNAYA, 360, 250),
        StationButton(VYBORGSKAYA, 360, 280),
        StationButton(PLOSHCHAD_LENINA, 360, 310),
        StationButton(CHERNYSHEVSKAYA, 360, 345),
        StationButton(PLOSHCHAD_VOSSTANIYA, 360, 375),
        StationButton(VLADIMIRSKAYA, 360, 465),
        StationButton(PUSHKINSKAYA, 325, 510),
        StationButton(TEKHNOLOGICHESKIY_INSTITUT_RED, 242, 545),
        StationButton(BALTIYSKAYA, 165, 600),
        StationButton(NARVSKAYA, 160, 640),
        StationButton(KIROVSKIY_ZAVOD, 160, 665),
        StationButton(AVTOVO, 160, 690),
        StationButton(LENINSKIY_PROSPEKT, 160, 745),
        StationButton(PROSPEKT_VETERANOV, 160, 775),
        StationButton(KOMENDANTSKIY_PROSPEKT, 133, 123),
        StationButton(STARAYA_DEREVNYA, 133, 153),
        StationButton(KRESTOVSKIY_OSTROV, 135, 245),
        StationButton(CHKALOVSKAYA, 150, 290),
        StationButton(SPORTIVNAYA, 175, 330),
        StationButton(ADMIRALTEYSKAYA, 233, 410),
        StationButton(SADOVAYA, 270, 465),
        StationButton(ZVENIGORODSKAYA, 300, 500),
        StationButton(OBVODNYY_KANAL, 360, 655),
        StationButton(VOLKOVSKAYA, 360, 685),
        StationButton(BUKHARESTSKAYA, 360, 715),
        StationButton(MEZHDUNARODNAYA, 360, 745),
        StationButton(PROSPECT_SLAVY, 360, 775),
        StationButton(DUNAYSKAYA, 360, 805),
        StationButton(SHUSHARY, 360, 835),
        StationButton(RYBATSKOYE, 545, 645),
        StationButton(OBUHOVO, 520, 615),
        StationButton(PROLETARSKAYA, 505, 585),
        StationButton(LOMONOSOVSKAYA, 476, 547),
        StationButton(ELIZAROVSKAYA, 460, 525),
        StationButton(PLOSHCHAD_ALEKSANDRA_NEVSKOGO_GREEN, 425, 470),
        StationButton(MAYAKOVSKAYA, 377, 407),
        StationButton(VASILEOSTROVSKAYA, 125, 385),
        StationButton(PRIMORSKAYA, 60, 350),
        StationButton(ZENIT, 10, 230),
        StationButton(BEGOVAYA, 10, 180),
        StationButton(SPASSKAYA, 278, 445),
        StationButton(DOSTOEVSKAYA, 340, 450),
        StationButton(LIGOVSKIY_PROSPEKT, 380, 447),
        StationButton(PLOSHCHAD_ALEKSANDRA_NEVSKOGO_ORANGE, 440, 448),
        StationButton(NOVOCHERKASSKAYA, 509, 490),
        StationButton(LADOZHSKAYA, 527, 513),
        StationButton(PROSPEKT_BOLSHEVIKOV, 550, 540),
        StationButton(ULITSA_DYBENKO, 580, 570),
    };
    std::vector<QPushButton *> stationButtonPtrs;
};
#endif // MAINWINDOW_H
