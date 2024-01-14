#ifndef BENCHMARKDIALOG_H
#define BENCHMARKDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QProgressBar>
#include <QCheckBox>
#include <QVBoxLayout>

#include "metro/tests/Tests.h"

#include "benchmarkworker.h"
#include "benchmarkviewer.h"

namespace Ui {
    class BenchmarkDialog;
}

class BenchmarkDialog : public QDialog {
Q_OBJECT

    QThread workerThread;

public:
    explicit BenchmarkDialog(QWidget *parent = nullptr);

    ~BenchmarkDialog();


private:
    Ui::BenchmarkDialog *ui;

    void accept() override;

    void reject() override;

    void registerCallback(QProgressBar *pb, metro::CallbackType type, metro::Benchmark *benchmark);

    metro::Benchmark *benchmark;

    BenchmarkWorker *worker;

    BenchmarkUpdateEmitter *emitter;

    QVBoxLayout *checkboxLayout;

    bool stop;

//    void startWorker();

signals:

    void runBenchmark(bool *s);

public slots:

    void publicCallback(int value, void *progresBar);

    void onFinish();
};

#endif // BENCHMARKDIALOG_H
