#ifndef METRO_ROUTE_H
#define METRO_ROUTE_H

#include "Station.h"

#include <algorithm>
#include <iostream>

enum station_insert_status {
    SUCCESS,
    ROUTE_COMPLETE,
    FAIL
};

class Route {
public:
    explicit Route(station_id target);
    Route(const Route *obj);

    int length;
    std::vector<station_id> path;
    station_id target;
    bool valid;

    station_insert_status addStation(station_id station);
};


#endif //METRO_ROUTE_H
