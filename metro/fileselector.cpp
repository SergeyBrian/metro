#include "fileselector.h"

bool selectFileOpen(QString *filename, QString *filename_base) {
    auto fileDialog = QFileDialog();
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setDefaultSuffix("mettro");
    fileDialog.setNameFilter(QFileDialog::tr("Mettro (*.mettro)"));
    QSettings settings;
    QString lastDir = settings.value("lastDir", QDir::homePath()).toString();
    fileDialog.setDirectory(lastDir);
    if (!fileDialog.exec()) return false;
    *filename = fileDialog.selectedFiles()[0];
    QFileInfo fileInfo(*filename);
    settings.setValue("lastDir", fileInfo.absolutePath());
    if (!filename_base) return true;
    *filename_base = fileInfo.baseName();
    return true;
}

bool selectFileSave(QString *filename, QString *filename_base) {
    auto fileDialog = QFileDialog();
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setDefaultSuffix("mettro");
    fileDialog.setNameFilter(QFileDialog::tr("Mettro (*.mettro)"));
    QSettings settings;
    QString lastDir = settings.value("lastDir", QDir::homePath()).toString();
    fileDialog.setDirectory(lastDir);
    if (!fileDialog.exec()) return false;
    *filename = fileDialog.selectedFiles()[0];
    QFileInfo fileInfo(*filename);
    settings.setValue("lastDir", fileInfo.absolutePath());
    if (!filename_base) return true;
    *filename_base = fileInfo.baseName();
    return true;
}
