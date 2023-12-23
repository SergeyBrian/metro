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

    auto metro = new metro::Metro();
    metro->generate(genDialog->getParams());
    auto metroWindow = new MetroWindow(metro);
    this->close();
    metroWindow->activateWindow();
    metroWindow->showMaximized();
}
