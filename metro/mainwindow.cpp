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

void MainWindow::on_actionOpen_triggered() {
    QString filename;
    if (!selectFileOpen(&filename)) return;
    try {
        auto metroWindow = new MetroWindow(filename);

        this->close();
        metroWindow->activateWindow();
        metroWindow->showMaximized();
    } catch (const metro::InvalidVersionException &e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(this, "Error", "Error reading file");
    }
}

