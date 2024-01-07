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
        switch (method) {
            case STUPID:
                return stupidSearch();
                break;
        }
    }

    void Route::clear() {
        target_stations.clear();
        route.clear();
    }

    bool Route::stupidSearch() {
        Station *begin = target_stations.front();
        route.push_back(begin);
        return true;
    }
}
