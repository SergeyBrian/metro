#ifndef METRO_METROAPP_H
#define METRO_METROAPP_H

#include <QApplication>
#include <QFileOpenEvent>
#include <QMessageBox>

#include "mainwindow.h"

class MetroApp : public QApplication {
    bool event(QEvent *event) noexcept override;

    QString m_macFileOpenOnStart;


public:
    MetroApp(int argc, char *argv[]);

    MainWindow *mainWindow;
};

#endif //METRO_METROAPP_H
