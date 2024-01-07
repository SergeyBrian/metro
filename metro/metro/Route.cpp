#include "Route.h"

namespace metro {
    Route::Route() = default;

    std::vector<Station *> Route::getRoute() {
        return route;
    }

    void Route::addStation(Station *station) {
        target_stations.push_back(station);
    }

    void Route::removeStation(Station *station) {
        target_stations.erase(
                std::remove_if(target_stations.begin(), target_stations.end(),
                               [&](Station *s) { return s->id == station->id; }),
                target_stations.end()
        );
    }

    bool Route::calculate(RouteSearchMethod method) {
        if (target_stations.size() < 2) return false;
        route.clear();
        ISearcher *searcher = getSearcher(method);
        bool status = searcher->findShortestRoute(target_stations, &route);
        delete searcher;
        return status;
    }

    void Route::clear() {
        target_stations.clear();
        route.clear();
    }

    std::vector<Station *> Route::getTargetStations() {
        return target_stations;
    }

    void Route::resetResult() {
        route.clear();
    }

    int Route::length() {
        int len = 0;
        for (int i = 0; i < route.size() - 1; i++) {
            len += getDistanceSquared(route.at(i)->pos, route.at(i + 1)->pos);
        }
        return len;
    }
}
