#ifndef METRO_FILESYS_V2_H
#define METRO_FILESYS_V2_H

#include "../Metro.h"

namespace metro::legacy::filesys_v2 {
    struct FStation {
        FStation();

        int id{};
        std::string name;
        Position pos{};
        int branch_id{};
        std::vector<int> connections;

        explicit FStation(const Station *station);
    };

    struct FBranch {
        FBranch();

        int id{};
        int stations_count{};
        Color color;
        int begin_id{};
        int end_id{};

        explicit FBranch(const Branch *branch);
    };


    void loadFromFile(const std::string &filename, metro::Metro *metro);
}

#endif //METRO_FILESYS_V2_H
