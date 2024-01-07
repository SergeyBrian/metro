#ifndef METRO_LEGACYFILESYS_H
#define METRO_LEGACYFILESYS_H

#include "Filesys_v2.h"

namespace metro::legacy {
    void loadFromFile(const std::string &filename, metro::Metro *metro, int file_version);
}

#endif //METRO_LEGACYFILESYS_H
