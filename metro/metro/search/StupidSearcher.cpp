#include "StupidSearcher.h"

namespace metro {
    StupidSearcher::~StupidSearcher() = default;

    bool StupidSearcher::findShortestRoute(const std::vector<Station *> &targetStations,
                                           std::vector<Station *> *route) {
        findAllRoutes(targetStations, {targetStations.front()});
        bool status;
        *route = selectShortestRoute(&status);
        return status;
    }

    void StupidSearcher::findAllRoutes(const std::vector<Station *> &targetStations,
                                       std::vector<Station *> curr_route) {
        Station *target_station = targetStations.back();
        Station *current_station = curr_route.back();
        if (current_station == target_station) {
            // Проверяем, что мы посетили все станции, которые заказывали
            for (auto targetStation: targetStations) {
                if (std::find(curr_route.begin(), curr_route.end(), targetStation) == curr_route.end()) return;
            }
            allRoutes.push_back(curr_route);
            return;
        }
        for (const auto &station: current_station->connections) {
            if (std::find(curr_route.begin(), curr_route.end(), station) != curr_route.end()) {
                continue;
            }
            std::vector<Station *> new_route = curr_route;
            new_route.push_back(station);
            findAllRoutes(targetStations, new_route);
        }
    }

    std::vector<Station *> StupidSearcher::selectShortestRoute(bool *status) {
        int min_route_len = INT_MAX;
        std::vector<Station *> shortest_route;
        for (const auto &route: allRoutes) {
            int route_len = 0;
            for (int i = 0; i < route.size() - 1; i++) {
                route_len += getDistanceSquared(route.at(i)->pos, route.at(i + 1)->pos);
            }
            if (route_len < min_route_len) {
                min_route_len = route_len;
                shortest_route = route;
            }
        }
        *status = !shortest_route.empty();
        return shortest_route;
    }
}