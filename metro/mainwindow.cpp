#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "metro/Exceptions.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    if (QApplication::arguments().size() > 1) {
        try {
            QFileInfo fileInfo(QApplication::arguments().at(1));
            openFile(fileInfo.fileName(), fileInfo.baseName());
        } catch (const std::runtime_error &e) {
            QMessageBox::critical(this, "Error", "Couldn't open file");
        }
    }
    QString newText = "New: " +
                      ui->actionNew->shortcut().toString(QKeySequence::NativeText) +
                      "\nOpen: " +
                      ui->actionOpen->shortcut().toString(QKeySequence::NativeText);
    ui->noFileOpen->setText(newText);
    showRecentFilesMenu(ui->menuFile, this);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_actionNew_triggered() {
    genDialog = new GenerateDialog(this);
    if (!genDialog->exec()) return;

    auto metro = new metro::Metro();
    metro->generate(genDialog->getParams());
    auto metroWindow = new MetroWindow(metro);
    this->close();
    metroWindow->activateWindow();
    metroWindow->showMaximized();
}

void MainWindow::on_actionOpen_triggered() {
    QString filename;
    QString filename_base;
    if (!selectFileOpen(&filename, &filename_base)) return;
    openFile(filename, filename_base);
}

void MainWindow::openFile(const QString &filename, const QString &filename_base) {
    MetroWindow *metroWindow;
    try {
        metroWindow = new MetroWindow(filename, filename_base);
    } catch (const std::runtime_error &e) {
        return;
    }

    this->close();
    metroWindow->activateWindow();
    metroWindow->showMaximized();
    addToRecentFiles(filename);
}

void MainWindow::on_actionOpenRecentTriggered() {
    auto action = dynamic_cast<QAction *>(QObject::sender());
    auto filename = action->data().value<QString>();
    openFile(filename, QFileInfo(filename).baseName());
}


void MainWindow::on_actionNavigator_benchmark_triggered() {
    auto benchmarkDialog = new BenchmarkDialog(this);
    benchmarkDialog->show();
}

