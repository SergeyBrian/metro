#include "benchmarkdialog.h"
#include "ui_benchmarkdialog.h"

BenchmarkDialog::BenchmarkDialog(QWidget *parent)
        : QDialog(parent), ui(new Ui::BenchmarkDialog) {
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Run");
    ui->progressBar->setVisible(false);
    ui->progressBar_2->setVisible(false);
    stop = true;
    checkboxLayout = new QVBoxLayout();
    for (int i = 0; i < metro::ROUTE_SEARCH_METHOD_COUNT; i++) {
        auto checkbox = new QCheckBox(QString::fromStdString(metro::search_method_name[i]));
        checkbox->setChecked(true);
        checkboxLayout->addWidget(checkbox);
    }
    ui->formLayout_2->addRow(checkboxLayout);
    setWindowTitle("Navigator benchmark");
}

BenchmarkDialog::~BenchmarkDialog() {
    delete ui;
}

void BenchmarkDialog::accept() {
    stop = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->progressBar_2->setVisible(true);
    ui->progressBar->setValue(0);
    ui->progressBar_2->setValue(0);
    benchmark = new metro::Benchmark({.stations_count = ui->spinBox->value()});
    for (int i = 0; i < checkboxLayout->count(); i++) {
        QWidget *checkbox = checkboxLayout->itemAt(i)->widget();
        checkbox->setEnabled(false);
        if (!dynamic_cast<QCheckBox *>(checkbox)->isChecked()) {
            benchmark->disable_method(static_cast<metro::RouteSearchMethod>(i));
        }
    }
    emitter = new BenchmarkUpdateEmitter();
    worker = new BenchmarkWorker(benchmark);
    registerCallback(ui->progressBar, metro::CALLBACK_STAGE, benchmark);
    registerCallback(ui->progressBar_2, metro::CALLBACK_STATION_COUNT, benchmark);
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &BenchmarkDialog::runBenchmark, worker, &BenchmarkWorker::run);
    connect(emitter, &BenchmarkUpdateEmitter::publicCallback, this, &BenchmarkDialog::publicCallback);
    connect(worker, &BenchmarkWorker::workFinished, this, &BenchmarkDialog::onFinish);
    workerThread.start();
    emit runBenchmark(&stop);
}

void BenchmarkDialog::registerCallback(QProgressBar *pb, metro::CallbackType type, metro::Benchmark *benchmark) {
    benchmark->register_callback(BenchmarkWorker::publicCallback, pb, type, emitter);
}

void BenchmarkDialog::publicCallback(int value, void *progresBar) {
    auto pb = static_cast<QProgressBar *>(progresBar);
    pb->setValue(value);
    pb->repaint();
}

void BenchmarkDialog::reject() {
    if (stop) return QDialog::reject();
    stop = true;
    workerThread.wait();
    ui->progressBar->setVisible(false);
    ui->progressBar_2->setVisible(false);
    for (int i = 0; i < checkboxLayout->count(); i++) {
        QWidget *checkbox = checkboxLayout->itemAt(i)->widget();
        checkbox->setEnabled(true);
    }
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void BenchmarkDialog::onFinish() {
    if (stop) return;
    auto viewer = new BenchmarkViewer(benchmark);
    viewer->show();
    this->destroy();
}

