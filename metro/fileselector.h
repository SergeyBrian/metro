#ifndef METRO_FILESELECTOR_H
#define METRO_FILESELECTOR_H

#include <QFileDialog>
#include <QSettings>

bool selectFileOpen(QString *filename, QString *filename_base = nullptr);

bool selectFileSave(QString *filename, QString *filename_base = nullptr);

#endif //METRO_FILESELECTOR_H
