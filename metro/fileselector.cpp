#include "fileselector.h"

bool selectFileOpen(QString *filename) {
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
    return true;
}

bool selectFileSave(QString *filename) {
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
    return true;
}
