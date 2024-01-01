#include "Route.h"

namespace metro {
    bool dijkstraSearch(Route *route) {
        Station *begin = route->target_stations.front();
        route->route.push_back(begin);
        return true;
    }

    bool calculateRoute(Route *route, RouteSearchMethod method) {
        if (route->target_stations.size() < 2) return false;
        route->route.clear();
        switch (method) {
            case DIJKSTRA:
                return dijkstraSearch(route);
                break;
        }
    }
}
