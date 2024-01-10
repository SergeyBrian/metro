#ifndef BENCHMARKVIEWER_H
#define BENCHMARKVIEWER_H

#include <QMainWindow>

#include "lib/qcustomplot.h"

#include "metro/tests/Tests.h"

namespace Ui {
    class BenchmarkViewer;
}

class BenchmarkViewer : public QMainWindow {
Q_OBJECT

public:
    explicit BenchmarkViewer(metro::Benchmark *benchmark, QWidget *parent = nullptr);

    ~BenchmarkViewer();

private:
    Ui::BenchmarkViewer *ui;
    metro::Benchmark *benchmark;
};

#endif // BENCHMARKVIEWER_H
