#ifndef METRO_FILESELECTOR_H
#define METRO_FILESELECTOR_H

#include <QFileDialog>
#include <QSettings>
#include <QMainWindow>
#include <QMenu>

bool selectFileOpen(QString *filename, QString *filename_base = nullptr);

bool selectFileSave(QString *filename, QString *filename_base = nullptr);

void addToRecentFiles(const QString &filename);

void showRecentFilesMenu(QMenu *fileMenu, QMainWindow *parent);

#endif //METRO_FILESELECTOR_H
