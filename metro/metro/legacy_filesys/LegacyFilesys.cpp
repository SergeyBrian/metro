#include "LegacyFilesys.h"

void metro::legacy::loadFromFile(const std::string &filename, metro::Metro *metro, int file_version) {
    switch (file_version) {
        case 2:
            filesys_v2::loadFromFile(filename, metro);
            break;
        default:
            throw std::runtime_error("Failed to load from file");
    }
}
