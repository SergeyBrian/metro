#ifndef METRO_METRO_H
#define METRO_METRO_H

#include <algorithm>

#include "Utils.h"

#include "Params.h"
#include "Station.h"
#include "Branch.h"

namespace metro {
    class Metro {
    public:
        Metro();

        std::vector<Station> stations;
        std::unordered_map<int, Branch> branches;

        void generate(Params params);

        Branch getBranchByStation(const Station &station);

        Position center{};
    };
}

#endif //METRO_METRO_H
