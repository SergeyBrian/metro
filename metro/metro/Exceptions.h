#ifndef METRO_EXCEPTIONS_H
#define METRO_EXCEPTIONS_H

#include <stdexcept>

namespace metro {
    class FilesysException : public std::runtime_error {
    public:
        FilesysException(const char *msg);
    };

    class InvalidVersionException : public FilesysException {
    public:
        InvalidVersionException();
    };

    class NotMetroFileException : public FilesysException {
    public:
        NotMetroFileException();
    };

    class DamagedFileException : public FilesysException {
    public:
        DamagedFileException();
    };

    class FileNotFoundException : public FilesysException {
    public:
        FileNotFoundException();
    };
}

#endif //METRO_EXCEPTIONS_H
