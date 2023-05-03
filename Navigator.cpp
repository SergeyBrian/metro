#include "Navigator.h"

int Navigator::findShortestRoute(Station *start, Station *end, Station *prev, std::vector<station_id> *route) {
    route->push_back(start->id);
    if (start->id == end->id) {
        return route->size();
    }

    int route_len = INT32_MAX;

    bool is_end_station = true;
    for (int i = 0; i < start->connections.size(); i++) {
        if (std::find(route->begin(), route->end(), start->connections[i]) != route->end()) continue;
        is_end_station = false;
        int tmp_route_len = findShortestRoute(stationList->getStation(start->connections[i]), end, start, route);
        if (tmp_route_len != -1 && tmp_route_len < route_len) route_len = tmp_route_len;
    }

    if (is_end_station || route_len == -1) {
        route->pop_back();
        return -1;
    }

    return route_len;
}

Navigator::Navigator(StationList *stationList) {
    this->stationList = stationList;
}
