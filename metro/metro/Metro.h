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

#define METRO_MAX_STATIONS_COUNT 2000
#define METRO_MIN_STATIONS_COUNT 2
#define METRO_MIN_BRANCHES_COUNT 1
#define METRO_MAX_BRANCHES_COUNT(stations_count) (stations_count / 2)

namespace metro {
    class Metro {
    public:
        Metro();

        std::vector<Station> stations;
        std::unordered_map<int, Branch> branches;
        std::vector<std::vector<bool>> branches_connections;
        Route route{};

        void generate(Params params);

        Branch getBranchByStation(const Station &station);

        Position center{};
        Params old_params{};

        bool addStationToRoute(Station *station);

        bool removeStationFromRoute(Station *station);

        RouteSearchMethod search_method;
    };
}

#endif //METRO_METRO_H
