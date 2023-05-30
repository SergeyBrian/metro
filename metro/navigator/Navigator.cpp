#include "Navigator.h"

Navigator::Navigator(StationList *stationList) {
    this->stationList = stationList;
}

Route *Navigator::findShortestRoute(station_id begin, station_id end) {
    auto init_route = new Route(end);
    routes.push_back(init_route);
    findAllRoutes(begin, end, init_route);

    int min_len = INT16_MAX;
    int min_index = -1;

    for (int i = 0; i < routes.size(); i++) {
        Route *route = routes[i];
        if (!route->valid) continue;
        if (route->length < min_len) {
            min_len = route->length;
            min_index = i;
        }
    }
    return routes[min_index];
}

int Navigator::findAllRoutes(station_id current, station_id end, Route *route) {
    Station *station = stationList->getStation(current);
    station_insert_status insertStatus = route->addStation(current);

    if (insertStatus == FAIL) return 0;
    if (insertStatus == ROUTE_COMPLETE) return 1;

    for (auto &connection: station->connections) {
        if (connection == current) continue;
        Route *route_copy = new Route(route);
        routes.push_back(route_copy);
        findAllRoutes(connection, end, route_copy);
    }

    return 0;
}

void Navigator::forgetRoutes() {
    routes.clear();
}
