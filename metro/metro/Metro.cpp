#include "Metro.h"

namespace metro {
    Metro::Metro() {
        old_params = {
                .branch_count = 3,
                .stations_count = 10,
                .branch_threshold = 3,
                .min_distance = 2,
                .intersect_threshold = 4,
        };
        search_method = STUPID;
    }

    void Metro::generate(Params params) {
        branches.clear();
        stations.clear();
        route.clear();
        old_params = params;
        int sum_x = 0;
        int sum_y = 0;
        branches_connections = std::vector<std::vector<bool>>(params.branch_count,
                                                              std::vector<bool>(params.branch_count));

        for (int i = 0; i < params.stations_count; i++) {
            int x = biasedRandomInt(0, 100);
            int y = biasedRandomInt(0, 100);

            int distanceOk = true;
            for (const auto &station: stations) {
                int offset = squareRadius(station.pos, {x, y});
                if (offset <= params.min_distance * params.min_distance) {
                    distanceOk = false;
                    break;
                }
            }

            if (!distanceOk) {
                std::printf("[INFO] Skipping point at %d %d\n", x, y);
                i--;
                continue;
            }

            sum_x += x;
            sum_y += y;
            stations.push_back({
                                       .id = i,
                                       .name = "#" + std::to_string(i),
                                       .pos = {
                                               .x = x,
                                               .y = y,
                                       },
                                       .branch_id = -1,
                               });
        }

        Position centerPos = {sum_x / params.stations_count, sum_y / params.stations_count};
        this->center = centerPos;
        std::sort(stations.begin(), stations.end(), [&centerPos](const Station &a, const Station &b) {
            return getDistanceSquared(a.pos, centerPos) > getDistanceSquared(b.pos, centerPos);
        });
        for (int i = 0; i < params.branch_count; i++) {
            Branch branch = {
                    .id = i,
                    .color = getColor(static_cast<ColorID>(i)),
                    .begin = nullptr,
                    .end = nullptr,
            };

            for (auto &station: stations) {
                if (station.branch_id != -1) continue;
                if (!branch.begin) {
                    branch.begin = &station;
                    station.branch_id = i;
                    continue;
                }
                if (isInOppositeQuadrant(station.pos, branch.begin->pos, centerPos)) {
                    branch.end = &station;
                    station.branch_id = i;
                    break;
                }
            }

            branches[i] = branch;
        }

        for (auto &[id, branch]: branches) {
            std::vector<Station *> branch_stations;
            for (auto &station: stations) {
                if (distanceToLineSegment(station.pos, branch.begin->pos, branch.end->pos) >
                    params.branch_threshold || station.branch_id != -1)
                    continue;
                branch_stations.push_back(&station);
                station.branch_id = branch.id;
            }
            branch_stations.push_back(branch.end);
            branch_stations.push_back(branch.begin);
            std::sort(branch_stations.begin(), branch_stations.end(),
                      [](const Station *a, const Station *b) {
                          return (a->pos.x < b->pos.x) || (a->pos.x == b->pos.x && a->pos.y < b->pos.y);
                      });
            for (int i = 0; i < branch_stations.size() - 1; i++) {
                bindStations(branch_stations[i], branch_stations[i + 1]);
            }
            branch.stations_count = static_cast<int>(branch_stations.size());
        }

        for (auto &station: stations) {
            if (station.branch_id == -1) continue;
            for (auto &other_station: stations) {
                if (other_station.id == station.id) continue;
                if (other_station.branch_id == station.branch_id) continue;
                if (other_station.branch_id == -1) continue;
                if (branches_connections.at(station.branch_id).at(other_station.branch_id)) continue;
                bool alreadyConnected = false;
                for (auto &connection: other_station.connections) {
                    if (connection->branch_id == station.branch_id) {
                        alreadyConnected = true;
                        break;
                    }
                }
                if (alreadyConnected) continue;

                int offset = squareRadius(station.pos, other_station.pos);
                if (offset > params.intersect_threshold * params.intersect_threshold) continue;
                std::printf("[INFO] intersect %s and %s\n", station.name.c_str(), other_station.name.c_str());
                bindStations(&station, &other_station);
                branches_connections[station.branch_id][other_station.branch_id] = true;
                branches_connections[other_station.branch_id][station.branch_id] = true;
                station.pos = other_station.pos;
            }
        }
    }

    Branch Metro::getBranchByStation(const Station &station) {
        try {
            return branches.at(station.branch_id);
        } catch (const std::out_of_range &e) {
            return Branch{.color = getColor(CORAL)};
        }
    }

    bool Metro::addStationToRoute(Station *station) {
        route.addStation(station);
        bool route_status = route.calculate(search_method);
        if (!route_status) route.resetResult();
        return route_status;
    }

    bool Metro::removeStationFromRoute(Station *station) {
        route.removeStation(station);
        bool route_status = route.calculate(search_method);
        if (!route_status) route.resetResult();
        return route_status;
    }
}
