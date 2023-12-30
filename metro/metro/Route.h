#ifndef METRO_ROUTE_H
#define METRO_ROUTE_H

#include "Utils.h"
#include "Station.h"

namespace metro {
    struct Route {
        std::vector<Station *> stations;
    };
}

#endif //METRO_ROUTE_H
