#include "metroapp.h"

bool MetroApp::event(QEvent *event) noexcept {
    switch (event->type()) {
        case QEvent::FileOpen: {
            auto fileOpenEvent = dynamic_cast<QFileOpenEvent *>(event);
            if (fileOpenEvent) {
                QString filename = fileOpenEvent->file();
                QFileInfo fileInfo(filename);
                mainWindow->openFile(filename, fileInfo.baseName());
            }
            break;
        }
        default:
            return QApplication::event(event);
    }
    return QApplication::event(event);
}

MetroApp::MetroApp(int argc, char **argv) : QApplication(argc, argv) {};
