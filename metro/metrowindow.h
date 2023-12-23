#ifndef METROWINDOW_H
#define METROWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "generatedialog.h"

#include "metro/Metro.h"

namespace Ui {
    class MetroWindow;
}

class MetroWindow : public QMainWindow {
Q_OBJECT

public:
    MetroWindow(metro::Metro *metro, QWidget *parent = nullptr);

    ~MetroWindow();

private slots:

    void slotAlarmTimer();

    void on_actionNew_triggered();

    void on_actionRegenerate_triggered();

    void on_actionShow_station_tags_triggered(bool checked);

    void on_actionShow_branch_tags_triggered(bool checked);

    void on_actionShow_center_marker_triggered(bool checked);

    void on_actionShow_branch_traces_triggered(bool checked);

private:
    Ui::MetroWindow *ui;
    QGraphicsView *gView;
    QGraphicsScene *scene;
    metro::Metro *metro;

    void drawScheme();

    void resizeEvent(QResizeEvent *event) override;

    void redraw();

    double getRealX(int x);

    double getRealY(int y);

    bool showBranchTags;
    bool showStationTags;
    bool showCenterMarker;
    bool showBranchTrace;
};

#endif // METROWINDOW_H