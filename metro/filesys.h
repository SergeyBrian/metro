#ifndef METRO_UI_FILESYS_H
#define METRO_UI_FILESYS_H

#include <QString>
#include <QMessageBox>
#include <QDialog>

#include "metro/Metro.h"
#include "metro/Filesys.h"
#include "metro/legacy_filesys/LegacyFilesys.h"

bool loadFromFile(const QString &filename, metro::Metro *metro);

bool saveToFile(const QString &filename, metro::Metro *metro);

#endif //METRO_UI_FILESYS_H
