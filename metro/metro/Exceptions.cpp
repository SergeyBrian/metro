#include "Exceptions.h"


metro::FilesysException::FilesysException(const char *msg) : runtime_error(msg) {}

metro::InvalidVersionException::InvalidVersionException() : FilesysException(
        "Metro file was saved in incompatible version of program"
) {}

metro::NotMetroFileException::NotMetroFileException() : FilesysException(
        "Not a metro file"
) {}

metro::DamagedFileException::DamagedFileException() : FilesysException(
        "File is damaged"
) {}

metro::FileNotFoundException::FileNotFoundException() : FilesysException(
        "File not found"
) {}
