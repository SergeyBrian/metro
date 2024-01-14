#include "benchmarkviewer.h"
#include "ui_benchmarkviewer.h"

BenchmarkViewer::BenchmarkViewer(metro::Benchmark *benchmark, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::BenchmarkViewer) {
    ui->setupUi(this);
    this->benchmark = benchmark;

    auto layout = new QVBoxLayout(this);
    auto plot = new QCustomPlot(this);
    layout->addWidget(plot);
    ui->centralwidget->setLayout(layout);
    plot->xAxis->setLabel("Stations count");
    plot->xAxis->setRange(plot->xAxis->range().lower, benchmark->getMaxParams().stations_count);
    plot->yAxis->setLabel("Search time");
    plot->legend->setVisible(true);
    double max_time = -1;
    int reduce = 0;
    for (int i = 0; i < metro::ROUTE_SEARCH_METHOD_COUNT; i++) {
        QVector<double> y;
        QVector<double> x;
        std::vector<metro::BenchmarkResult> results;
        try {
            results = benchmark->getResults(static_cast<metro::RouteSearchMethod>(i));
        } catch (const std::out_of_range &e) {
            reduce++;
            continue;
        }
        for (auto &result: results) {
            double time = result.time;
            if (time > max_time) max_time = time;
            y.push_back(time);
            x.push_back(result.params.stations_count);
        }
        plot->addGraph();
        plot->graph(i - reduce)->addData(x, y);
        plot->graph(i - reduce)->setName(QString::fromStdString(metro::search_method_name[i]));
        metro::Color color = metro::getColor(static_cast<metro::ColorID>(i - reduce));
        plot->graph(i - reduce)->setPen(QColor::fromRgb(color.rgb.r, color.rgb.g, color.rgb.b));
    }
    plot->yAxis->setRange(plot->yAxis->range().lower, max_time);
//    plot->yAxis->setScaleType(QCPAxis::stLogarithmic);
    showMaximized();
}

BenchmarkViewer::~BenchmarkViewer() {
    delete ui;
}
