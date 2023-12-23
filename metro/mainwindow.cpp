#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QString newText = "New: " +
                      ui->actionNew->shortcut().toString(QKeySequence::NativeText) +
                      "\nOpen: " +
                      ui->actionOpen->shortcut().toString(QKeySequence::NativeText);
    ui->noFileOpen->setText(newText);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_actionNew_triggered() {
    genDialog = new GenerateDialog(this);
    if (!genDialog->exec()) return;
    int stationsCount = genDialog->getStationsCount();
    int branchesCount = genDialog->getBranchesCount();
    int branchThreshold = genDialog->getBranchThreshold();
    QString seed = genDialog->getSeed();
    auto metro = new metro::Metro();
    metro->generate(metro::Params{
            .branch_count = branchesCount,
            .stations_count = stationsCount,
            .branch_threshold = branchThreshold,
    });
    auto metroWindow = new MetroWindow(metro);
    this->close();
    metroWindow->activateWindow();
    metroWindow->showMaximized();
}
