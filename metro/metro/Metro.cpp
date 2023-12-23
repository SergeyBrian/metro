#include "Metro.h"

namespace metro {
    Metro::Metro() = default;

    void Metro::generate(Params params) {
        int sum_x = 0;
        int sum_y = 0;

        for (int i = 0; i < params.stations_count; i++) {
            int x = biasedRandomInt(0, 100);
            int y = biasedRandomInt(0, 100);

            sum_x += x;
            sum_y += y;
            stations.push_back({
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
    }

    Branch Metro::getBranchByStation(const Station &station) {
        try {
            return branches.at(station.branch_id);
        } catch (const std::out_of_range &e) {
            return Branch{};
        }
    }
}
