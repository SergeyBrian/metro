#include "filesys.h"

bool loadFromFile(const QString &filename, metro::Metro *metro) {
    try {
        metro::loadFromFile(filename.toStdString(), metro);
        return true;
    }
    catch (const metro::InvalidVersionException &e) {
        QMessageBox::StandardButton useLegacy = QMessageBox::critical(nullptr, "Incompatible file version",
                                                                      "Incompatible file version. Try loading anyway?",
                                                                      QMessageBox::Yes | QMessageBox::No);
        if (useLegacy == QMessageBox::Yes) {
            try {
                metro::legacy::loadFromFile(filename.toStdString(), metro, e.version);
                return true;
            } catch (const metro::FilesysException &e) {
                QMessageBox::critical(nullptr, "Error", QString::fromStdString(e.what()));
                return false;
            } catch (const std::runtime_error &e) {
                QMessageBox::critical(nullptr, "Error", e.what());
                return false;
            }
        }
        return false;
    } catch (const metro::FilesysException &e) {
        QMessageBox::critical(nullptr, "Error", QString::fromStdString(e.what()));
        return false;
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(nullptr, "Error", "Error reading file");
        return false;
    }
}

bool saveToFile(const QString &filename, metro::Metro *metro) {
    try {
        metro::saveToFile(filename.toStdString(), metro);
        return true;
    } catch (const std::runtime_error &e) {
        QMessageBox::critical(nullptr, "Error", "Error reading file");
        return false;
    }
}
