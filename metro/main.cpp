#include "mainwindow.h"

#include "metroapp.h"

int main(int argc, char *argv[]) {
    MetroApp a(argc, argv);
    MainWindow w;
    a.mainWindow = &w;
    w.show();
    return a.exec();
}
