#include "metrowindow.h"
#include "ui_metrowindow.h"

#define MARKER_WIDTH 10

MetroWindow::MetroWindow(metro::Metro *metro, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MetroWindow) {
    showBranchTags = true;
    showStationTags = false;
    showCenterMarker = false;
    showBranchTrace = false;
    this->filename_base = "* New metro";

    ui->setupUi(this);
    this->metro = metro;
    gView = ui->graphicsView;
    gView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene = new QGraphicsScene();
    gView->setScene(scene);
    showRecentFilesMenu(ui->menuFile, this);
    redraw();
}

MetroWindow::~MetroWindow() {
    delete ui;
}

void MetroWindow::redraw() {
    this->setWindowTitle("Metro viewer: " + filename_base);
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
        auto *stationMarker = new StationEllipse({x - MARKER_WIDTH / 2,
                                                  y - MARKER_WIDTH / 2,
                                                  MARKER_WIDTH, MARKER_WIDTH});
        stationMarker->Station(station);
        connect(stationMarker->Helper(), &GraphicsItemHelper::itemClicked, this, &MetroWindow::stationPressCallback);
        stationMarker->addToScene(scene);
        if (selectedStations[station->id]) stationMarker->toggleSelect();
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

void MetroWindow::stationPressCallback(QGraphicsItem *stationMarker) {
    auto _stationMarker = dynamic_cast<StationEllipse *>(stationMarker);
    qDebug() << "Station " << QString::fromStdString(_stationMarker->Station()->name) << " pressed";
    bool selected = _stationMarker->toggleSelect();
    bool routeStatus;
    if (selected) routeStatus = metro->addStationToRoute(_stationMarker->Station());
    else routeStatus = metro->removeStationFromRoute(_stationMarker->Station());
    selectedStations[_stationMarker->Station()->id] = selected;
    drawRoute();
    printf("Building route for targets:\n");
    for (const auto &station: metro->route.getTargetStations()) {
        printf("%s -> ", station->name.c_str());
    }
    printf("\n");
    printf("Result:\n");
    for (const auto &station: metro->route.getRoute()) {
        printf("%s -> ", station->name.c_str());
    }
    printf("\n");
}


void MetroWindow::on_actionSave_triggered() {
    if (filename.isEmpty() && !selectFileSave(&filename, &filename_base)) return;
    metro::saveToFile(filename.toStdString(), metro);
    redraw();
}


void MetroWindow::on_actionOpen_triggered() {
    if (!selectFileOpen(&filename, &filename_base)) return;
    try {
        metro::loadFromFile(filename.toStdString(), metro);
        selectedStations.clear();
        redraw();
        addToRecentFiles(filename);
    } catch (const metro::FilesysException &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", "Error reading file");
    }
}

MetroWindow::MetroWindow(const QString &filename, const QString &filename_base, QWidget *parent) : MetroWindow(
        new metro::Metro(), parent) {
    this->filename_base = filename_base;
    metro::loadFromFile(filename.toStdString(), metro);
}


void MetroWindow::on_actionSave_as_triggered() {
    if (!selectFileSave(&filename, &filename_base)) return;
    metro::saveToFile(filename.toStdString(), metro);
    redraw();
    addToRecentFiles(filename);
}

void MetroWindow::on_actionOpenRecentTriggered() {
    auto action = dynamic_cast<QAction *>(QObject::sender());
    filename = action->data().value<QString>();
    metro::loadFromFile(filename.toStdString(), metro);
    selectedStations.clear();
    redraw();
    addToRecentFiles(filename);
}

void MetroWindow::drawRoute() {
    for (const auto &line: routeLines) {
        scene->removeItem(line);
    }
    routeLines.clear();

    std::vector<metro::Station *> route = metro->route.getRoute();
    if (route.size() < 2) return;
    for (int i = 0; i < route.size() - 1; i++) {
        metro::Station *cur = route.at(i);
        metro::Station *next = route.at(i + 1);
        QGraphicsLineItem *line = scene->addLine(getRealX(cur->pos.x), getRealY(cur->pos.y),
                                                 getRealX(next->pos.x), getRealY(next->pos.y));
        auto pen = QPen(Qt::red);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(5);
        line->setPen(pen);
        routeLines.push_back(line);
    }
}

