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
};

#endif // METROWINDOW_H
