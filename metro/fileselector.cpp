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

void addToRecentFiles(const QString &filename) {
    QSettings settings;
    auto recentFiles = settings.value("recent_files").value<QStringList>();
    if (recentFiles.contains(filename)) {
        recentFiles.removeOne(filename);
    }
    recentFiles.insert(0, filename);
    settings.setValue("recent_files", recentFiles);
}

void showRecentFilesMenu(QMenu *fileMenu, QMainWindow *parent) {
    QMenu *recentMenu = fileMenu->addMenu("Open recent");
    QSettings settings;
    auto recentFiles = settings.value("recent_files").value<QStringList>();
    recentMenu->setDisabled(recentFiles.empty());
    for (const auto &filename: recentFiles) {
        QString filename_base = QFileInfo(filename).baseName();
        QAction *action = recentMenu->addAction(filename_base, parent, SLOT(on_actionOpenRecentTriggered()));
        action->setData(filename);
    }
}
