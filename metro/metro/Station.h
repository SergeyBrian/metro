#ifndef METRO_STATION_H
#define METRO_STATION_H

#include <string>
#include <utility>

#include "Position.h"

namespace metro {
    struct Station {
        std::string name;
        Position pos;
        int branch_id;

        std::vector<Station *> connections;
    };

    void bindStations(Station *a, Station *b);
};

#endif //METRO_STATION_H
