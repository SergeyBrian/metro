#ifndef METRO_METRO_H
#define METRO_METRO_H

#define METRO_LIB_VERSION 2

#include <algorithm>
#include <fstream>

#include "Utils.h"

#include "Params.h"
#include "Station.h"
#include "Branch.h"
#include "Route.h"
#include "Exceptions.h"

namespace metro {
    class Metro {
    public:
        Metro();

        std::vector<Station> stations;
        std::unordered_map<int, Branch> branches;
        Route route{};

        void generate(Params params);

        Branch getBranchByStation(const Station &station);

        Position center{};
        Params old_params{};

        void addStationToRoute(Station *station);

        void removeStationFromRoute(Station *station);
    };
}

#endif //METRO_METRO_H
