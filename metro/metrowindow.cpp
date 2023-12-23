#include "metrowindow.h"
#include "ui_metrowindow.h"

#define MARKER_WIDTH 10

MetroWindow::MetroWindow(metro::Metro *metro, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MetroWindow) {
    showBranchTags = true;
    showStationTags = false;
    showCenterMarker = false;
    showBranchTrace = false;

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
    for (int i = 0; i < metro->stations.size(); i++) {
        metro::Station *station = &metro->stations[i];
        // TODO: Придумать, что делать с станциями, которые не привязались ни к какой ветке и убрать этот костыль
        if (station->branch_id == -1) continue;
        double x = getRealX(station->pos.x);
        double y = getRealY(station->pos.y);
        auto *stationMarker = new StationEllipse();
        stationMarker->setRect({x - MARKER_WIDTH / 2,
                                y - MARKER_WIDTH / 2,
                                MARKER_WIDTH, MARKER_WIDTH});
        stationMarker->Station(station);
        connect(stationMarker->helper, &GraphicsItemHelper::itemClicked, this, &MetroWindow::test_callback);
        scene->addItem(stationMarker);
        metro::Branch branch = metro->getBranchByStation(*station);
        metro::Color color = branch.color;
        QColor branchQColor = QColor::fromRgb(color.rgb.r, color.rgb.g, color.rgb.b);
        stationMarker->setBrush(branchQColor);
        if (showStationTags) {
            QGraphicsTextItem *text = scene->addText(QString::fromStdString(station->name));
            text->setPos(x, y);
        }
        for (const auto &connection: station->connections) {
            QGraphicsLineItem *connectionLine = scene->addLine(x, y,
                                                               getRealX(connection->pos.x),
                                                               getRealY(connection->pos.y));
            connectionLine->setPen(QColor::fromRgb(color.rgb.r, color.rgb.g, color.rgb.b));
        }
        if (branch.begin->id == station->id) {
            if (showBranchTags) {
                QGraphicsTextItem *branchName = scene->addText(
                        "Branch #" + QString::fromStdString(std::to_string(branch.id)));
                branchName->setPos(x, y - 20);
                branchName->setDefaultTextColor(branchQColor);
            }
        }
    }
    if (showCenterMarker) {
        QGraphicsRectItem *debug_centerMarker = scene->addRect(getRealX(metro->center.x),
                                                               getRealY(metro->center.y),
                                                               MARKER_WIDTH, MARKER_WIDTH);
        debug_centerMarker->setBrush(Qt::red);
    }
    if (showBranchTrace) {
        for (const auto &[id, branch]: metro->branches) {
            QGraphicsLineItem *line = scene->addLine(getRealX(branch.begin->pos.x), getRealY(branch.begin->pos.y),
                                                     getRealX(branch.end->pos.x), getRealY(branch.end->pos.y));
            auto pen = QPen(QColor::fromRgb(branch.color.rgb.r, branch.color.rgb.g, branch.color.rgb.b));
            pen.setStyle(Qt::DashLine);
            line->setPen(pen);
        }
    }
}

double MetroWindow::getRealX(int x) {
    return (gView->width() - MARKER_WIDTH * 2) * (static_cast<double>(x) / 100);
}

double MetroWindow::getRealY(int y) {
    return (gView->height() - MARKER_WIDTH * 2) * (static_cast<double>(y) / 100);
}

void MetroWindow::on_actionNew_triggered() {
    auto genDialog = new GenerateDialog(this);
    if (!genDialog->exec()) return;
    metro->generate(genDialog->getParams());
    redraw();
}


void MetroWindow::on_actionRegenerate_triggered() {
    metro->generate(metro->old_params);
    redraw();
}


void MetroWindow::on_actionShow_station_tags_triggered(bool checked) {
    showStationTags = checked;
    redraw();
}


void MetroWindow::on_actionShow_branch_tags_triggered(bool checked) {
    showBranchTags = checked;
    redraw();
}


void MetroWindow::on_actionShow_center_marker_triggered(bool checked) {
    showCenterMarker = checked;
    redraw();
}


void MetroWindow::on_actionShow_branch_traces_triggered(bool checked) {
    showBranchTrace = checked;
    redraw();
}

void MetroWindow::test_callback(QGraphicsItem *stationMarker) {
    auto _stationMarker = dynamic_cast<StationEllipse *>(stationMarker);
    qDebug() << "Station " << QString::fromStdString(_stationMarker->Station()->name) << " pressed";
}

