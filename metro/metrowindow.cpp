#include "metrowindow.h"
#include "ui_metrowindow.h"

#define MARKER_WIDTH 10

MetroWindow::MetroWindow(metro::Metro *metro, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MetroWindow) {
    ui->setupUi(this);
    this->metro = metro;
    gView = ui->graphicsView;
    gView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene();
    gView->setScene(scene);
    redraw();
}

MetroWindow::~MetroWindow() {
    delete ui;
}

void MetroWindow::redraw() {
    auto timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    timer->start(50);
}

void MetroWindow::resizeEvent(QResizeEvent *event) {
    redraw();
}

void MetroWindow::slotAlarmTimer() {
    QRect winGeometry = this->geometry();

    gView->setGeometry(0, 0, winGeometry.width(), winGeometry.height());
    scene->setSceneRect(0, 0, winGeometry.width(), winGeometry.height());
    drawScheme();
}

void MetroWindow::drawScheme() {
    scene->clear();
    for (const auto &station: metro->stations) {
        double x = getRealX(station.pos.x);
        double y = getRealY(station.pos.y);
        QGraphicsEllipseItem *stationMarker = scene->addEllipse(x, y, MARKER_WIDTH, MARKER_WIDTH);
        metro::Color color = metro->getBranchByStation(station).color;
        stationMarker->setBrush(QColor::fromRgb(color.rgb.r, color.rgb.g, color.rgb.b));
        QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(station.branch_id)));
        text->setPos(x, y);
        for (const auto &connection: station.connections) {
            QGraphicsLineItem *connectionLine = scene->addLine(x, y,
                                                               getRealX(connection->pos.x),
                                                               getRealY(connection->pos.y));
            connectionLine->setPen(QColor::fromRgb(color.rgb.r, color.rgb.g, color.rgb.b));
        }
    }
#ifndef NDEBUG
    QGraphicsRectItem *debug_centerMarker = scene->addRect(getRealX(metro->center.x),
                                                           getRealY(metro->center.y),
                                                           MARKER_WIDTH, MARKER_WIDTH);
    debug_centerMarker->setBrush(Qt::red);
    for (const auto &[id, branch]: metro->branches) {
        QGraphicsLineItem *line = scene->addLine(getRealX(branch.begin->pos.x), getRealY(branch.begin->pos.y),
                                                 getRealX(branch.end->pos.x), getRealY(branch.end->pos.y));
        auto pen = QPen(QColor::fromRgb(branch.color.rgb.r, branch.color.rgb.g, branch.color.rgb.b));
        pen.setStyle(Qt::DashLine);
        line->setPen(pen);
    }
#endif
}

double MetroWindow::getRealX(int x) {
    return (gView->width() - MARKER_WIDTH * 2) * (static_cast<double>(x) / 100);
}

double MetroWindow::getRealY(int y) {
    return (gView->height() - MARKER_WIDTH * 2) * (static_cast<double>(y) / 100);
}
