#ifndef METRO_NAVIGATOR_H
#define METRO_NAVIGATOR_H

#include "StationList.h"
#include "Route.h"

class Navigator {
public:
    explicit Navigator(StationList *stationList);

    ~Navigator() = default;

    Route *findShortestRoute(station_id begin, station_id end);

    std::vector<Route *> routes;

    int findAllRoutes(station_id current, station_id end, Route *route);

    StationList *stationList;

    void forgetRoutes();
};


#endif //METRO_NAVIGATOR_H
