#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QDebug>
#include <QStatusBar>
#include <QMessageBox>

#include "generatedialog.h"
#include "metrowindow.h"
#include "fileselector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GenerateDialog *genDialog;
private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
