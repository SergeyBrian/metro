#ifndef METRO_STATION_H
#define METRO_STATION_H

#include <string>
#include <utility>

#include "Position.h"

namespace metro {
    struct Station {
        int id;
        std::string name;
        Position pos;
        int branch_id;

        std::vector<Station *> connections;

        inline bool operator==(Station s) const {
            return s.id == id;
        }

        inline bool operator==(Station *s) const {
            return s->id == id;
        }
    };

    void bindStations(Station *a, Station *b);
};

#endif //METRO_STATION_H
